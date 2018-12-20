/*
* 写三个线程，一个线程打印1~52，一个线程打印A~Z，一个线程打印a~z
* 打印顺序是12Aa34Bb...5152Zz
* 每个小写字母后要换行
*/
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

static std::mutex mtx;
static std::condition_variable cv;
static int run_id = 0;

static void print123(){
    int i;
    for(i = 1; i <= 26; ++i){
        std::unique_lock<std::mutex> lck(mtx);
        while(1 != run_id)cv.wait(lck);
        std::cout << 2 * i - 1;
        std::cout << 2 * i;
        run_id = 2;
        cv.notify_all();
    }
}

static void printABC(){
    int i;
    for(i = 0; i < 26; ++i){
        std::unique_lock<std::mutex> lck(mtx);
        while(2 != run_id)cv.wait(lck);
        std::cout << (char)('A' + i);
        run_id = 3;
        cv.notify_all();
    }
}

static void printabc(){
    int i;
    for(i = 0; i < 26; ++i){
        std::unique_lock<std::mutex> lck(mtx);
        while(3 != run_id)cv.wait(lck);
        std::cout << (char)('a' + i) << std::endl;
        run_id = 1;
        cv.notify_all();
    }
}

void twothreadprintbyturn(){
    std::thread th1(print123);
    std::thread th2(printABC);
    std::thread th3(printabc);
    {
        std::unique_lock<std::mutex> lck(mtx);
        run_id = 1;
        cv.notify_all();
    }
    th1.join();
    th2.join();
    th3.join();
}
