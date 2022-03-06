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

//Solution, make sure each thread has the same order for locking mutex

class LogFile {
    std::mutex _mu;
    std::mutex _mu2;
    ofstream _f;
public:
    LogFile() {
        _f.open("log.txt");
    }
    void shared_print(string id, int value){
        // std lock locks arbirary number of lockable objects like mutex
        // using dead lock avoidance algorithm
        std::lock(_mu, _mu2);
        std::lock_guard<mutex> locker(_mu, std::adopt_lock); // tells the locker that the mutex is already locked
        // adopt to the ownership of the mutex, so that when go out of the scopem, remember to unlock the mutex
        std::lock_guard<mutex> locker2(_mu2, std::adopt_lock);
        cout << "From" << id << ": " << value << endl;
    }
    void shared_print2(string id, int value){
        std::lock(_mu, _mu2);
        std::lock_guard<mutex> locker(_mu, std::adopt_lock); // tells the locker that the mutex is already locked
        // adopt to the ownership of the mutex, so that when go out of the scopem, remember to unlock the mutex
        std::lock_guard<mutex> locker2(_mu2, std::adopt_lock);
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

/* avoiding deadlock
1. Prefer locking single mutex

2. Try not to lock the mutex and call some user function
    - Since donot know what that function do
    - Might lock another mutex or this mutex again

3. std::lock() to lock more than one mutex
4. Lock the mutex in same order if stdlock is not possible 
5.Hirearchy of mutex 


Locking Granularity 
- Fine grained lockL: protects small amount of data
    - More computationally efficient
    - More likely to dead lock
- Coarse-grained lock: protexts big amounts of data
    - Loss of parallel computing as many threads waiting for resources


*/