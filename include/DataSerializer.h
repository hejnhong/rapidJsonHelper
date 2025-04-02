#ifndef DATA_SERIALIZER_H
#define DATA_SERIALIZER_H

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

#include <string>
#include <type_traits>

class JsonSeriaLizable;

class DataSerializer {
public:
    template <typename T>
    void writeItem(std::string key, T value);
};

template <typename T>
void DataSerializer::writeItem(std::string key, T value) {

}

#endif // DATA_SERIALIZER_H