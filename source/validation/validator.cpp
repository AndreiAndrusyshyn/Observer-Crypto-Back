#include "validator.h"

validator::validator(const char* file_name)
{
        sodium_init();
        std::ifstream readFILE(file_name, std::ios::binary);
        read_claim(readFILE);
        read_stack(readFILE);
        readFILE.close();
        check(file_name);
        make_buffer();
        if(status != 255){validation();}
        remove(file_name);
};

validator::~validator()
{
    delete[] buffer_signature;
    delete[] buffer_public_keys;
    delete[] buffer_reference_data;
}

uint16_t validator::return_answer(){ return status; }


void validator::check_status(string check)
{
    if(check == "OK")
    {
       status = 0; }
    else if(check == "PASS")
    {
       status = 1;
    }
    else if(check == "FAILED")
    {
        status = 255;
    }
}

void validator::read_claim(ifstream& infile)
{
    infile.read((char *) &claim_block_number, sizeof(uint64_t));
    infile.read((char *) &claim_uuid, sizeof(boost::uuids::uuid));
    infile.read((char *) &claim_user_amount, sizeof(uint16_t));

    for (int i = 0; i < claim_user_amount;)
    {
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

    for (int i = 0; i < claim_user_amount;)
    {
        infile.read((char *) &ID, sizeof(ID));
        paymentID.push_back(ID);
        infile.read((char *) buffer_signature, Signature::signatureSize());
        signatures.push_back(buffer_signature);
        i++;
    }
}

void validator::check(const char *file)
{
    try
    {
        if (claim_block_number != stack_block_number) { remove(file);throw 1;}
        else if(claim_uuid != stack_uuid) { remove(file); throw 2; }
        else if(claim_user_amount != stack_user_amount) {  remove(file); throw 3; }
        else if(paymentID[0] != 0) {remove(file);throw 4; }
        else if(paymentID[(paymentID.size()/2)] != paymentID[0]) {remove(file); throw 5; }
        else {check_status("OK");}

    }
    catch (int x)
    {
        switch (x)
        {

            case 1: std::cerr<<"Block numbers are not equal!"<<"\n"; check_status("FAILED");break;
            case 2: std::cerr<<"UUID are not equal!"<<"\n"; check_status("FAILED");break;
            case 3: std::cerr<<"Amount of users are not equal!"<<"\n";check_status("FAILED");break;
            case 4: std::cerr<<"Payment id starts not from 0!"<<"\n"; check_status("FAILED");break;
            case 5: std::cerr<<"Payment id starts not equal!"<<"\n"; check_status("FAILED");break;
            default: std::cout<<"Check complete"<<"\n";
        }
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
            Signature sig(signatures[i]);
            auto hello = make_shared<PublicKey>(publicKeys[i]);
            if (sig.check(buffer_reference_data, sizeof(buffer_reference_data), hello) == 0) { throw 11; };
            i++;
        }
    }
    catch (int x)
    {
        std::cerr<<"DATA IS CORRUPTED!"<<"\n";
    }
    std::cout<<"Data is OK"<<"\n";
    check_status("PASS");

}




