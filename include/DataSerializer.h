#ifndef DATA_SERIALIZER_H
#define DATA_SERIALIZER_H

#include "JsonSeriaLizable.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

#include <string>

class DataSerializer
{
public:
    std::string serialize(JsonSeriaLizable *obj);
    void deserialize(const std::string &jsonStr, JsonSeriaLizable *obj);

private:
    rapidjson::Document doc;
    rapidjson::StringBuffer buf;
};

#endif