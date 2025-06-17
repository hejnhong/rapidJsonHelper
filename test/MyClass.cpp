# include "MyClass.h"

MyClass::MyClass()
    : id(0), name("my class") {
    testList = {"one", "two", "three"};
}

void MyClass::fromJson(SerializeUtil *serializeUtil) {
    serializeUtil->readItem("name", name);
    std::cout << "name: " << name << std::endl;

    serializeUtil->readItem("subClass", subClass);

    SubClass *subClassPtr = nullptr;
    serializeUtil->readItem("subClassPtr", subClassPtr);
    if (subClassPtr != nullptr) {
        std::cout << "subClassPtr is created " << std::endl;
    }


    serializeUtil->readList("testList", testList);
    for (auto &item : testList) {
        std::cout << "item: " << item << std::endl;
    }
}

void MyClass::toJson(SerializeUtil *serializeUtil) const {
    serializeUtil->writeItem("name", "zhangsan");
    serializeUtil->writeItem("subClassPtr", &subClass);
    serializeUtil->writeItem("subClass", subClass);
    serializeUtil->writeList("testList", testList);
}