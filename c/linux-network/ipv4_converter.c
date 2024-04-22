#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 函数：将有符号32位整数转换为IPv4地址字符串
char* int_to_ipv4(unsigned int num, char* output) {
    unsigned char bytes[4];
    bytes[0] = (num & 0xFF000000) >> 24;
    bytes[1] = (num & 0x00FF0000) >> 16;
    bytes[2] = (num & 0x0000FF00) >> 8;
    bytes[3] = (num & 0x000000FF);

    sprintf(output, "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);
    return output;
}

// 函数：将IPv4地址字符串转换为有符号32位整数
int ipv4_to_int(const char* ip) {
    int num = 0;
    unsigned char bytes[4];
    sscanf(ip, "%hhu.%hhu.%hhu.%hhu", &bytes[0], &bytes[1], &bytes[2], &bytes[3]);
    
    num = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
    return num;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-ip | -str] [value]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-ip") == 0) {
        unsigned int num = atoi(argv[2]);
        char ipv4_str[16];
        printf("整型 %u 转换为IPv4地址: %s\n", num, int_to_ipv4(num, ipv4_str));
    } else if (strcmp(argv[1], "-str") == 0) {
        int num = ipv4_to_int(argv[2]);
        printf("IPv4地址 %s 转换为整型: %d\n", argv[2], num);
    } else {
        fprintf(stderr, "Error: Unknown flag. Use -ip or -str.\n");
        return 1;
    }

    return 0;
}
