/**
 * 线程池头文件
 * 作者：mnmlyn@163.com
 * 日期：2019年3月16日
 */
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

/**
 * 任务类型
 */
typedef void (* TaskFunc)(void *, int);

/**
 * 线程池指针
 */
typedef struct ThreadPool * ThreadPoolPtr;

/**
 * @function    threadPool_create
 * @brief       创建线程池
 * @poolSize    线程池可容纳的线程数量
 * @queueSize   线程池任务队列的大小
 * @return      创建的线程池指针，失败为NULL
 */
ThreadPoolPtr threadPool_create(int poolSize, int queueSize);

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
         TaskFunc func, void *arg, int argn);

/**
 * @function    threadPool_destroy
 * @brief       销毁线程池，等待任务执行完毕
 * @pool        线程池指针
 * @return      成功true，否则false
 */
bool threadPool_destroy(ThreadPoolPtr pool);
