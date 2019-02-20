#include "DataParser.h"
#include "../../validation/Validator.cpp"

DataParser::DataParser(const string &FileNameBuffer) : fileName(FileNameBuffer.data()), readFile(fileName, std::ios::binary){

    mAnswerDescriptor = open("fifo/answers.fifo", O_WRONLY | O_NONBLOCK);
    readData();
    passToValidator();
    writeAnswer();
}

void DataParser::readData()
{
    readFile.read((char*)&parsedData.claimBlockNumber, sizeof(uint64_t));
    readFile.read((char*)&parsedData.claimUUID, sizeof(boost::uuids::uuid));
    readFile.read((char*)&parsedData.claimUserAmount ,sizeof(uint16_t));

    for(int i = 0 ; i< parsedData.claimUserAmount;)
    {
        readFile.read((char*)&ID, sizeof(ID));
        parsedData.paymentID.push_back(ID);
        i++;
    }

    for(int i = 0 ; i< parsedData.claimUserAmount;)
    {
        readFile.read((char*)bufferPublicKeys, PublicKey::kKeySize());
        parsedData.publicKeys.push_back(bufferPublicKeys);
        i++;
    }

    readFile.read((char *) &parsedData.stackBlockNumber, sizeof(uint64_t));
    readFile.read((char *) &parsedData.stackUUID, sizeof(boost::uuids::uuid));
    readFile.read((char *) &parsedData.stackUserAmount, sizeof(uint16_t));

    for (int i = 0; i < parsedData.claimUserAmount;)
    {
        readFile.read((char*) &ID, sizeof(ID));
        parsedData.paymentID.push_back(ID);

        i++;
    }

    for (int i = 0; i < parsedData.claimUserAmount;)
    {
        readFile.read((char *) bufferSignature, Signature::signatureSize());
        parsedData.signatures.push_back(bufferSignature);
        i++;
    }

    readFile.seekg(0, ios::beg);

    readFile.read((char*)parsedData.bufferReferenceData, sizeof(parsedData.bufferReferenceData));

}

void DataParser::passToValidator()
{
    ptrToValidator = new Validator(&parsedData);
}

void DataParser::writeAnswer()
{
    write(mAnswerDescriptor, (ptrToValidator->check() + "\n").c_str(), (ptrToValidator->check() + "\n").size());
}

DataParser::~DataParser()
{
    delete ptrToValidator;
    readFile.close();
    close(mAnswerDescriptor);
}