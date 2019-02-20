#include "Validator.h"
#include "../interface/DataParser/DataParser.h"

Validator::Validator(struct data *structData) : mStruct(structData) {};

string Validator::check()
{
    sodium_init();
    if (mStruct->claimBlockNumber != mStruct->stackBlockNumber
        || mStruct->claimUserAmount != mStruct->stackUserAmount
        || mStruct->claimUUID != mStruct->stackUUID)
    {
        return "255";
    }
    else
    {
        if (mStruct->paymentID[0] != 0 || mStruct->paymentID[mStruct->paymentID.size() / 2] != 0) { return "255"; }
        for (uint16_t i = 0; i < (mStruct->claimUserAmount) / 2;)
        {
            if (mStruct->paymentID[i] != mStruct->paymentID[(mStruct->paymentID.size() / 2) + i]) { return "255"; }

            ++i;
        }

        for (uint16_t i = 0; i < (mStruct->claimUserAmount);)
        {
            Signature sig(mStruct->signatures[i]);
            if (!(sig.check(mStruct->bufferReferenceData, sizeof(mStruct->bufferReferenceData),
                            make_shared<PublicKey>(mStruct->publicKeys[i])))) { return "255"; }
            ++i;
        }


        return "1";
    }

}
//
//Validator::~Validator() {
//    delete mStruct;
//}
//


