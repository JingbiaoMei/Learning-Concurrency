#include <iostream>
#include <thread>

void func_1()
{
    std::cout << "Hello";
}

int main()
{
    std::thread t1(func_1); // t1 starts running
    t1.join();
    return 0;
}