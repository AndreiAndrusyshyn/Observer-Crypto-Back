#include "FileNameParser.h"

FileNameParser::FileNameParser() {};

void FileNameParser::appendReadData(as::streambuf *buffer,
                                    const size_t receivedBytesCount)
{
    if (receivedBytesCount == 0)
    {
        return;
    }

    const char *data = as::buffer_cast<const char *>(buffer->data());

    for (size_t i = 0; i < receivedBytesCount; ++i)
    {
        mBuffer.push_back(*data++);
    }

}

pair<bool, DataParser::Shared> FileNameParser::processReceivedFileName()
{
    return tryDeserializeFileName();
}

pair<bool, DataParser::Shared> FileNameParser::tryDeserializeFileName()
{

    if (mBuffer.size() < (kFileNameRepresentationSize))
    {
        return FileNameIsInvalidorIncomplete();
    }

    size_t nextFileNameSeparatorIndex = mBuffer.find(kFileNameSepator);

    if (nextFileNameSeparatorIndex == string::npos)
    {
        return FileNameIsInvalidorIncomplete();
    }

    try
    {
        auto name = tryParseFileName(mBuffer.substr(0, kFileNameRepresentationSize - 1));

        cutBufferUpToNextFileName();
        return name;

    }
    catch (std::exception &e)
    {
        cutBufferUpToNextFileName();
        return FileNameIsInvalidorIncomplete();
    }

}


pair<bool, DataParser::Shared> FileNameParser::tryParseFileName(const string &buffer)
{
    DataParser *data = nullptr;

    try
    {
        data = new DataParser(buffer);
    }
    catch (bad_alloc &)
    {
        return FileNameIsInvalidorIncomplete();
    }
    return make_pair(true, DataParser::Shared(data));
}

pair<bool, DataParser::Shared> FileNameParser::FileNameIsInvalidorIncomplete()
{
    return make_pair(false, nullptr);
}

void FileNameParser::cutBufferUpToNextFileName()
{
    size_t nextFileNameSeparatorIndex = mBuffer.find(kFileNameSepator);
    if (mBuffer.size() > (nextFileNameSeparatorIndex))
    {
        mBuffer = mBuffer.substr(nextFileNameSeparatorIndex + 1, mBuffer.size() - 1);
    }
    else
    {
        mBuffer.clear();
    }
    mBuffer.shrink_to_fit();
}

