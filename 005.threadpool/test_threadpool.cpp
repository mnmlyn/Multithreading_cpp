/**
 * 线程池测试
 * 作者：mnmlyn@163.com
 * 日期：2019年3月16日
 */
#include "threadpool.h"
#include <stdio.h>
#include <unistd.h>
void func(void *_arg, int n) {
    int *arg = (int *)_arg;
    n = n / sizeof(int);
    printf("%d", n);
    int i;
    int temp;
    int count = 100000;
    while (count--) {
        for (i = 0; i < n - 1; ++i) {
            temp = arg[i];
            arg[i] = arg[i + 1];
            arg[i + 1] = temp;
        }
    }
    printf("haha, %d\n", count);
    for (i = 0; i < n; ++i) {
        printf("%d ", arg[i]);
    }
    printf("\nchild finish\n");
}

int main(int argc, char **argv) {
    ThreadPoolPtr pool = threadPool_create(1000,1000);
    if (pool)printf("succ\n");
    else printf("fail\n");
    int arr[5] = {1, 2, 3, 4, 5};
    for (;;) {
        threadPool_addTask(pool, func, arr, sizeof(int)*5);
        usleep(1);
    }
    //sleep(5);
    threadPool_destroy(pool);
    printf("end\n");

    return 0;
}





