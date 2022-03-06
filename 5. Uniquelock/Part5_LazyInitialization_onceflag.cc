#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
using namespace std;

class LogFile {
    std::mutex _mu; // mutex for print text
    // std::mutex _mu_open; // mutex for open the file
    std::once_flag _flag;
    ofstream _f;
public:
    LogFile() {
        // lazy initialization 
        // or Initialization upon first use idiom
    }
    void shared_print(string id, int value){
        
        // {
        //     std::unique_lock<mutex> locker2(_mu_open);
        //     if (!_f.is_open()) { // open if not opened
                
        //         _f.open("log.txt");
        //     }
        // }
        std::call_once(_flag, [&](){_f.open("log.txt"); });
        // Makes sure this lambda function will be called only once by one thread

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

