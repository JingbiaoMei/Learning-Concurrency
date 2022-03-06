#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
using namespace std;



class LogFile {
    std::mutex _mu;
    ofstream _f;
public:
    LogFile() {
        _f.open("log.txt");
    }
    void shared_print(string id, int value){
        std::lock_guard<mutex> locker(_mu);
        _f << "From" << id << "id:" << value << endl;
    }
};

void function_1(LogFile& log){
    for (int i=0; i>-100; i--)
        log.shared_print("t1", i);
}


int main()
{
    LogFile log;
    std::thread t1(function_1, std::ref(log)); // t1 starts running

    // Do something in the main thread without wasting resource
     
    
    for (int i = 0; i<100; i++)
        log.shared_print(string("From main:"), i);
   
   t1.join(); // main thread waits for t1 to finish

    return 0;
}