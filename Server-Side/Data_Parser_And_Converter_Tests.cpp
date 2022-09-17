#include "Data_Parser_And_Converter_Tests.h"
#include "Data_Parser_And_Converter.h"
#include "../gtest/gtest.h"


Data_Parser_And_Converter_Tests::Data_Parser_And_Converter_Tests() {
    RUN_ALL_TESTS();
}
// test map converter
TEST(DataParserAndConverter, PositiveMapConverter) {
    std::map<std::string , std::string> testedMap = Data_Parser_And_Converter::parseDataThenConvertToMap("," , "::" , "Name::Ahmed,Age::27");
    EXPECT_EQ(testedMap["Name"], "Ahmed");
    EXPECT_EQ(testedMap["Age"], "27");
    EXPECT_EQ(testedMap.size(), 2);
}

TEST(DataParserAndConverter, PositiveMapConverterNoFirstDelimiterInString) {
    std::map<std::string, std::string> testedMap = Data_Parser_And_Converter::parseDataThenConvertToMap(",", "::", "Age::27");
    EXPECT_EQ(testedMap["Age"], "27");
    EXPECT_EQ(testedMap.size(), 1);
}

TEST(DataParserAndConverter, PositiveMapConverterNoDelimitersInString) {
    std::map<std::string, std::string> testedMap = Data_Parser_And_Converter::parseDataThenConvertToMap(",", "::", "Age");
    EXPECT_EQ(testedMap["Age"], "");
    EXPECT_EQ(testedMap.size(), 1);
}

TEST(DataParserAndConverter, PositiveMapConverterNoString) {
    std::map<std::string, std::string> testedMap = Data_Parser_And_Converter::parseDataThenConvertToMap(",", "::", "");
    EXPECT_EQ(testedMap.size(), 0);
}

// test pair converter
TEST(DataParserAndConverter, PositivePairConverter) {
    std::pair<std::string, std::string> testedPair = Data_Parser_And_Converter::parseDataThenConvertToPair("::", "Name::Ahmed");
    EXPECT_EQ(testedPair.first, "Name");
    EXPECT_EQ(testedPair.second, "Ahmed");
}

TEST(DataParserAndConverter, PositivePairConverterManyDelimiterInString) {
    std::pair<std::string, std::string> testedPair = Data_Parser_And_Converter::parseDataThenConvertToPair("::", "Name::Ahmed::Eldakhly");
    EXPECT_EQ(testedPair.first, "Name");
    EXPECT_EQ(testedPair.second, "Ahmed::Eldakhly");
}

TEST(DataParserAndConverter, PositivePairConverterNoDelimitersInString) {
    std::pair<std::string, std::string> testedPair = Data_Parser_And_Converter::parseDataThenConvertToPair("::", "Eldakhly");
    EXPECT_EQ(testedPair.first, "Eldakhly");
    EXPECT_EQ(testedPair.second, "");
}

TEST(DataParserAndConverter, PositivePairConverterNoString) {
    std::pair<std::string, std::string> testedPair = Data_Parser_And_Converter::parseDataThenConvertToPair(",", "");
    EXPECT_EQ(testedPair.first, "");
    EXPECT_EQ(testedPair.second, "");
}

TEST(DataParserAndConverter, PositivePairConverterNoString) {
    std::pair<std::string, std::string> testedPair = Data_Parser_And_Converter::parseDataThenConvertToPair(",", "");
    EXPECT_EQ(testedPair.first, "");
    EXPECT_EQ(testedPair.second, "");
}

TEST(DataParserAndConverter, NegativePairConverterWrongDelimiter) {
    std::pair<std::string, std::string> testedPair = Data_Parser_And_Converter::parseDataThenConvertToPair(",", "Name::Eldakhly");
    EXPECT_EQ(testedPair.first, "Name::Eldakhly");
    EXPECT_EQ(testedPair.second, "");
}

// test vector converter
TEST(DataParserAndConverter, PositiveVectorConverter) {
    std::vector<std::string> testedvector = Data_Parser_And_Converter::parseDataThenConvertToVector(",", "Ahmed,Abdaalah,Eldakhly");
    EXPECT_EQ(testedvector[0], "Ahmed");
    EXPECT_EQ(testedvector[1], "Abdallah");
    EXPECT_EQ(testedvector[2], "Eldakhly");
    EXPECT_EQ(testedvector.size(), 3);
}

TEST(DataParserAndConverter, NegativeVectorConverterWrongDelimiter) {
    std::vector<std::string> testedvector = Data_Parser_And_Converter::parseDataThenConvertToVector("::", "Ahmed,Abdaalah,Eldakhly");
    EXPECT_EQ(testedvector[0], "Ahmed,Abdaalah,Eldakhly");
    EXPECT_EQ(testedvector.size(), 1);
}

TEST(DataParserAndConverter, NegativeVectorConverterEmptyString) {
    std::vector<std::string> testedvector = Data_Parser_And_Converter::parseDataThenConvertToVector("::", "");
    EXPECT_EQ(testedvector.size(), 0);
}