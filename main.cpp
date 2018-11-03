#include <iostream>
#include <thread>

void hello(){
    std::cout << "Hello Concurrent World\n";
}

int main(){
    std::thread t(hello);
    t.join();

    std::cin.get();
    return 0;
}