#ifdef GENERATOR
#include "source/file_generator/file_generator.cpp"
#endif

int main()
{
#ifdef GENERATOR
    file_generator generator;
#endif

#ifdef UTIL
    //here comes main util
#endif
}