#ifndef SERIALIZE_UTIL_H
#define SERIALIZE_UTIL_H

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

#include <iostream>
#include <string>
#include <type_traits>

class SerializeUtil {
public:
    template <typename T>
    void writeItem(std::string key, T value);

    void init(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, rapidjson::Value &node);
private:
    void reset();

	rapidjson::PrettyWriter<rapidjson::StringBuffer> *writer = nullptr;
    rapidjson::Value *curNode = nullptr;
};

template <typename T>
void SerializeUtil::writeItem(std::string key, T value) {
    std::cout << key << ": " << value << std::endl;
    writer->Key(key.c_str());
    if constexpr (std::is_integral_v<T>) {
        writer->Int(value);
    } else if constexpr (std::is_floating_point_v<T>) {
        writer->Double(value);
    } else if constexpr (std::is_same_v<T, std::string>) {
        writer->String(value);
    }
}

#endif // SERIALIZE_UTIL_H