#include "Data_Parser_And_Converter.h"
Data_Parser_And_Converter::Data_Parser_And_Converter() {

}

/// <summary>
/// 
/// </summary>
/// <param name="delimiter"></param>
/// <param name="keyValueDelimiter"></param>
/// <param name="rawData"></param>
/// <returns></returns>
std::map<std::string, std::string> Data_Parser_And_Converter::parseDataThenConvertToMap(std::string delimiter, std::string keyValueDelimiter, std::string rawData) {

    std::map<std::string, std::string> parsedMap;

    // solution 1 without using vector converter and pair converter
    rawData = rawData.append(",");
    long position = 0;
    std::string tempString;

    while ((position = rawData.find(delimiter)) != std::string::npos) {
        // store the substring
        tempString = rawData.substr(0, position);
        int keyDelimiterLocation = rawData.find(keyValueDelimiter);
        parsedMap.insert({ tempString.substr(0, keyDelimiterLocation), tempString.substr(keyDelimiterLocation + 1, tempString.length()) });
        rawData.erase(0, position + delimiter.length());
    }

    

   // sloution 2 using vector and pair converters
    /*std::vector<std::string> dataAsVector = parseDataThenConvertToVector(delimiter, rawData);
    std::pair<std::string, std::string> subStringAsPair;
    for (std::string subString : dataAsVector) {
        subStringAsPair = parseDataThenConvertToPair(keyValueDelimiter, subString);
        parsedMap.insert(subStringAsPair.first, subStringAsPair.second);
    }*/

    return parsedMap;
}

/// <summary>
/// 
/// </summary>
/// <param name="delimiter"></param>
/// <param name="rawData"></param>
/// <returns></returns>
std::pair<std::string, std::string> Data_Parser_And_Converter::parseDataThenConvertToPair(std::string delimiter, std::string rawData) {
    std::pair<std::string, std::string> parsedPair;
    int delimiterLocation = rawData.find(delimiter);

    parsedPair.first = rawData.substr(0, delimiterLocation);
    parsedPair.second = rawData.substr(delimiterLocation + 1, rawData.length());

    return parsedPair;
}

/// <summary>
/// 
/// </summary>
/// <param name="delimiter"></param>
/// <param name="rawData"></param>
/// <returns></returns>
std::vector<std::string> Data_Parser_And_Converter::parseDataThenConvertToVector(std::string delimiter, std::string rawData) {
    std::vector<std::string> parsedVector;
    rawData = rawData.append(",");
    int delimiterLocation;
    while ((delimiterLocation = rawData.find(delimiter)) != std::string::npos) {
        // store the substring
        parsedVector.push_back(rawData.substr(0, delimiterLocation));
        rawData.erase(0, delimiterLocation + delimiter.length());
    }

    return parsedVector;
}