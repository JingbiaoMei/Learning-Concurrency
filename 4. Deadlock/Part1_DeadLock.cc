#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
using namespace std;

// With two mutex, the code will not be finished, it will stuck in the middle
// A dead lock happens
// T1 thread locks mutex mu
// Before T1 go ahead and lock mu2, main thread locks mu2
// The T1 is waiting for main thread to release mu2
// The main thread is waiting for T1 to release mu

class LogFile {
    std::mutex _mu;
    std::mutex _mu2;
    ofstream _f;
public:
    LogFile() {
        _f.open("log.txt");
    }
    void shared_print(string id, int value){
        std::lock_guard<mutex> locker(_mu);
        std::lock_guard<mutex> locker2(_mu2);
        cout << "From" << id << ": " << value << endl;
    }
    void shared_print2(string id, int value){
        std::lock_guard<mutex> locker2(_mu);
        std::lock_guard<mutex> locker(_mu);
        cout << "From" << id << ": " << value << endl;
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

        
    for (int i = 0; i<100; i++)
        log.shared_print2(string("From main: "), i);
   
   t1.join(); // main thread waits for t1 to finish

    return 0;
}