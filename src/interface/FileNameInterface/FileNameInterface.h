#ifndef OCB_FILENAMEINTERFACE_H
#define OCB_FILENAMEINTERFACE_H

#include "../../interface/FifoInterface.h"
#include "../FileDataParser/FileNameParser.cpp"

class FileNameInterface : public FifoInterface {
public:
    signals::signal<void(DataParser::Shared)> FileNameReceivedSignal;
    explicit FileNameInterface(as::io_service &ioService);
    void beginAcceptFileNames();
    static const constexpr char *kFIFOName = "requests.fifo";
    static const constexpr char *kFIFONameAnswer = "answers.fifo";
    static const constexpr unsigned int kPermissionMaks = 0666;
    ~FileNameInterface();
protected:
    virtual const char* FIFOName() const;
    virtual const char* FIFONameAnswer() const;
    static const constexpr size_t kFileNameBufferSize = 1024;
    as::io_service &mIOService;
    void asyncReceiveNextFileName();
    void handleReceivedInfo(const boost::system::error_code &error, const size_t bytesTransferred);
    void handleTimeout(const boost::system::error_code &error);
    as::streambuf mFileNameBuffer;
    unique_ptr<as::posix::stream_descriptor> mFIFOStreamDescriptor;
    unique_ptr<as::deadline_timer> mReadTimeoutTimer;
    unique_ptr<FileNameParser> mFileNameParser;
};


#endif //OCB_FILENAMEINTERFACE_H
