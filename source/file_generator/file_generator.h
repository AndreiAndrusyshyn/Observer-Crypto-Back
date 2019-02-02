#ifndef LAMPORT_FILE_GENERATOR_H
#define LAMPORT_FILE_GENERATOR_H

#include "../../include/includes.h"

class file_generator
{
public:
    file_generator();
    void set_random();
    void add_claim();
    void read_claim();
    void make_buffer();
    void add_stack();
private:
    uint64_t block_number, get_block;
    uint16_t user_amount, get_user_amount;
    boost::uuids::random_generator gen;
    boost::uuids::uuid block_uuid = gen(), get_block_uuid;
    std::vector<PrivateKey *> private_keys;
    std::vector<uint16_t> ids;
    byte *buffer = new byte[sizeof(uint16_t) * sizeof(uint16_t) + sizeof(boost::uuids::uuid) + ((user_amount) * (sizeof(uint16_t)))];
};
#endif //LAMPORT_FILE_GENERATOR_H
