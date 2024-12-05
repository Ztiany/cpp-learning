/*
 * =======================================
 *  类的定义
 * =======================================
 */

#include <iostream>
#include <string>

using std::istream;
using std::ostream;

#include "define_class.h"

Sales_data::Sales_data(std::istream& is) {
    read(is, *this);
}

double Sales_data::avg_price() const {
    if (units_sold)
        return revenue / units_sold;
    return 0;
}

Sales_data& Sales_data::combine(const Sales_data& rhs) {
    std::cout << rhs.bookNo << std::endl;
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

istream& read(istream& is, Sales_data& item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

ostream& print(ostream& os, const Sales_data& item) {
    os << item.isbn() << " " << item.units_sold << " "
        << item.revenue << " " << item.avg_price();
    return os;
}

int main() {
    Sales_data item;
    const std::string null_book("abc");
    item.combine(static_cast<Sales_data>(null_book));
    return EXIT_SUCCESS;
}
