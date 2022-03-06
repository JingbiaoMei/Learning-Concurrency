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
        // do something else without locking the mutex



        locker.lock();
        _f << "From" << id << ": " << value << endl;
        locker.unlock();

        //lock and unlock for more than one time

        // could move a unique lock
        // Transfer the ownership of the mutex from one unique lock to another

        std::unique_lock<mutex> locker2 = std::move(locker);

        // unique lock is more heavy weighted then the lock guard
        // less performance from unique lock 
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

