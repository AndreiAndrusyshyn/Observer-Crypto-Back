#include "TestDataGenerator.h"

//data* TestDataGenerator::properData() {
////    return &parsedData;
//}

data* testDataGenerator::differenClaimAndStackAmountNumbers()
{
    srand(time(NULL));
    parsedData.claimUserAmount = (rand()%5);
    parsedData.stackUserAmount = (rand()%1 + 4);
    return &parsedData;
}

data* testDataGenerator::differenClaimAndStackBlockNumbers()
{
    srand(time(NULL));
    parsedData.claimBlockNumber = (rand()%5);
    parsedData.stackBlockNumber = (rand()%1 + 4);
    return &parsedData;
}

data* testDataGenerator::differenClaimAndStackUUID()
{
    boost::uuids::random_generator gen_rand;
    parsedData.claimUUID = gen_rand();
    parsedData.stackUUID = gen_rand();
    return &parsedData;
}

data* testDataGenerator::differenClaimAndStackPaymentID()
{
    srand(time(NULL));
    parsedData.claimUserAmount = 4 ;
    parsedData.paymentID.reserve(8);
    for (int i = 0 ; i < 4;) {
        parsedData.paymentID[i] = (rand() %1 + 5);
        ++i;
    }
    return &parsedData;
}

data* testDataGenerator::corruptedSignatures()
{
    parsedData.claimUserAmount =4;

    parsedData.signatures.reserve(4);
    for (int i = 0 ; i < 4;) {
        parsedData.signatures[0] = (byte*)'2';
        ++i;
    }
    return &parsedData;
}

data* testDataGenerator::corruptedPublickKeys()
{
    parsedData.claimUserAmount =4;
    parsedData.publicKeys.reserve(4);

    for (int i = 0 ; i < 4;) {
        parsedData.publicKeys[i] = (byte*)'4';
        ++i;
    };
    return &parsedData;
}

data* testDataGenerator::corruptedBuffer()
{
    parsedData.bufferReferenceData = new byte('3');
    return &parsedData;
}