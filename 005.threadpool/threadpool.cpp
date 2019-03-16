/**
 * 线程池，基于pthread
 * 作者：mnmlyn@163.com
 * 日期：2019年3月16日
 */
#include "threadpool.h"

/**
 * @struct  Task
 * @brief   任务结构体
 * @process 任务指针
 * @arg 任务参数
 */
struct Task {
    void (* process)(void *);
    void *arg;
};

/**
 * @struct  ThreadPool
 * @brief   线程池结构体
 * @mutex   互斥量
 * @cond    条件变量
 * @taskQueue   任务队列
 * @threads 线程池中的线程
 * @poolSize    线程池大小
 * @queueSize   任务队列大小
 * @head    任务队列头
 * @tail    任务队列尾
 * @started 线程池是否继续运行
 * @runningCount    正在运行的线程计数
 */
struct ThreadPool {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    TaskPtr taskQueue;
    pthread_t *threads;
    int poolSize;
    int queueSize;
    int head;
    int tail;
    volatile int started;
    int runningCount;
};

/**
 * @function    threadPool_create
 *
 */
ThreadPoolPtr threadPool_create(int poolSize, int queueSize) {
    
}

/**
 * @function    threadPool_addTask
 *
 */
bool threadPool_addTask() {

}

/**
 * @function    threadPool_destroy
 *
 */
bool threadPool_destroy() {

}

















