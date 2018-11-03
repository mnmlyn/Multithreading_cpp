/* 使用detach()来直接分离线程，不会面临这里要说的问题。
 * 使用join等待线程结束，可能面临一场环境下的等待问题。
 * 比如：
 * 1.start thread t
 * 2.do something in current thread
 * 3.join
 * 这里2有可能会出错，发生异常，从而导致3没有被执行。
 * 因此，要使用下边的方法：
 * start thread t
 * try{
 * do something in current thread }
 * catch{
 * t.join();
 * throw;
 * }
 * t.join()
 * 也就是要在代码的每种可能的退出路径上，都使用join。
 * 但是，这样很啰嗦，于是就有了RAII
 * 即，资源获取即初始化
 */
#include <iostream>
#include <thread>

/* 提供一个类，在其析构函数中进行join
 * 哪怕函数一场退出，栈中声明的临时变量或对象，都会执行析构，
 * 从而保证join一定被调用
*/
class thread_guard{
    std::thread &t;
public:
    explicit thread_guard(std::thread &_t):t(_t){}
    ~thread_guard(){
        if(t.joinable()){/* join只能被调用一次，调用后，t的joinable()变为false */
            t.join();
        }
    }
    thread_guard(const thread_guard &)=delete;/* 禁用编译器自动生成的复制构造函数 */
    thread_guard & operator =(const thread_guard &)=delete;/* 禁用编译器自动生成的赋值运算符重载 */
};

static void func1(){
    std::cout << "execute func1\n";
}

void RAII_Test(){
    std::thread t(func1);
    thread_guard g(t);/* g是放在栈区的临时变量，在该函数（正常或异常）退出后，g的析构函数都会被调用
                        从而保证调用了t的join()函数 */

    //do_something_in_current_thread();
}