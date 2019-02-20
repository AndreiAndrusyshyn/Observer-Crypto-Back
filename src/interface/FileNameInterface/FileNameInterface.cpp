#include "FileNameInterface.h"

FileNameInterface::FileNameInterface(as::io_service &ioService) : mIOService(ioService)
{

    if(!ifFIFOExists()){
        createFIFO(kPermissionMaks);

    }
    if(!ifFIFOAnswerExists())
    {
        createFIFOAnswer(kPermissionMaks);
    }
    mFIFODescriptor = open(FIFOFilePath().c_str(), O_RDONLY | O_NONBLOCK);

    if(mFIFODescriptor == -1)
    {
        std::cout<<"Can't Open Fifo file";
        std::abort();
    }

    try
    {
        mFIFOStreamDescriptor = unique_ptr<as::posix::stream_descriptor> (new as::posix::stream_descriptor(
                mIOService,
                mFIFODescriptor));
        mFIFOStreamDescriptor -> non_blocking(true);
    }catch(std::bad_alloc &)
    {
        std::cout<<"Can not allocate enough memory for fifo stream descriptoy";
    }

    try
    {
        mReadTimeoutTimer = unique_ptr<as::deadline_timer> (new as::deadline_timer(mIOService, boost::posix_time::seconds(2)));

    }catch (std::bad_alloc &){
        std::cout<<"Can not allocate enough memory for fifo read timer";
    }
    mFileNameParser = unique_ptr<FileNameParser>(new FileNameParser());
    mFileNameBuffer.prepare(kFileNameBufferSize);

}

FileNameInterface::~FileNameInterface()
{
    mFIFOStreamDescriptor->cancel();
    mReadTimeoutTimer->cancel();
    close(mFIFODescriptor);
}

void FileNameInterface::beginAcceptFileNames()
{
    asyncReceiveNextFileName();
}

void FileNameInterface::asyncReceiveNextFileName()
{
    as::async_read_until(*mFIFOStreamDescriptor, mFileNameBuffer,
            kFileNameSepator,
            boost::bind(&FileNameInterface::handleReceivedInfo, this,
                    as::placeholders::error,
                    as::placeholders::bytes_transferred));


}

void FileNameInterface::handleReceivedInfo(const boost::system::error_code &error, const size_t bytesTransferred)
{
    if (!error || error == as::error::message_size)
    {
        mFileNameParser->appendReadData(&mFileNameBuffer, bytesTransferred);
        mFileNameBuffer.consume(bytesTransferred);
        while (true)
        {
            auto flagAndFileName = mFileNameParser->processReceivedFileName();
            if (flagAndFileName.first)
            {
                FileNameReceivedSignal(flagAndFileName.second);
            }
            else
            {
                break;
            }
        }
        asyncReceiveNextFileName();
    }
    else
    {
        if (error == as::error::eof)
        {
            mReadTimeoutTimer->expires_from_now(boost::posix_time::seconds(1));
            mReadTimeoutTimer->async_wait(
                    boost::bind(&FileNameInterface::handleTimeout, this, as::placeholders::error));

        }
        else
        {
            mReadTimeoutTimer->expires_from_now(boost::posix_time::minutes(10));
            mReadTimeoutTimer->async_wait(boost::bind(&FileNameInterface::handleTimeout, this, as::placeholders::error));

        }
    }
}

const char *FileNameInterface::FIFOName() const
{
    return  kFIFOName;
}

const char *FileNameInterface::FIFONameAnswer() const
{
    return  kFIFONameAnswer;
}

void FileNameInterface::handleTimeout(const boost::system::error_code &errorMessage)
{
  if(errorMessage)
  {
      throw 1;
  }
    asyncReceiveNextFileName();
}