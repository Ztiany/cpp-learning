/*
 * =======================================
 *  IO 类
 * =======================================
 */

#include <cstdlib>
#include <iostream>

using namespace std;

void tieIO() {
    cin.tie(&cerr);
    string receive;
    while (getline(cin, receive)) {
        if (receive == "q") {
            break;
        }
        cerr << receive << endl;
    }
}

void assessStatus() {
    int ival; // 循环读取一个 int 值。
    /*
     * cin >> ival：这部分代码尝试从标准输入读取一个整数值，并将其存储在变量 ival 中。如果读取成功，cin 的状态将是
     * true；如果读取失败（例如，输入不是整数），cin 的状态将是 false。
     *
     * "," 运算符：逗号运算符 , 用于连接两个表达式，并返回第二个表达式的值。在这种情况下，cin >> ival 和 !cin.eof()
     * 都会被执行，但 while 循环的条件将是 !cin.eof() 的值。
     *
     * !cin.eof()：这部分代码检查 cin 是否到达了文件结束（EOF）。如果 cin 到达了文件结束，cin.eof() 将返回 true，
     * 否则返回 false。
     */
    while (cin >> ival, !cin.eof()) {
        if (cin.bad()) {
            // 出现致命错误，程序需要退出
            throw runtime_error("IO stream corrupted");
        }
        cout << "is fail = " << cin.fail() << endl; // 警告用户
        if (cin.fail()) {
            // 错误的输入
            cerr << "bad data, try again" << endl; // 警告用户
            cin.clear(iostream::goodbit); // 重置状态
            cin.ignore(); // 清除缓冲区，否则错误的输入一直在缓冲区中
            continue; // 继续
        }
    }
}

void ioFlush() {
    cout << unitbuf; // 每一次操作都要刷新一次
    cout << "hello";
    cout << nounitbuf; // 恢复使用缓冲区
}

void ioError() {
    int word;
    while (cin >> word) {
        // 输入不合法则条件为false
        // ok 操作是成功的
        cout << "word = " << word << endl;
    }
}

void ioStatus() {
    cout << "----------- ioStatus ----------- " << endl;
    cout << "goodbit " << std::ostream::goodbit << endl;
    cout << "eofbit " << std::ostream::eofbit << endl;
    cout << "badbit " << std::ostream::badbit << endl;
    cout << "failbit " << std::ostream::failbit << endl;

    cout << "good() " << cout.good() << endl;
    cout << "eof() " << cout.eof() << endl;
    cout << "bad() " << cout.bad() << endl;
    cout << "fail() " << cout.fail() << endl;

    cout << "rdstate() " << cout.rdstate() << endl;
}

int main() {
    ioStatus();
    ioError();
    ioFlush();
    assessStatus();
    tieIO();
    return EXIT_SUCCESS;
}
