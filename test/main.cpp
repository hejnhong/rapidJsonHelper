#include "MyClass.h"

#include <iostream>
int main() {
    DataSerializer serializer;
    MyClass myClass;
    myClass.toJson(&serializer);
    return 0;
}