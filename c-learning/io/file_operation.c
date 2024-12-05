/*
 * =======================================
 *  文件操作：复制、加密、解密
 * =======================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file_size() {
    const char* read_path = "Student.txt";
    FILE* fp = fopen(read_path, "r");
    // 重新定位文件指针：SEEK_END 文件末尾，0 偏移量。
    fseek(fp, 0, SEEK_END);
    // 返回当前的文件指针，相对于文件开头的位移量。
    const long size = ftell(fp);
    printf("%s file size = %ld \n", read_path, size);
}

void copy_file() {
    const char* read_path = "Student.txt";
    const char* write_path = "Student_copy.txt";

    // 读的文件，b 字符表示操作二进制文件 binary。
    FILE* read_fp = fopen(read_path, "rb");
    if (read_fp == NULL) {
        printf("open read file fail");
        return;
    }
    // 写的文件
    FILE* write_fp = fopen(write_path, "wb");
    if (write_fp == NULL) {
        printf("open write file fail");
        return;
    }
    // 复制
    int buff[50]; //缓冲区域
    size_t len = 0; //每次读到的数据长度
    while ((len = fread(buff, sizeof(int), 50, read_fp)) != 0) {
        //将读到的内容写入新的文件
        printf("read len-> %ld, ", len);
        fwrite(buff, sizeof(int), len, write_fp);
    }

    // 关闭流
    fclose(read_fp);
    fclose(write_fp);
}

// 加密文本文件，规则：1^1=0, 0^0=0, 1^0=1, 0^1=1 同为 0，不同为 1。
void encrypt1(const char* normal_path, const char* crypt_path) {
    //打开文件
    FILE* normal_fp = fopen(normal_path, "r");
    FILE* crypt_fp = fopen(crypt_path, "w");
    //一次读取一个字符
    int ch = 0;
    while ((ch = fgetc(normal_fp)) != EOF) {
        //End of File
        printf("read ch = %c, ", ch);
        //写入（异或运算）
        fputc(ch ^ 9, crypt_fp);
    }
    //关闭
    fclose(normal_fp);
    fclose(crypt_fp);
}

// 解密文本文件
void decrypt1(const char* crypt_path, const char* decrypt_path) {
    //打开文件
    FILE* normal_fp = fopen(crypt_path, "r");
    FILE* crypt_fp = fopen(decrypt_path, "w");
    //一次读取一个字符
    int ch;
    while ((ch = fgetc(normal_fp)) != EOF) {
        //End of File
        //写入（异或运算）
        fputc(ch ^ 9, crypt_fp);
    }
    //关闭
    fclose(crypt_fp);
    fclose(normal_fp);
}

// 二进制文件加密，规则：密码位数+异或
void encrypt2(const char* normal_path, const char* crypt_path, const char* password) {
    //打开文件
    FILE* normal_fp = fopen(normal_path, "rb");
    FILE* crypt_fp = fopen(crypt_path, "wb");
    //一次读取一个字符
    int ch;
    int i = 0; //循环使用密码中的字母进行异或运算
    const size_t pwd_len = strlen(password); //密码的长度
    while ((ch = fgetc(normal_fp)) != EOF) {
        // End of File
        // 写入（异或运算）
        fputc(ch ^ password[i % pwd_len], crypt_fp);
        i++;
    }
    //关闭
    fclose(crypt_fp);
    fclose(normal_fp);
}

//二进制文件解密
void decrypt2(const char* crypt_path, const char* decrypt_path, const char* password) {
    //打开文件
    FILE* normal_fp = fopen(crypt_path, "rb");
    FILE* crypt_fp = fopen(decrypt_path, "wb");
    //一次读取一个字符
    int ch;
    int i = 0; //循环使用密码中的字母进行异或运算
    const size_t pwd_len = strlen(password); //密码的长度
    while ((ch = fgetc(normal_fp)) != EOF) {
        // End of File
        // 写入（异或运算）
        fputc(ch ^ password[i % pwd_len], crypt_fp);
        i++;
    }
    //关闭
    fclose(crypt_fp);
    fclose(normal_fp);
}


int main() {
    // 获取文件大小
    read_file_size();

    // 复制文件
    copy_file();

    // 文本加解密
    //encrypt1("./test1.txt", "./test1_en.txt");
    //decrypt1("./test1_en.txt", "./test1_de.txt");

    // 二进制加解密
    //encrypt2("./list.rar", "./list_en.rar", "haha");
    //decrypt2("./list_en.rar", "./list_de.rar", "haha");

    return EXIT_SUCCESS;
}
