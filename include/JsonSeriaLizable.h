#ifndef JSON_SERIALIZABLE_H
#define JSON_SERIALIZABLE_H

#include "DataSerializer.h"

class JsonSeriaLizable {
public:
    void virtual toJson(DataSerializer *serializer) = 0;
    void virtual fromJson(DataSerializer *serializer) = 0;

    ~JsonSeriaLizable() {}
};
#endif // JSON_SERIALIZABLE_H