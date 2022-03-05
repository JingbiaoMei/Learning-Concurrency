#include <iostream>
#include <thread>
#include <string>
using namespace std;
class Fctor {
public: 
    void operator()(string msg) {
        std::cout << "t1 says:" << msg << std::endl;
        
    } 
};


int main()
{
    string s = "Hello";
    std::thread t1((Fctor()), s); // t1 starts running
    
    // Do something in the main thread without wasting resource
     
    try {
        std::cout << "from main thread: " << s << std::endl;
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