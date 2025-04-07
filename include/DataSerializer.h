#ifndef DATA_SERIALIZER_H
#define DATA_SERIALIZER_H

#include "JsonSeriaLizable.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

class DataSerializer
{
public:
    void serialize(JsonSeriaLizable *obj);
    void deserialize(JsonSeriaLizable *obj);

private:
    rapidjson::Document doc;
    rapidjson::StringBuffer buf;
};

#endif