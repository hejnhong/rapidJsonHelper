#include "MyClass.h"
#include "DataSerializer.h"

#include <string>
#include <iostream>
int main() {
    MyClass myClass;
    DataSerializer dataSerializer;
    std::string res = dataSerializer.serialize(&myClass);
    std::cout << res << std::endl;

    // deserialize
    MyClass myClass2;
    dataSerializer.deserialize(res, &myClass2);
    return 0;
}