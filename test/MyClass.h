#ifndef MY_CLASS_H
#define MY_CLASS_H

#include "JsonSeriaLizable.h"
#include "SubClass.h"

#include <string>
#include <vector>

class MyClass : public JsonSeriaLizable
{
public:
    MyClass();

    void fromJson(SerializeUtil *serializeUtil) override;
    void toJson(SerializeUtil *serializeUtil) const override;

private:
    int id;
    std::string name;
    SubClass subClass;
    std::vector<std::string> list;
};

#endif // MY_CLASS_H