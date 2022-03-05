#include <iostream>
#include <thread>

void func_1()
{
    std::cout << "Hello";
}

int main()
{
    std::thread t1(func_1); // t1 starts running
    // t1.join(); //main thread waits for t1 to finish
    t1.detach(); // t1 will freely on its own -- daemon process
    // Since here main thread does not do anything, it finishes
    // very quickly, therefore, the thread t1 failed to print anything 

    // If two threads are sharing certain resource, then the thread owns that resource,
    // should live as long as other thread is accessing that resource
    
    // After detach, the thread cannot be joined, but can be checked:
    if (t1.joinable())
        t1.join();
    
    return 0;
}