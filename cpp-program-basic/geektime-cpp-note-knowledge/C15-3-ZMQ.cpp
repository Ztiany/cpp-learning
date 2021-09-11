/*
 ============================================================================
 
 Author      : Ztiany
 Description : ZMQ 使用示例
    1. 运行环境：msys2
    2. 安装 ZMP：pacman -S mingw-w64-x86_64-zeromq

 ============================================================================
 */

#include <zmq.hpp>
#include <iostream>
#include <string>
#include <future>

using namespace std;

const auto thread_num = 1;

zmq::context_t context(thread_num);

//https://stackoverflow.com/questions/19344955/non-local-lambda-and-capturing-variables-what-does-block-scope-means
// auto make_sock = [&](auto mode)，块作用域以外的 Lambda 函数捕捉列表必须为空。
auto make_sock = [](auto mode) {
    return zmq::socket_t(context, mode);
};

void case1() {
    const auto addr = "ipc:///dev/shm/zmq.sock"s;
    //const auto addr = "inproc:///dev/shm/zmq.sock"s;

    auto receiver = [=]() {
        auto sock = make_sock(ZMQ_PULL);

        sock.bind(addr);
        assert(sock.connected());

        zmq::message_t msg;

        sock.recv(&msg);

        cout << msg.size() << endl;

        string s = {msg.data<char>(), msg.size()};
        cout << s << endl;
    };

    auto sender = [=]() {
        auto sock = make_sock(ZMQ_PUSH);

        sock.connect(addr);
        assert(sock.connected());

        string s = "hello zmq";
        //zmq::message_t msg(begin(s), end(s));
        //sock.send(msg);

        sock.send(s.data(), s.size());
    };

    sender();
    receiver();
}


int main() {
    //print zmp version
    int a, b, c;
    std::tie(a, b, c) = zmq::version();
    cout << "version = " << a << b << c << endl;

    //run case1
    case1();

    return EXIT_SUCCESS;
}