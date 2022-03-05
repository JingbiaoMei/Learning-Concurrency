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
    std::thread t1((Fctor()), std::ref(s)); 
    // Note that the parameter passed to the thread is always value 
    // rather than reference 
    // Enforing the reference passing with the above
    // Now that they are sharing the same memory location 
    // This might cause data race problem that will be managed later
    
    
    // Do something in the main thread without wasting resource
     
    t1.join();
    std::cout << "from main: " << s << endl;
    

    return 0;
}