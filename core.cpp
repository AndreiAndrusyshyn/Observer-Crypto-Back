#ifdef GENERATOR
#define CATCH_CONFIG_MAIN
#include "source/tests/catch.hpp"
#include "source/tests/validator_test/validator_test.cpp"
#endif
#ifdef VALIDATOR
#include "source/validation/validator.cpp"
#endif

#ifndef GENERATOR
int main()
{
    char file_name[80],response[80];;
    int fifi_open;
    mkfifo("fifo", 0666);
    char stop[2] = {'q'};
    while(string(file_name) != stop)
    {
        fifi_open = open("fifo", O_RDONLY);
        read(fifi_open, file_name, sizeof(file_name));
        close(fifi_open);

        auto renew_file_name = std::remove(std::begin(file_name), std::end(file_name),'\n' );

        validator *validation= new validator(file_name);

        sprintf(response, "%d", validation->return_answer());

        fifi_open = open("fifo", O_WRONLY);
        write(fifi_open, response, sizeof(file_name));
        close(fifi_open);
    }
}
#endif