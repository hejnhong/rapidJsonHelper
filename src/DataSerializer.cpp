# include "DataSerializer.h"

std::string DataSerializer::serialize(JsonSeriaLizable *obj) {
    buf.Clear();
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer;
    writer.Reset(buf);
    writer.StartObject();

    rapidjson::Value rootNode;

    SerializeUtil serializeUtil;
    serializeUtil.init(writer, rootNode);
    obj->toJson(&serializeUtil);

    writer.EndObject();

    return buf.GetString();
}

void DataSerializer::deserialize(JsonSeriaLizable *obj) {

}