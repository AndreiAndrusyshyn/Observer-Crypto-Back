#include "../../tests/catch.hpp"
#include "../../validation/Validator.cpp"
#include "../TestDataGenerator/TestDataGenerator.cpp"

TEST_CASE("GENERATE TEST FILES")
{
   REQUIRE(Validator(testDataGenerator().differenClaimAndStackAmountNumbers()).check() == "255");

    REQUIRE(Validator(testDataGenerator().differenClaimAndStackBlockNumbers()).check() == "255");

    REQUIRE(Validator(testDataGenerator().differenClaimAndStackPaymentID()).check() == "255");

    REQUIRE(Validator(testDataGenerator().differenClaimAndStackUUID()).check() == "255");

    REQUIRE(Validator(testDataGenerator().corruptedSignatures()).check() == "255");

   REQUIRE(Validator(testDataGenerator().corruptedPublickKeys()).check() == "255");

  // REQUIRE(Validator(TestDataGenerator().corruptedBuffer()).check() == "255");
}