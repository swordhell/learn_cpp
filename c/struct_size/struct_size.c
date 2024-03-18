#include <stdio.h>  
  
struct AlarmMessage {  
    unsigned char device_type;  
    unsigned char row;  
    unsigned char box;  
    unsigned int pos:4;  
    unsigned int level:4;  
};  
  
int main() {  
    // 计算struct AlarmMessage的大小  
    size_t size = sizeof(struct AlarmMessage);  
      
    // 打印出大小  
    printf("Size of struct AlarmMessage: %zu bytes\n", size);  
      
    return 0;  
}
/*
这个`struct`定义了一个名为`AlarmMessage`的结构体，其中包含了以下成员：

1. `device_type`：1字节（`unsigned char`）
2. `row`：1字节（`unsigned char`）
3. `box`：1字节（`unsigned char`）
4. `pos`：4位（`unsigned int`）
5. `level`：4位（`unsigned int`）

结构体的总大小取决于成员的大小以及对齐方式。在这个结构体中，大部分成员都是1字节，不需要对齐；而对于位域成员，编译器通常会按照最大成员的大小来对齐。在这里，`pos`和`level`都是4位，因此按照字节对齐会占用1字节。

所以，这个结构体的总大小为：1字节 + 1字节 + 1字节 + 1字节 = 4字节。


gcc struct_size.c -o struct_size

*/