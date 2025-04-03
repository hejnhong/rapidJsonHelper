#ifndef MY_CLASS_H
#define MY_CLASS_H

#include "JsonSeriaLizable.h"

class MyClass : public JsonSeriaLizable
{
public:
    MyClass();

    void fromJson(DataSerializer *serializer) override;
    void toJson(DataSerializer *serializer) override;
}

#endif // MY_CLASS_H