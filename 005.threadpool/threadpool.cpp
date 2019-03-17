/**
 * 线程池，基于pthread
 * 作者：mnmlyn@163.com
 * 日期：2019年3月16日
 * 参考：http://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html
 */
#include "threadpool.h"

/**
 * @struct  Task
 * @brief   任务结构体
 * @process 任务指针
 * @arg     任务参数
 * @argn    参数的大小（字节为单位）
 */
struct Task {
    TaskFunc process;
    void *arg;
    int argn;
};
typedef struct Task Task;
typedef Task * TaskPtr;

/**
 * @struct          ThreadPool
 * @brief           线程池结构体
 * @mutex           互斥量
 * @cond            条件变量
 * @taskQueue       任务队列
 * @threads         线程池中的线程
 * @poolSize        线程池大小
 * @queueSize       任务队列大小
 * @head            任务队列头
 * @tail            任务队列尾
 * @queueCount      正在排队任务数
 * @started         线程池是否继续运行
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
    int queueCount;
    volatile int started;
    int runningCount;
};
typedef struct ThreadPool ThreadPool;

/**
 * @function    threadPool_workerThread
 * @brief       线程池工作线程
 * @pool        线程池指针
 */
static void *threadPool_workerThread(void *_pool) {
    ThreadPoolPtr pool = (ThreadPoolPtr)_pool;
    Task task;
    for (;;) {
        pthread_mutex_lock(&pool->mutex);//==0 on succ TODO
        --pool->runningCount;
        while (pool->queueCount == 0 && pool->started)
            pthread_cond_wait(&pool->cond, &pool->mutex);//TODO: on fail
        if (0 == pool->queueCount && 0 == pool->started)
            break;
        task = pool->taskQueue[pool->head];
        pool->head = (pool->head + 1) % pool->queueSize;
        --pool->queueCount;
        ++pool->runningCount;
        pthread_mutex_unlock(&pool->mutex);//==0 on succ TODO
        task.process(task.arg, task.argn);
        free(task.arg);
    }
    pthread_mutex_unlock(&pool->mutex);//==0 on succ TODO
}

/**
 * @function    threadPool_create
 * @brief       创建线程池
 * @poolSize    线程池可容纳的线程数量
 * @queueSize   线程池任务队列的大小
 * @return      创建的线程池指针，失败为NULL
 */
ThreadPoolPtr threadPool_create(int poolSize, int queueSize) {
    if (poolSize < 1 || queueSize < 1)
        return NULL;
    ThreadPoolPtr pool = (ThreadPoolPtr)malloc(sizeof(ThreadPool));
    if (!pool){
        return NULL;
    }
    pool->mutex = PTHREAD_MUTEX_INITIALIZER;
    pool->cond = PTHREAD_COND_INITIALIZER;
    pool->taskQueue = (TaskPtr)malloc(sizeof(Task) * queueSize);
    if (!pool->taskQueue) {
        free(pool);
        return NULL;
    }
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * poolSize);
    if (!pool->threads) {
        free(pool->taskQueue);
        free(pool);
        return NULL;
    }
    pool->poolSize = poolSize;
    pool->queueSize = queueSize;
    pool->head = 0;
    pool->tail = 0;
    pool->queueCount = 0;
    pthread_mutex_lock(&pool->mutex);
    int i;
    for (i = 0; i < poolSize; ++i) {
        //TODO: on fail
        pthread_create(pool->threads + i, 0, threadPool_workerThread, pool);
    }
    pool->started = 1;
    pool->runningCount = poolSize;
    pthread_mutex_unlock(&pool->mutex);
    return pool;
}

/**
 * @function    threadPool_addTask
 * @brief       向线程池中添加任务
 * @pool        线程池指针
 * @func        任务函数
 * @arg         参数指针
 * @argn        参数的字节数
 * @return      成功true，否则false
 */
bool threadPool_addTask(ThreadPoolPtr pool, 
        TaskFunc func, void *arg, int argn) {
    void *_arg = malloc(argn);
    if (!_arg) {
        return false;
    }
    memcpy(_arg, arg, argn);
    pthread_mutex_lock(&pool->mutex);//TODO: on fail
    if (pool->queueCount >= pool->queueSize || 0 == pool->started) {
        pthread_mutex_unlock(&pool->mutex);//TODO: on fail
        free(_arg);
        return false;
    }
    pool->taskQueue[pool->tail].process = func;
    pool->taskQueue[pool->tail].arg = _arg;
    pool->taskQueue[pool->tail].argn = argn;
    pool->tail = (pool->tail + 1) % pool->queueSize;
    ++pool->queueCount;
    pthread_cond_signal(&pool->cond);
    pthread_mutex_unlock(&pool->mutex);//TODO: on fail
    return true;
}

/**
 * @function    threadPool_destroy
 * @brief       销毁线程池，等待任务执行完毕
 * @pool        线程池指针
 * @return      成功true，否则false
 */
bool threadPool_destroy(ThreadPoolPtr pool) {
    int i;
    pthread_mutex_lock(&pool->mutex);
    pool->started = 0;
    pthread_cond_broadcast(&pool->cond);
    pthread_mutex_unlock(&pool->mutex);
    for (i = 0; i < pool->poolSize; ++i) {
        pthread_join(pool->threads[i], NULL);//TODO: on fail
    }
    free(pool->threads);
    free(pool->taskQueue);
    free(pool);
    return true;
}
