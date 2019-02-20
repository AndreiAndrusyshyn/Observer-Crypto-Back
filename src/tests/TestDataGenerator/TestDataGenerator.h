#ifndef TEST_FILE_GENERATOR_H
#define TEST_FILE_GENERATOR_H

#include "../../../include/includes.h"

class testDataGenerator
{
public:
    data* properData();
    data* differenClaimAndStackAmountNumbers();
    data* differenClaimAndStackBlockNumbers();
    data* differenClaimAndStackUUID();
    data* differenClaimAndStackPaymentID();
    data* corruptedSignatures();
    data* corruptedPublickKeys();
    data* corruptedBuffer();
private:
    data parsedData;
};
#endif //TEST_FILE_GENERATOR_H