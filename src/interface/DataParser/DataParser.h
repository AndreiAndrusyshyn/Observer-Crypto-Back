#ifndef OCB_DATAPARSER_H
#define OCB_DATAPARSER_H

#include "../../dataStruct/DataStruct.h"
#include "../../validation/Validator.h"

class DataParser
{
public:
    typedef shared_ptr<DataParser> Shared;
    DataParser(const string &FileNameBuffer);
    void passToValidator();
    void readData();
    void writeAnswer();
    ~DataParser();

private:
    uint16_t ID;
    byte *bufferSignature = new byte[Signature::signatureSize()];
    byte *bufferPublicKeys = new byte[PublicKey::kKeySize()];
    const char *fileName;
    std::ifstream readFile;
    int mAnswerDescriptor;
    Validator *ptrToValidator;
};

#endif //OCB_DATAPARSER_H
