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
        //std::lock_guard<mutex> locker(_mu, std::adopt_lock); 
        // Unique lock is similar to lock guard but more flexible 
        std::unique_lock<mutex> locker(_mu);
        _f << "From" << id << ": " << value << endl;
        locker.unlock();
        //... if other things to be done, but does not require mutex lock
        // could call unlock, only the printing requires the lock 
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

