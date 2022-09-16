#include "Data_Parser_And_Converter.h"
Data_Parser_And_Converter::Data_Parser_And_Converter() {

}


std::map<std::string, std::string> Data_Parser_And_Converter::parseDataThenConvertToMap(std::string delimiter, std::string rawData) {

}

std::pair<std::string, std::string> Data_Parser_And_Converter::parseDataThenConvertToPair(std::string delimiter, std::string rawData) {
    std::pair<std::string, std::string> parsedPair;
    std::string delim = delimiter;
    int delimLocation = rawData.find(delim);

    parsedPair.first = rawData.substr(0, delimLocation);
    parsedPair.second = rawData.substr(delimLocation + 1, rawData.length());

    return parsedPair;
}

std::vector<std::string> Data_Parser_And_Converter::parseDataThenConvertToVector(std::string delimiter, std::string rawData) {

}