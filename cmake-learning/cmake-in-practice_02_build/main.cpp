#include <boost/regex.hpp>
#include <iostream>

int main() {
  std::string text = "Contact us at support@example.com or sales@example.com.";

  // 定义一个用于匹配电子邮件地址的正则表达式
  boost::regex email_regex(R"(([\w.%+-]+)@([\w.-]+\.[a-zA-Z]{2,}))");
  boost::sregex_iterator it(text.begin(), text.end(), email_regex);
  boost::sregex_iterator end;

  // 遍历所有匹配的结果
  while (it != end) {
    std::cout << "Found email: " << (*it)[0] << std::endl;
    ++it;
  }

  return 0;
}