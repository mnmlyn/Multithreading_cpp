#ifndef _MAIN_H_
#define _MAIN_H_

/* 第一个多线程程序 */
void firstTest();
/* RAII，使得函数退出前保证调用join */
void RAII_Test();
/* 子线程和主线程交替打印信息 */
void problem1();
/* 三个子线程，在主线程发出命令后，开始轮流执行 */
void twothreadprintbyturn();
#endif
