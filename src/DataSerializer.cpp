#include "DataSerializer.h"
#include "JsonSeriaLizable.h"

std::string DataSerializer::serialize(JsonSeriaLizable *obj) {
    obj->toJson(this);
}

void DataSerializer::reset() {
    buf.Clear();
    writer.Reset(buf);
    doc.Clear();
    curNode = nullptr;
}