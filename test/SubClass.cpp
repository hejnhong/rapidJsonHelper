# include "SubClass.h"

SubClass::SubClass() : age(0), sex("default") {
}

SubClass::SubClass(int age, const std::string &sex) 
    : age(age), sex(sex) {
}

void SubClass::fromJson(SerializeUtil *serializeUtil) {
    serializeUtil->readItem("sex", sex);
    serializeUtil->readItem("age", age);
    std::cout<<"age:"<<age<<" sex:"<<sex<<std::endl;
}

void SubClass::toJson(SerializeUtil *serializeUtil) const {
    serializeUtil->writeItem("sex", sex);
    serializeUtil->writeItem("age", age);
}