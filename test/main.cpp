#include "MyClass.h"
#include "DataSerializer.h"

#include <string>
#include <iostream>
int main() {
    MyClass myClass;
    DataSerializer dataSerializer;

    // serialize
    std::string res = dataSerializer.serialize(&myClass);
    std::cout << "serialized data : " << res << std::endl;

    // deserialize
    MyClass myClass2;
    dataSerializer.deserialize(res, &myClass2);
    return 0;
}