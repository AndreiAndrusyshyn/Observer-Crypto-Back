#ifndef TEST_FILE_GENERATOR_H
#define TEST_FILE_GENERATOR_H

#include "../../../include/includes.h"

class test_file_generator
{
public:
    test_file_generator();
    test_file_generator(string test_case, uint64_t stack_number);
    test_file_generator(string uuid);
    void change_numb(string t_case, uint64_t d);
    void change_uuid(string uuid);
    void set_random();
    void add_claim(const char* file_name);
    void read_claim(const char* file_name);
    void make_buffer();
    void add_stack(const char* file_name);
    const char* make_file_name();
private:
    uint64_t block_number, get_block;
    uint16_t user_amount, get_user_amount, dumm_user_amount;
    boost::uuids::random_generator gen_rand;
    boost::uuids::string_generator gen;
    boost::uuids::uuid block_uuid = gen_rand(), get_block_uuid;
    std::vector<PrivateKey *> private_keys;
    std::vector<uint16_t> ids, dumm_ids;
    byte *buffer = new byte[sizeof(uint16_t) * sizeof(uint16_t) + sizeof(boost::uuids::uuid) + ((user_amount) * (sizeof(uint16_t)))];
    std::string file_name_generate_from_uuid;
    const char* char_file_name;
};
#endif //TEST_FILE_GENERATOR_H