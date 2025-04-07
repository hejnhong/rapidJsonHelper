#ifndef JSON_SERIALIZABLE_H
#define JSON_SERIALIZABLE_H

#include "SerializeUtil.h"

class JsonSeriaLizable {
public:
    void virtual toJson(SerializeUtil *serializeUtil) = 0;
    void virtual fromJson(SerializeUtil *serializeUtil) = 0;

    ~JsonSeriaLizable() {}
};
#endif // JSON_SERIALIZABLE_H