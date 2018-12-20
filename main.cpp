#include <iostream>
#include "main.h"

int main(){
    /* 第一个多线程程序 */
    //firstTest();
    /* RAII，保证函数异常和正常退出前，都调用了join */
    //RAII_Test();
    /* 两个线程交替执行，考察条件变量的使用 */
    problem1();

    return 0;
}
