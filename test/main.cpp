#include "MyClass.h"

#include <iostream>
int main() {
    SerializeUtil serializeUtil;
    MyClass myClass;
    myClass.toJson(&serializeUtil);
    return 0;
}