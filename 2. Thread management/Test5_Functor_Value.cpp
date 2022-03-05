#include <iostream>
#include <thread>
#include <string>
using namespace std;
class Fctor {
public: 
    void operator()(string msg) {
        std::cout << "t1 says:" << msg << std::endl;
        msg = "changed massage";
    } 
};


int main()
{
    string s = "Hello";
    std::thread t1((Fctor()), s); // t1 starts running
    // Note that the parameter passed to the thread is always value 
    // rather than reference 

    // Do something in the main thread without wasting resource
     
    t1.join();
    std::cout << "from main: " << s << endl;
    

    return 0;
}