#ifndef SUB_CLASS_H
#define SUB_CLASS_H

#include "JsonSeriaLizable.h"

class SubClass : public JsonSeriaLizable
{
public:
    SubClass();

    void fromJson(SerializeUtil *serializeUtil) override;
    void toJson(SerializeUtil *serializeUtil) override;

private:
    int id;
    std::string name;
};

#endif // SUB_CLASS_H