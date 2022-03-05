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
     
    try{
        for (int i = 0; i<100; i++)
            std::cout << "from main thread: " << i << std::endl;
    } catch (...) {
        t1.join();
        throw;
    }

    // using RAII is an alternative method
    // When w goes out of scope, it will automatically join the thread
    // Wrapper w(t1);

    t1.join(); // main thread waits for t1 to finish

    return 0;
}