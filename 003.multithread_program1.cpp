/* 参考：https://www.cnblogs.com/ljygoodgoodstudydaydayup/p/5950400.html
 * 题目：子线程循环 10 次，接着主线程循环 100 次，
 * 接着又回到子线程循环 10 次，接着再回到主线程又循环 100 次。
 * ...
 * 如此循环50次，试写出代码
*/
#include <iostream>
#include <thread>
#include <mutex>

static void func_child(){
    int i,j;
    for(i=0;i<50;++i){
        
        std::cout << "child:";
        for(j=0;j<10;++j){
            std::cout << j << " ";
        }
        std::cout << "\n";
    }
}

static void func_main(){
    int i,j;
    for(i=0;i<50;++i){
        
        std::cout << "main:";
        for(j=0;j<100;++j){
            std::cout << j << " ";
        }
        std::cout << "\n";
    }
}

void problem1(){
    std::thread t1(func_child);
    func_main();
}