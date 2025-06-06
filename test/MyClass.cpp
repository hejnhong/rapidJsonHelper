# include "MyClass.h"

MyClass::MyClass()
    : id(0), name("my class") {
    list = {"one", "two", "three"};
}

void MyClass::fromJson(SerializeUtil *serializeUtil) {
    serializeUtil->readItem("name", name);
    serializeUtil->readItem("subClass", subClass);
    std::cout << "name: " << name << std::endl;
}

void MyClass::toJson(SerializeUtil *serializeUtil) const {
    serializeUtil->writeItem("name", "zhangsan");
    serializeUtil->writeItem("subClass", &subClass);
    serializeUtil->writeItem("subClass2", subClass);
    serializeUtil->writeList("list", list);
}