#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
using namespace std;

class LogFile {
    std::mutex _mu; // mutex for print text
    std::mutex _mu_open; // mutex for open the file
    ofstream _f;
public:
    LogFile() {
        // lazy initialization 
        // or Initialization upon first use idiom
    }
    void shared_print(string id, int value){
        // to make sure thread safe, needs a mutex to sync file opening process
        {
            std::unique_lock<mutex> locker2(_mu_open);
            if (!_f.is_open()) { // open if not opened
                // the file will only be opened once in the shared_print function
                
                // before the thread open the file, it will lock the mutex

                // However, this is still not thread safe, as there might be 2 threads 
                // trying to lock the mutex at the same time. The second thread will first 
                // be blocked, then it could then lock the mutex. Finally, the file would be 
                // opened twice 
                // Solution: the file open needs to be protected as well, see part4
                _f.open("log.txt");
            }
        }
        // However, this block raises another problem, everytime, the program will
        // check if file is opened or not and lock the mutex and then unlock
        // which wastes clock cycles 
        // Solution with std once_flag see part5

        std::unique_lock<mutex> locker(_mu);
        _f << "From" << id << ": " << value << endl;
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

