# include "SubClass.h"

SubClass::SubClass() {

}

void SubClass::fromJson(SerializeUtil *serializeUtil) {
    std::cout << "SubClass::fromJson" << std::endl;
}

void SubClass::toJson(SerializeUtil *serializeUtil) const {
    serializeUtil->writeItem("name", "zhangsan");
}