#ifndef OCB_FILEDATAPARSER_H
#define OCB_FILEDATAPARSER_H

#include "../../../src/interface/DataParser/DataParser.cpp"

class FileNameParser
{
public:
    FileNameParser();
    void appendReadData(as::streambuf *buffer, const size_t receivedBytesCount);
    pair<bool, DataParser::Shared> processReceivedFileName();
    static const size_t kFileNameRepresentationSize = 41;
private:
    inline pair<bool, DataParser::Shared> tryDeserializeFileName();
    inline pair<bool, DataParser::Shared> tryParseFileName(const string &buffer);
    inline pair<bool, DataParser::Shared> FileNameIsInvalidorIncomplete();
    void cutBufferUpToNextFileName();
private:
    std::string mBuffer;

};


#endif //OCB_FILEDATAPARSER_H
