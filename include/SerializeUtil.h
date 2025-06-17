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
#include <vector>

class SerializeUtil {
public:
    template <typename T>
    void writeItem(const std::string &key, const T &item);

    template <typename T>
    void readItem(const std::string &key, T &item);

    template <typename T>
    void writeList(const std::string &key, const std::vector<T> &list);

    template <typename T>
    void readList(const std::string &key, std::vector<T> &list);



    void init(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, rapidjson::Value &node);
    void setCurNode(rapidjson::Value &node);
private:
    void reset();

    template <typename T>
    void writeValue(const T &value);

    template <typename T>
    void readValue(rapidjson::Value &node, T &value);

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
    } else if constexpr (std::is_object_v<T>) {
        if (std::is_base_of_v<JsonSeriaLizable, T>) {
            writer->StartObject();
            value.toJson(this);
            writer->EndObject();
        }
    }
}

template <typename T>
void SerializeUtil::writeItem(const std::string &key, const T &item) {
    std::cout <<"writeItem: " << key << std::endl;
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

template <typename T>
void SerializeUtil::readValue(rapidjson::Value &node, T &value) {
    if constexpr (std::is_integral_v<T>) {
        value = node.GetInt();
    } else if constexpr (std::is_floating_point_v<T>) {
        value = node.GetDouble();
    } else if constexpr (std::is_same_v<T, std::string>) {
        value = node.GetString();
    } else if constexpr (std::is_same_v<T, bool>) {
        value = node.GetBool();
    } else if constexpr (std::is_same_v<T, char>) {
        value = node.GetString()[0];
    } else if constexpr (std::is_enum_v<T>) {
        value = static_cast<T>(node.GetInt());
    } else if constexpr (std::is_same_v<std::decay_t<T>, const char*>
                         || std::is_same_v<std::decay_t<T>, char*>) {
        if (node.IsString()) {
            value = node.GetString();
        } else {
            value = nullptr;
        }
    } else if constexpr (std::is_pointer_v<std::decay_t<T>>) {
        using RawType = std::remove_pointer_t<std::decay_t<T>>;
        if constexpr (std::is_base_of_v<JsonSeriaLizable, RawType>) {
            if (node.IsObject()) {
                if (!value) {
                    value = new RawType();
                }

                auto tmp = curNode;
                curNode = &node;
                value->fromJson(this);
                curNode = tmp;
            } else {
                std::cout<<"not a json object."<<std::endl;
            }
        } else {
            std::cout << "Not a JsonSeriaLizable pointer." << std::endl;
        }
    } else if constexpr (std::is_object_v<T>) {
        if (std::is_base_of_v<JsonSeriaLizable, T>) {
            if (node.IsObject()) {
                auto tmp = curNode;
                curNode = &node;
                value.fromJson(this);
                curNode = tmp;
            }
        }
    }
}

template <typename T>
void SerializeUtil::readItem(const std::string &key, T &item) {
    std::cout <<"readItem: " << key << std::endl;
    if (curNode != nullptr && curNode->HasMember(key.c_str())) {
        readValue((*curNode)[key.c_str()], item);
    }
}

template <typename T>
void SerializeUtil::readList(const std::string &key, std::vector<T> &list) {
    std::cout <<"readList: " << key << std::endl;
    if (curNode != nullptr && curNode->HasMember(key.c_str()) && curNode->IsArray()) {
        for (auto &item : (*curNode)[key.c_str()].GetArray()) {
            T value;
            readValue(item, value);
            list.emplace_back(value);
        }
    }
}

#endif // SERIALIZE_UTIL_H