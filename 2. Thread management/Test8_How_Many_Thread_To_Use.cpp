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
    // Oversubscription
    // More threads than CPU number 
    // Content switching reduces the performance
    int num = std::thread::hardware_concurrency(); // Indication of num_cores
    cout << num << endl;
    return 0;
}