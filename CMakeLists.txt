cmake_minimum_required(VERSION 3.10)

project(MySerializer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include_directories(${CMAKE_SOURCE_DIR})
include_directories(third_party/rapidjson/include)

add_library(data_serializer OBJECT src/SerializeUtil.cpp src/DataSerializer.cpp)
target_include_directories(data_serializer PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(test 
    test/main.cpp
    test/MyClass.cpp
    test/SubClass.cpp
)

target_link_libraries(test data_serializer)