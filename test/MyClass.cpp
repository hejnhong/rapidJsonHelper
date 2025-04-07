# include "MyClass.h"

MyClass::MyClass() {

}

void MyClass::fromJson(SerializeUtil *serializeUtil) {
    
}

void MyClass::toJson(SerializeUtil *serializeUtil) {
    serializer->writeItem("name", "zhangsan");
}