#pragma once
class Data_Converter
{
    public:
        Data_Converter();
        map<string, string> parsePayloadToMap(string delimiter, string rawData);
        pair<string, string> parsePayloadToPair(string delimiter, string rawData);
        vector<string> parsePayloadToVector(string delimiter, string rawData);

    protected:

    private:
};

