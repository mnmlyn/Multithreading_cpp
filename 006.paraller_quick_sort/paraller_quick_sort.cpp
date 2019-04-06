#include <iostream>
#include <future>
#include <utility>
#include <list>
#include <algorithm>

using namespace std;

//参考C++ Concurrency IN Action
list<int> parallel_quick_sort(list<int> input) {
    if (input.empty())
        return input;
    list<int> result;
    //将input的第一个元素，从原位置摘除，拼接到ret的开头
    result.splice(result.begin(), input, input.begin());
    //选定这个元素作为枢纽
    const int &pivot = *result.begin();
    //对input进行划分，匿名表达式返回true的在前，不满足的在后，
    //返回第一个不满足的元素的迭代器
    list<int>::iterator divide_point = 
            partition(input.begin(), input.end(), 
            [&](const int & t){return t<pivot;});
    //划分点之前的元素列表，切分下来
    list<int> lower_part;
    lower_part.splice(lower_part.end(), 
            input, input.begin(), divide_point);
    //前半部分异步执行快排
    future<list<int> > new_lower = 
            async(parallel_quick_sort, move(lower_part));
    //剩余的后半部分，本线程内执行快排
    list<int> new_higher = parallel_quick_sort(move(input));
    //将前后两部分结果合并
    result.splice(result.end(), new_higher);
    result.splice(result.begin(), new_lower.get());
    return result;
}

int add_two(int a, int b) {
    return a + b;
}

int main(int argc, char **argv) {
    future<int> fut = async(add_two,1,2);
    //future<int> fut(async(add_two,1,2));//这样写也正确，拷贝构造
    cout << "do something\n";
    int ret = fut.get();
    cout << "async ret = " << ret << endl;
    cout << "parallel_quick_sort\n";
    int arr[] = {16,18,2,1,6,232,86,4,3,77,19};
    list<int> mylist(arr, arr + sizeof(arr)/sizeof(int));
    list<int> sort_ret = parallel_quick_sort(mylist);
    for(int x:sort_ret)
        cout << x << " ";
    cout << endl;
    cout << "End\n";
}

