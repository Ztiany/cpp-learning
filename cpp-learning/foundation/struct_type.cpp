/*
 * =======================================
 *  使用 struct 自定义数据结构
 * =======================================
 */

#include <iostream>
#include <cstring>
#include "06.struct_type.h"

using namespace std;

static void test_sales_data() {

    // 声明一个 Sales_data
    Sales_data sales_data;

    // 书的单价
    double price;

    // 输入单价
    cin >> sales_data.bookNo >> sales_data.units_sold >> price;

    sales_data.revenue = sales_data.units_sold * price;

    cout << "bookNo = " << sales_data.bookNo << ", units_sold = " << sales_data.units_sold << ", revenue=" << sales_data.revenue;
}

static void test_Books() {
    Books Book1, Book2;

    // Book1 详述
    strcpy(Book1.title, "C++ 教程");//数据无法直接赋值，只能拷贝
    strcpy(Book1.author, "Runoob");
    strcpy(Book1.subject, "编程语言");
    Book1.book_id = 12345;

    // Book2 详述
    strcpy(Book2.title, "CSS 教程");
    strcpy(Book2.author, "Runoob");
    strcpy(Book2.subject, "前端技术");
    Book2.book_id = 12346;

    // 输出 Book1 信息
    cout << "第一本书标题 : " << Book1.title << endl;
    cout << "第一本书作者 : " << Book1.author << endl;
    cout << "第一本书类目 : " << Book1.subject << endl;
    cout << "第一本书 ID : " << Book1.book_id << endl;

    // 输出 Book2 信息
    cout << "第二本书标题 : " << Book2.title << endl;
    cout << "第二本书作者 : " << Book2.author << endl;
    cout << "第二本书类目 : " << Book2.subject << endl;
    cout << "第二本书 ID : " << Book2.book_id << endl;

}

int main() {
    test_sales_data();
    test_Books();
    return EXIT_SUCCESS;
}