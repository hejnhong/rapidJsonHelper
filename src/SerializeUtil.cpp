#include "SerializeUtil.h"

void SerializeUtil::reset() {
}

void SerializeUtil::init(rapidjson::PrettyWriter<rapidjson::StringBuffer> &_writer,
                         rapidjson::Value &node) {
    writer = &_writer;
    curNode = &node;                
}

void SerializeUtil::setCurNode(rapidjson::Value &node) {
    curNode = &node;
}