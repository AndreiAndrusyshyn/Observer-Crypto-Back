#include "validator.h"

validator::validator(const char* file_name)
{
    sodium_init();

    std::ifstream readFILE(file_name, std::ios::binary);

    read_claim(readFILE);
    read_stack(readFILE);
    readFILE.close();

    make_buffer();
    validation();
};

void validator::read_claim(ifstream& infile)
{
    infile.read((char *) &claim_block_number, sizeof(uint64_t));
    infile.read((char *) &claim_uuid, sizeof(boost::uuids::uuid));
    infile.read((char *) &claim_user_amount, sizeof(uint16_t));

    for (int i = 0; i < claim_user_amount;) {
        infile.read((char *) &ID, sizeof(ID));
        paymentID.push_back(ID);
        infile.read((char *) buffer_public_keys, PublicKey::kKeySize());
        publicKeys.push_back(buffer_public_keys);
        i++;
    }
}

void validator::read_stack(ifstream& infile)
{
    infile.read((char *) &stack_block_number, sizeof(uint64_t));
    infile.read((char *) &stack_uuid, sizeof(boost::uuids::uuid));
    infile.read((char *) &stack_user_amount, sizeof(uint16_t));


    for (int i = 0; i < claim_user_amount;) {
        infile.read((char *) &ID, sizeof(ID));
        paymentID.push_back(ID);
        infile.read((char *) buffer_signature, Signature::signatureSize());
        signatures.push_back(buffer_signature);
        i++;
    }
}

void validator::make_buffer()
{
    std::ofstream writeFILE("buffer_reference_data.txt", std::ios::binary);
    writeFILE.write((char*)&claim_block_number, sizeof(claim_block_number));
    writeFILE.write((char*)&claim_uuid, sizeof(claim_uuid));
    writeFILE.write((char*)&claim_user_amount, sizeof(claim_user_amount));

    for(uint16_t i = 0; i < claim_user_amount;)
    {
        writeFILE.write((char*)&paymentID[i], sizeof(uint16_t));
        i++;
    }

    writeFILE.close();
    std::ifstream readFIle("buffer_reference_data.txt", std::ios::binary);
    readFIle.read((char*)buffer_reference_data, sizeof(buffer_reference_data));
    readFIle.close();
    remove("buffer_reference_data.txt");
};

void validator::validation()
{
    try
    {
        for (uint16_t i = 0; i < claim_user_amount;)
        {

            Signature ziga_zaga(signatures[i]);
            auto hello = make_shared<PublicKey>(publicKeys[i]);
            if (ziga_zaga.check(buffer_reference_data, sizeof(buffer_reference_data), hello) == 0) { throw 1; };

            i++;
        }
    }
    catch (int x)
    {
        std::cerr<<"DATA IS CORRUPTED!";
        std::abort();
    }
    std::cerr<<"Data is OK";
}




