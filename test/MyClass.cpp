# include "MyClass.h"

MyClass::MyClass()
    : id(0), name("my class") {
    list = {"one", "two", "three"};
}

void MyClass::fromJson(SerializeUtil *serializeUtil) {
    
}

void MyClass::toJson(SerializeUtil *serializeUtil) {
    serializeUtil->writeItem("name", "zhangsan");
    serializeUtil->writeItem("subClass", &subClass);
    serializeUtil->writeList("list", list);
}