#ifndef MY_CLASS_H
#define MY_CLASS_H

#include "JsonSeriaLizable.h"

class MyClass : public JsonSeriaLizable
{
public:
    MyClass();

    void fromJson(SerializeUtil *serializeUtil) override;
    void toJson(SerializeUtil *serializeUtil) override;
};

#endif // MY_CLASS_H