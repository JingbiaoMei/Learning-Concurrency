#include <iostream>
#include <thread>
#include <mutex>
using namespace std;


// Race condition is when the outcome of the program depends on the relative 
// execution order of one or more threads
// Typically not good for the program

// Using Mutex to solve the problem



std::mutex mu;

// By using shared_print, cout function is used only 
// by one thread at a time
void shared_print(string msg, int id) {
    std::lock_guard<std::mutex> guard(mu); 
    //RAII
    // Whenever the guard goes out of scope, mu will always be unlocked with/without exception 
    // We need to make sure this function is not provided to other function as arguemnt
    // Not used by other function
    
    //mu.lock();

    // However, another issue is that the resource (cout) is not being protected
    // if another thread calls it 
    cout << msg << id << endl;
    //mu.unlock();
}


void func() {
    for (int i=0; i>-100; i--) {
        shared_print("From t1:" , i) ;
    }
}


int main()
{

    std::thread t1(func); // t1 starts running

    // Do something in the main thread without wasting resource
     
    
    for (int i = 0; i<100; i++)
        shared_print("From main:" , i) ;
   
    

   t1.join(); // main thread waits for t1 to finish

    return 0;
}