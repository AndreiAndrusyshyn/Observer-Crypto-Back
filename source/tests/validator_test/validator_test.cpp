#include "../../tests/catch.hpp"
#include "../../validation/validator.h"
#include "../../validation/validator.cpp"
#include "../../tests/test_file_generator/test_file_generator.h"
#include "../../tests/test_file_generator/test_file_generator.cpp"

TEST_CASE("GENERATE TEST FILES")
{
    SECTION("FILE IS OK")
    {
        REQUIRE_NOTHROW(validator(test_file_generator().make_file_name()));
    }

    SECTION("DIFFERENT BLOCK NUMBERK ")
    {
        REQUIRE(validator(test_file_generator("different block number", 21).make_file_name()).return_answer() == 255);
    }

    SECTION("DIFFERENT USER AMOUNT")
    {
        REQUIRE(validator(test_file_generator("different user amount", 22).make_file_name()).return_answer() == 255);
    }

    SECTION("DIFFERENT UUID")
    {
        REQUIRE(validator(test_file_generator("11111121-9999-8888-7777-123456789012").make_file_name()).return_answer() == 255);
    }

    SECTION("DIFFERENT PAYMENT ID")
    {
        REQUIRE(validator(test_file_generator("broken payment id", 23).make_file_name()).return_answer() == 255);
    }

    SECTION("PAYMENT ID START WITH VALUE DIFFERENT FROM 0")
    {
        REQUIRE(validator(test_file_generator("broken start of payment id", 24).make_file_name()).return_answer() == 255);
    }
}

