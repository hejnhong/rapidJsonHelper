# include "DataSerializer.h"

std::string DataSerializer::serialize(JsonSeriaLizable *obj) {
    buf.Clear();
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer;
    writer.Reset(buf);

    rapidjson::Value rootNode;

    SerializeUtil serializeUtil;
    serializeUtil.init(writer, rootNode);
    obj->toJson(&serializeUtil);

    return buf.GetString();
}

void DataSerializer::deserialize(JsonSeriaLizable *obj) {

}