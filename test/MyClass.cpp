# include "MyClass.h"

MyClass::MyClass() {

}

void MyClass::fromJson(SerializeUtil *serializeUtil) {
    
}

void MyClass::toJson(SerializeUtil *serializeUtil) {
    serializeUtil->writeItem("name", "zhangsan");
}