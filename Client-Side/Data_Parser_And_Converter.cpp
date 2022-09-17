#include "Data_Parser_And_Converter.h"

/// <summary>
/// 
/// </summary>
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
    if (!rawData.length())
    {
        return parsedMap;
    }
    
    rawData = rawData.append(delimiter);
    std::string tempString;
    long position = 0;
    while ((position = rawData.find(delimiter)) != std::string::npos) {
        // store the substring
        tempString = rawData.substr(0, position);
        int keyDelimiterLocation = rawData.find(keyValueDelimiter);
        if (keyDelimiterLocation == std::string::npos)
        {
            parsedMap.insert({ tempString, "" });
        }else {
            parsedMap.insert({ tempString.substr(0, keyDelimiterLocation), tempString.substr(keyDelimiterLocation + keyValueDelimiter.length(), tempString.length()) });
        }
        
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
    if (delimiterLocation == std::string::npos){
        delimiterLocation = rawData.length();
        parsedPair.first = rawData.substr(0, delimiterLocation);
        parsedPair.second = "";
    }else {
        parsedPair.first = rawData.substr(0, delimiterLocation);
        parsedPair.second = rawData.substr(delimiterLocation + delimiter.length(), rawData.length());
    } 

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
    if (!rawData.length())
    {
        return parsedVector;
    }
    rawData = rawData.append(delimiter);
    int delimiterLocation;
    while ((delimiterLocation = rawData.find(delimiter)) != std::string::npos) {
        // store the substring
        parsedVector.push_back(rawData.substr(0, delimiterLocation));
        rawData.erase(0, delimiterLocation + delimiter.length());
    }

    return parsedVector;
}