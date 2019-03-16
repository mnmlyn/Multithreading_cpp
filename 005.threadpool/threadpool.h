/**
 * 线程池头文件
 * 作者：mnmlyn@163.com
 * 日期：2019年3月16日
 */
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

typedef void (* TaskFunc)(void *, int);

typedef struct Task Task;
typedef Task * TaskPtr;

typedef struct ThreadPool ThreadPool;
typedef ThreadPool * ThreadPoolPtr;

ThreadPoolPtr threadPool_create(int poolSize, int queueSize);
bool threadPool_addTask(ThreadPoolPtr pool,
         TaskFunc func, void *arg, int argn);
bool threadPool_destroy(ThreadPoolPtr pool);

