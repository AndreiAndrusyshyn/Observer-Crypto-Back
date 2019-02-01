#ifndef LAMPORT_FILE_GENERATOR_H
#define LAMPORT_FILE_GENERATOR_H

#include "../../include/includes.h"

class file_generator
{
public:
    file_generator();
    void add_claim();
    void read_claim();
    void make_buffer();
    void add_stack();
private:
    uint64_t block_number = 5, user_amount = 4, get_block, get_user_amount;
    boost::uuids::string_generator gen;
    boost::uuids::uuid block_uuid = gen("{11234567-1234-1234-0123-123456abcdef}"), get_block_uuid;;
    std::vector<PrivateKey *> private_keys;
    std::vector<uint16_t> ids;
    byte buffer[sizeof(uint16_t) * sizeof(uint16_t) + sizeof(boost::uuids::uuid) + (sizeof(user_amount) * (sizeof(uint16_t)))];
};
#endif //LAMPORT_FILE_GENERATOR_H
