# include "MyClass.h"

MyClass::MyClass() {

}

void MyClass::fromJson(DataSerializer *serializer) {
    
}

void MyClass::toJson(DataSerializer *serializer) {
    serializer->writeItem("name", "zhangsan")
}