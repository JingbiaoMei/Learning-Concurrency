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
    return 0;
}