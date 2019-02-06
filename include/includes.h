#ifndef LAMPORT_INCLUDES_H
#define LAMPORT_INCLUDES_H

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#include <sodium.h>
#include "../crypto/src/lamportscheme.h"

using namespace crypto::lamport;

#endif //LAMPORT_INCLUDES_H
