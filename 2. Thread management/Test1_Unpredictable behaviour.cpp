#include <iostream>
#include <thread>

void func_1()
{
    std::cout << "from thread1: Hello";
}

int main()
{
    std::thread t1(func_1); // t1 starts running

    // Do something in the main thread without wasting resource

    // This will cause some unexplainable behaviour
    // Additionally, if there is any sort of   exception raised
    // in the main thread, it will terminate the whole program
    // we need to handle the exception in the main thread
    for (int i = 0; i<100; i++)
        std::cout << "from main thread: " << i << std::endl;

    //t1.join(); // main thread waits for t1 to finish

    return 0;
}