#ifdef GENERATOR
#include "source/file_generator/file_generator.cpp"
#endif

#ifdef VALIDATOR
#include "source/validation/validator.cpp"
#endif

int main(int argc, char **argv)
{
#ifdef GENERATOR
   file_generator();
#endif

#ifdef VALIDATOR
   validator validator(argv[1]);
#endif

};