#ifndef C_BASIC_STRUCT_TYPE_H
#define C_BASIC_STRUCT_TYPE_H

#include <string>

/**
 * 定义 Sales_data，表示销售数据。
 */
struct Sales_data {
    // 从 class 继承默认是 private 继承，而从 struct 继承默认是 public 继承。
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

/**
 * 可以为创建的类型取一个"别名"
 */
typedef struct {
    char title[50];
    char author[50];
    char subject[100];
    int book_id;
} Books;

#endif
