# include "SubClass.h"

SubClass::SubClass() {

}

void SubClass::fromJson(SerializeUtil *serializeUtil) {
    
}

void SubClass::toJson(SerializeUtil *serializeUtil) {
    serializeUtil->writeItem("name", "zhangsan");
}