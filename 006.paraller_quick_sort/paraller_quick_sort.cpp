#include <iostream>
#include <future>

using namespace std;

int add_two(int a, int b) {
    return a + b;
}

int main(int argc, char **argv) {
    future<int> fut = async(add_two,1,2);
    cout << "do something\n";
    int ret = fut.get();
    cout << "async ret = " << ret << endl;
    cout << "End\n";
}
