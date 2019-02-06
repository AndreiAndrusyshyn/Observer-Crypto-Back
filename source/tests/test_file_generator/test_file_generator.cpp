#include "test_file_generator.h"

test_file_generator::test_file_generator()
{
    sodium_init();
    make_file_name();
    set_random();
    add_claim(char_file_name);
    read_claim(char_file_name);
    make_buffer();
    add_stack(char_file_name);
};

test_file_generator::test_file_generator(string test_case, uint64_t stack_number)
{
    sodium_init();
    make_file_name();
    if (test_case == "different block number")
    {
        set_random();
        add_claim(char_file_name);
        read_claim(char_file_name);
        make_buffer();
        change_numb(test_case, stack_number);
        add_stack(char_file_name);
    }
    else if (test_case == "different user amount")
    {
        set_random();
        add_claim(char_file_name);
        read_claim(char_file_name);
        make_buffer();
        change_numb(test_case, stack_number);
        add_stack(char_file_name);
    }
    else if (test_case == "broken payment id")
    {
        set_random();
        add_claim(char_file_name);
        read_claim(char_file_name);
        make_buffer();
        change_numb(test_case, stack_number);
        add_stack(char_file_name);
    }
    else if(test_case == "broken start of payment id")
    {
        set_random();
        change_numb(test_case, stack_number);
        add_claim(char_file_name);
        read_claim(char_file_name);
        make_buffer();
        add_stack(char_file_name);
    }
}

test_file_generator::test_file_generator(string uuid)
{
    sodium_init();
    make_file_name();
    set_random();
    add_claim(char_file_name);
    read_claim(char_file_name);
    make_buffer();
    change_uuid(uuid);
    add_stack(char_file_name);
}

void test_file_generator::change_uuid(string uuid)
{
    get_block_uuid = gen(uuid);
}

void test_file_generator::change_numb(string t_case, uint64_t stack)
{
    if(t_case == "different block number"){ get_block = stack; }
    else if(t_case == "different user amount")
    {
        dumm_user_amount = stack;
    }
    else if (t_case == "broken payment id")
    {
        ids[0] = stack;
    }
    else if(t_case == "broken start of payment id")
    {
        dumm_ids[0] = stack;
    }
}

void test_file_generator::set_random()
{
    srand(time(NULL));
    block_number=1;
    user_amount = (rand()%1024+1);
    dumm_user_amount = user_amount;

    for(uint16_t i = 0; i<user_amount;)
    {
        dumm_ids.push_back(i);
        i++;
    }
}

void test_file_generator::add_claim(const char* file_name)
{
    std::ofstream writeFILE(file_name, std::ios::binary);
    writeFILE.write((char*)&block_number, sizeof(block_number));
    writeFILE.write((char*)&block_uuid, sizeof(block_uuid));
    writeFILE.write((char*)&user_amount, sizeof(user_amount));

    for(uint16_t i = 0;i < user_amount;)
    {
        PrivateKey *pKey = new PrivateKey();

        private_keys.push_back(pKey);

        auto pubKey = pKey->derivePublicKey()->data();
        writeFILE.write((char*)&dumm_ids[i], sizeof(uint16_t));
        writeFILE.write((char*)pubKey, PublicKey::kKeySize());
        ++i;
    }
    writeFILE.close();
};

void test_file_generator::read_claim(const char* file_name)
{
    std::ifstream readFILE(file_name, std::ios::binary);

    readFILE.read((char*)&get_block, sizeof(uint64_t));
    readFILE.seekg(sizeof(uint64_t));
    readFILE.read((char*)&get_block_uuid, sizeof(get_block_uuid));
    readFILE.read((char*)&get_user_amount, sizeof(get_user_amount));

    for(uint16_t i = 0; i < get_user_amount;){

        uint16_t id;
        readFILE.read((char*)&id, sizeof(uint16_t));
        ids.push_back(id);
        readFILE.seekg(PublicKey::kKeySize(), readFILE.cur);
        i++;
    }
    readFILE.close();
};

void test_file_generator::make_buffer()
{
    std::ofstream writeFILE("buffer_reference_data.txt", std::ios::binary);
    writeFILE.write((char*)&get_block, sizeof(get_block));
    writeFILE.write((char*)&get_block_uuid, sizeof(get_block_uuid));
    writeFILE.write((char*)&get_user_amount, sizeof(get_user_amount));

    for(uint16_t i = 0; i < get_user_amount;)
    {
        writeFILE.write((char*)&ids[i], sizeof(uint16_t));
        i++;
    }

    writeFILE.close();

    std::ifstream readFIle("buffer_reference_data.txt", std::ios::binary);

    readFIle.read((char*)buffer, sizeof(buffer));

    readFIle.close();
    remove("buffer_reference_data.txt");
};

void test_file_generator::add_stack(const char* file_name)
{
    std::ofstream writeFILE(file_name,std::ios::app );
    writeFILE.write((char*)&get_block, sizeof(block_number));
    writeFILE.write((char*)&get_block_uuid, sizeof(block_uuid));
    writeFILE.write((char*)&dumm_user_amount, sizeof(user_amount));

    for(uint16_t i = 0;i < get_user_amount;)
    {

        Signature sig(buffer, sizeof(buffer), private_keys[i]);
        auto signat = sig.data();

        writeFILE.write((char*)&ids[i], sizeof(uint16_t));
        writeFILE.write((char*)signat, Signature::signatureSize());

        ++i;
    }
    writeFILE.close();

};

const char* test_file_generator::make_file_name()
{
    file_name_generate_from_uuid = boost::lexical_cast<std::string>(block_uuid);
    file_name_generate_from_uuid+=".txt";
    char_file_name = file_name_generate_from_uuid.c_str();
    return char_file_name;
}
