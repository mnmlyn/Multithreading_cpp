#include <iostream>
#include <thread>

static void hello(){
    std::cout << "Hello Concurrent World\n";
}

/* 第一个多线程程序 */
void firstTest(){
    std::thread t(hello);
    t.join();/* 使用join等待线程t结束，注意join只能使用一次，
                使用后，该线程的t.joinable()变为false */
}