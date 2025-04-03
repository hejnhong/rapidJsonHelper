#ifndef DATA_SERIALIZER_H
#define DATA_SERIALIZER_H

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

#include <iostream>
#include <string>
#include <type_traits>

class JsonSeriaLizable;

class DataSerializer {
public:
    std::string serialize(JsonSeriaLizable *obj);

    template <typename T>
    void writeItem(std::string key, T value);
};

template <typename T>
void DataSerializer::writeItem(std::string key, T value) {
    std::cout << key << ": " << value << std::endl;
}

#endif // DATA_SERIALIZER_H