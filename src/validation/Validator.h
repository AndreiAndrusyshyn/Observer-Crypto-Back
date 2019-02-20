#ifndef OCB_VALIDATOR_H
#define OCB_VALIDATOR_H

#include "../../include/includes.h"

class Validator
{
public:
    explicit Validator(struct data *structData);
    string check();
   // ~Validator();
private:
   data *mStruct;
};
#endif //OCB_VALIDATOR_H
