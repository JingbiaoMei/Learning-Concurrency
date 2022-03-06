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

class stack {
    // Array for storing the data
    int* _data;
    // Mutex for protecting the data
    std::mutex _mu;
public:
    void pop(); // pops off the item on top of the stack 
    int& top(); // returns the item on top
    //.... other things
    // top and pop uses mutex to protect data
    // The stack does not leak the data to outside world

}

void function_1 (stack& st) {
    int v = st.top();
    st.pop();
    // process the data v     
    process(v);
    // This function will be used to launch some threads
    // with shared data st
    // Will this code be thread safe?
    // No!! some data will be lost      
    // Consider a stack of 8639 
    // When 2 threads call this func, 
    // Both thread get the top of 8 
    // But first thread might pop 8, and second pop 6
    // 6 will be lost 
    // This depends on the operation, might/might not happen in reality 

    // Solution
    // The operation of pop and top should not be separated into two function 
    // They should be combined to make sure no data lost 
}

class stack_safe {
    // Array for storing the data
    int* _data;
    // Mutex for protecting the data
    std::mutex _mu;
public:
    int& pop(); // pops off the item on top of the stack 
    int& top(); // returns the item on top
}

void function_1_safe (stack& st) {
    int v = st.top();
    // process the data v     
    process(v);
    // However, still not exception safe, say no data could be poped 
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