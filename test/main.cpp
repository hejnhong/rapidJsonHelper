#include "MyClass.h"

#include <iostream>
int main() {
    DataSerializer serializer;
    MyClass myClass;
    serializer.serialize(&myClass);
    return 0;
}