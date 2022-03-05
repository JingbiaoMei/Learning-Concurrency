#include <iostream>
#include <thread>
#include <string>
using namespace std;
class Fctor {
public: 
    void operator()(string& msg) {
        std::cout << "t1 says:" << msg << std::endl;
        msg = "changed massage";
    } 
};


int main()
{
    string s = "Hello";

    // Print out parent thread id
    cout << std::this_thread::get_id() << endl;

    std::thread t1((Fctor()), std::move(s)); 
    
    // Move s from main thread to the child thread 
    // Safe and efficient
    
    // Print child thread id
    cout << t1.get_id() << endl;
    // Or print this_thread get id in the child thread function

    
    // Some objects in c++ can not be copied, only moved
    // like thread object
    // std::thread t2 = t1; this will not work

    // to transfer ownership of a thread:
    std::thread t2 = std::move(t1);

    t2.join();
    // std::cout << "from main: " << s << endl;
    

    return 0;
}