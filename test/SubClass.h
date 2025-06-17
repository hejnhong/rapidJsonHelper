#ifndef SUB_CLASS_H
#define SUB_CLASS_H

#include "JsonSeriaLizable.h"

#include <string>

class SubClass : public JsonSeriaLizable
{
public:
    SubClass();
    SubClass(int age, const std::string &sex);

    void fromJson(SerializeUtil *serializeUtil) override;
    void toJson(SerializeUtil *serializeUtil) const override;

private:
    int age;
    std::string sex;
};

#endif // SUB_CLASS_H