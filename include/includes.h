#ifndef LAMPORT_INCLUDES_H
#define LAMPORT_INCLUDES_H

#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/signals2.hpp>

#include <sodium.h>
#include "../crypto/src/lamportscheme.h"

using namespace std;
namespace as = boost::asio;
namespace fs = boost::filesystem;
namespace signals = boost::signals2;

typedef uint8_t byte;
static const constexpr char kFileNameSepator = '\n';
using namespace crypto::lamport;

#endif //LAMPORT_INCLUDES_H
