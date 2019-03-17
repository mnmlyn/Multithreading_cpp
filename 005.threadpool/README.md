# 使用C语言，基于linux pthread实现的线程池程序
## 测试方法：  
1. 编译
```make```
2. 运行
```./prog```
测试程序重复创建和释放线程池，向线程池中添加任务。
## 使用方法：
1. 在项目中包含threadpool.h
2. 线程池任务函数定义为```void func(void *arg, int argn);```  
arg为函数参数指针，argn为arg的大小（单位为字节）
3. 创建线程池  
```ThreadPoolPtr threadPool_create(int poolSize, int queueSize);```
4. 向线程池添加任务  
```bool threadPool_addTask(ThreadPoolPtr pool, TaskFunc func, void *arg, int argn);```  
5. 使用完成后，销毁线程池  
```bool threadPool_destroy(ThreadPoolPtr pool);```
