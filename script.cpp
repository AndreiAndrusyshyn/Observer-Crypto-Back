#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

int main()
{
    int fd1;

    char response[80], file_name[80];

    uint16_t get;

    while(1) {
        // Now open in write mode and write
        // string taken from u
        // ser.
        fd1 = open("fifo", O_WRONLY);
        fgets(file_name, sizeof(file_name), stdin);
        write(fd1, file_name, strlen(file_name) + 1);
        close(fd1);

        fd1 = open("fifo", O_RDONLY);
        read(fd1, response, sizeof(response));
        close(fd1);


        std::cout<<response<<"\n";
    }

}

