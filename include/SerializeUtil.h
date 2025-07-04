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
#include <unordered_map>

class SerializeUtil {
public:
    template <typename T>
    void writeItem(const std::string &key, const T &item);

    template <typename T>
    void writeList(const std::string &key, const std::vector<T> &list);

    template <typename T>
    void writeList(const std::string &key, const std::vector<std::vector<T>> &list);

    template <typename T>
    void writeMap(const std::string &key, const std::unordered_map<std::string, T> &map);

    template <typename T>
    void readItem(const std::string &key, T &item);

    template <typename T>
    void readList(const std::string &key, std::vector<T> &list);

    template <typename T>
    void readList(const std::string &key, std::vector<std::vector<T>> &list);

    template <typename T>
    void readMap(const std::string &key, std::unordered_map<std::string, T> &map);

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
    // std::cout <<"writeItem: " << key << std::endl;
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
void SerializeUtil::writeList(const std::string &key, const std::vector<std::vector<T>> &list) {
    writer->Key(key.c_str());
    writer->StartArray();
    for (const auto &subList : list) {
        writer->StartArray();
        for (const auto &item : subList) {
            writeValue(item);
        }
        writer->EndArray();
    }
    writer->EndArray();
}

template <typename T>
void SerializeUtil::writeMap(const std::string &key, const std::unordered_map<std::string, T> &map) {
    writer->Key(key.c_str());
    writer->StartObject();
    for (const auto &[key, value] : map) {
        writeItem(key, value);
    }
    writer->EndObject();
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
    // std::cout <<"readItem: " << key << std::endl;
    if (!curNode || !curNode->IsObject() || !curNode->HasMember(key.c_str())) {
        return;
    }

    readValue((*curNode)[key.c_str()], item);
}

template <typename T>
void SerializeUtil::readList(const std::string &key, std::vector<T> &list) {
    // std::cout <<"readList: " << key << std::endl;
    if (!curNode || !curNode->IsObject() || !curNode->HasMember(key.c_str())) {
        return;
    }
    if (!(*curNode)[key.c_str()].IsArray()) {
        return;
    }
    for (auto &node : (*curNode)[key.c_str()].GetArray()) {
        T value;
        readValue(node, value);
        list.emplace_back(std::move(value));
    }
}

template <typename T>
void SerializeUtil::readList(const std::string &key, std::vector<std::vector<T>> &list) {
    // std::cout <<"readList: " << key << std::endl;
    if (!curNode || !curNode->IsObject() || !curNode->HasMember(key.c_str())) {
        return;
    }
    if (!(*curNode)[key.c_str()]->IsArray()) {
        return;
    }
    for (auto &arrayNode : (*curNode)[key.c_str()].GetArray()) {
        std::vector<T> subList;
        if (arrayNode.IsArray()) {
            for (auto &node : arrayNode.GetArray()) {
                T value;
                readValue(node, value);
                subList.emplace_back(std::move(value));
            }
        }
        list.emplace_back(std::move(subList));
    }
}

template <typename T>
void SerializeUtil::readMap(const std::string &key, std::unordered_map<std::string, T> &map) {
    if (curNode == nullptr || !curNode->IsObject() || !curNode->HasMember(key.c_str())) {
        return;
    }
    auto &jsonMap = curNode->GetObject()[key.c_str()];
    for (auto it = jsonMap.MemberBegin(); it != jsonMap.MemberEnd(); ++it) {
        std::pair<std::string, T> pair;
        pair.first = it->name.GetString();
        readValue(it->value, pair.second);
        map.emplace(std::move(pair))
    }
}

#endif // SERIALIZE_UTIL_H