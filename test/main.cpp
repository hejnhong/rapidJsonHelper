#include "MyClass.h"
#include "DataSerializer.h"

#include <iostream>
int main() {
    // SerializeUtil serializeUtil;
    MyClass myClass;
    // myClass.toJson(&serializeUtil);
    DataSerializer dataSerializer;
    dataSerializer.serialize(&myClass);
    return 0;
}