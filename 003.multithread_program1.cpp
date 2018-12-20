/* 参考：https://www.cnblogs.com/ljygoodgoodstudydaydayup/p/5950400.html
 * 题目：子线程循环 10 次，接着主线程循环 100 次，
 * 接着又回到子线程循环 10 次，接着再回到主线程又循环 100 次。
 * ...
 * 如此循环50次，试写出代码
 * 搞定：学习条件变量condition_variable的使用
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = true;

static void func_child(){
    int i,j;
    for(i=0;i<50;++i){
        std::unique_lock<std::mutex> lck(mtx);
        while(!ready)cv.wait(lck);
        std::cout << "child:";
        for(j=0;j<5;++j){
            std::cout << j << " ";
        }
        std::cout << "\n";
        ready = false;
        cv.notify_one();
    }
}

static void func_main(){
    int i,j;
    for(i=0;i<50;++i){
        std::unique_lock<std::mutex> lck(mtx);
        while(ready)cv.wait(lck);
        std::cout << "main:";
        for(j=0;j<37;++j){
            std::cout << j << " ";
        }
        std::cout << "\n";
        ready = true;
        cv.notify_one();
    }
}

void problem1(){
    std::thread t1(func_child);
    func_main();
    t1.join();
}
