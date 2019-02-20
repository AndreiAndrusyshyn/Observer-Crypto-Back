#ifdef GENERATOR
#define CATCH_CONFIG_MAIN
#include "src/tests/catch.hpp"
#include "src/tests/TestValidator/TestValidator.cpp"
#endif

#ifdef VALIDATOR
#include "src/interface/initInterface/InitInterface.cpp"
#endif

#ifndef GENERATOR
int main()
{
   return InitInterface().run();
}
#endif