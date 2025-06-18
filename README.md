# rapidJsonHelper

## 1. 功能介绍
该库封装了rapidjson的常用功能，让不同类型的数据，无论是简单数值，还是指针、对象、vector、map 等等，都能够使用简单的接口进行序列化和反序列化。

## 2. 使用说明
1. 把 include 和 src 文件夹复制到项目里，并加入编译
2. 序列化的类继承接口类 Serializable，并实现 toJson 和 fromJson 方法。具体可参考 MyClass 和 SubClass 类。
3. 通过 DataSerializer 中的 serialize 和 deserialize 方法进行序列化和反序列化。比如 test 下 main.cpp 有如下代码：
   ```c++
    MyClass myClass;
    DataSerializer dataSerializer;

    // serialize
    std::string res = dataSerializer.serialize(&myClass);
    std::cout << res << std::endl;

    // deserialize
    MyClass myClass2;
    dataSerializer.deserialize(res, &myClass2);
    ```

## 3. 接口说明
SerializeUtil 类里的接口分为读和写两部分：

writeItem：写单个数据项到json中，key 是在 json 中的 key
readItem：读单个数据项，把 key 对应的数据项读到 item 中

writeList：写 vector 数据
readList：读数据到 vector 中
