#ifndef SERIALIZE_UTIL_H
#define SERIALIZE_UTIL_H

// #include "JsonSeriaLizable.h"
class JsonSeriaLizable;

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

#include <iostream>
#include <string>
#include <type_traits>

class SerializeUtil {
public:
    template <typename T>
    void writeItem(const std::string &key, const T &item);

    template <typename T>
    void writeList(const std::string &key, const std::vector<T> &list);


    void init(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, rapidjson::Value &node);
private:
    void reset();

    template <typename T>
    void writeValue(const T &value);

	rapidjson::PrettyWriter<rapidjson::StringBuffer> *writer = nullptr;
    rapidjson::Value *curNode = nullptr;
};

template <typename T>
void SerializeUtil::writeValue(const T &value) {
    if constexpr (std::is_integral_v<T>) {
        writer->Int(value);
    } else if constexpr (std::is_floating_point_v<T>) {
        writer->Double(value);
    } else if constexpr (std::is_same_v<T, std::string>) {
        writer->String(value.c_str());
    } else if constexpr (std::is_same_v<T, bool>) {
        writer->Bool(value);
    } else if constexpr (std::is_same_v<T, char>) {
        writer->String(value);
    } else if constexpr (std::is_enum_v<T>) {
        writer->Int(static_cast<int>(value));
    }else if constexpr (std::is_same_v<std::decay_t<T>, const char*>
                        || std::is_same_v<std::decay_t<T>, char*>) {
        if (value) {
            writer->String(value);
        }
    } else if constexpr (std::is_pointer_v<std::decay_t<T>>) {
        using RawType = std::remove_pointer_t<std::decay_t<T>>;
        if constexpr (std::is_base_of_v<JsonSeriaLizable, RawType>) {
            if (value) {
                writer->StartObject();
                value->toJson(this);
                writer->EndObject();
            } else {
                writer->Null();
            }
        } else {
            std::cout << "Not a JsonSeriaLizable pointer." << std::endl;
        }
    }
}

template <typename T>
void SerializeUtil::writeItem(const std::string &key, const T &item) {
    std::cout <<"writeItem, " << key << ": " << value << std::endl;
    writer->Key(key.c_str());
    writeValue(item);
}

template <typename T>
void SerializeUtil::writeList(const std::string &key, const std::vector<T> &list) {
    writer->Key(key.c_str());
    writer->StartArray();
    for (const auto &item : list) {
        writeValue(item);
    }
    writer->EndArray();
}

#endif // SERIALIZE_UTIL_H