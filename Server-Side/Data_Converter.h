#pragma once
#include <map>
#include <utility>
#include <string.h>
#include <vector>

class Data_Converter
{
    public:
        Data_Converter();
        std::map<std::string, std::string> parsePayloadToMap(std::string delimiter, std::string rawData);
        std::pair<std::string, std::string> parsePayloadToPair(std::string delimiter, std::string rawData);
        std::vector<std::string> parsePayloadToVector(std::string delimiter, std::string rawData);

    protected:

    private:
};

