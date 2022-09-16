// gaurd to prevent including file many time.
#pragma once

// headers
#include <string>
#include <map>
#include <utility>
#include <vector>

// class prototype
class Data_Parser_And_Converter
{
    public:
        Data_Parser_And_Converter();
        static std::map<std::string, std::string> parseDataThenConvertToMap(std::string delimiter, std::string rawData);
        static std::pair<std::string, std::string> parseDataThenConvertToPair(std::string delimiter, std::string rawData);
        static std::vector<std::string> parseDataThenConvertToVector(std::string delimiter, std::string rawData);

    protected:

    private:
};

