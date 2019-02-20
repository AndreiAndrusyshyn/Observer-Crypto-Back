#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/signals2.hpp>
#include <string>
#include <boost/bind.hpp>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;
namespace as = boost::asio;
namespace fs = boost::filesystem;
namespace signals = boost::signals2;

static const constexpr char kFileNameSepator = '\n';

std::string make_string(boost::asio::streambuf& streambuf)
{
    return {boost::asio::buffers_begin(streambuf.data()),
            boost::asio::buffers_end(streambuf.data())};
}

int main() {
    int as;
    as = open("fifo/requests.fifo", O_WRONLY | O_NONBLOCK);
    int ad;
    ad = open("fifo/answers.fifo", O_RDONLY | O_NONBLOCK);
    as::io_service io_service1;

    unique_ptr<as::posix::stream_descriptor> mWrite = unique_ptr<as::posix::stream_descriptor>(
            new as::posix::stream_descriptor(io_service1, as));
    unique_ptr<as::posix::stream_descriptor> mRead = unique_ptr<as::posix::stream_descriptor>(
            new as::posix::stream_descriptor(io_service1, ad));
    mRead->non_blocking(true);
    mWrite->non_blocking(true);
    io_service1.run();
    for (;;) {

        boost::asio::streambuf write_buffer;
        std::ostream output(&write_buffer);
        std::string d;
        getline(std::cin, d);
        output <<d + "\n";
        std::cout << "Writing: " << make_string(write_buffer) << std::endl;
        boost::asio::write(*mWrite, write_buffer);

        sleep(1);

        boost::asio::streambuf read_buffer;
        boost::asio::read_until(*mRead, read_buffer, kFileNameSepator);
        std::cout << "Read: " << make_string(read_buffer) << std::endl;

    }
}