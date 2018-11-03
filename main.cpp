#include <iostream>
#include "main.h"

int main(){
    /* 第一个多线程程序 */
    //firstTest();
    /* RAII，保证函数异常和正常退出前，都调用了join */
    RAII_Test();

    std::cin.get();
    return 0;
}