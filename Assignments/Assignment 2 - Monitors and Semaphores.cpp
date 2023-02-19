/*
Kyungchan Im
CST - 315
Professor Richardo Citro
Feb 19, 2023

Assignment 2: Monitors and Semaphores
*/

// include necessary packages for the program
#include <iostream>
#include <queue>     // Queue for buffer
#include <mutex>     // Mutex to give a system a lock or unlock 
#include <condition_variable> // conditional object able to block the calling thread until notified to resume.
#include <chrono>    // use the package only for timing the thread process
#include <thread>    // use the package only for timing the thread process

using namespace std;

// Monitor Implementation
class Monitor {
    private:
        queue<int> buffer;  // buffer to store items
        int capacity;       // represent the size of the buffer
        mutex mtx;          // mutex to protect shared data by using lock, unlock
        condition_variable not_full;    // to notify producer when buffer is not full
        condition_variable not_empty;   // to notify consumer when buffer is not empty

    public: 
        Monitor(int capacity) {         
            this->capacity = capacity;  // points to the object for which the member function is called
        }

        // producer method to add item to buffer
        void produce(int item) {
            unique_lock<mutex> lock(mtx);
            // wait until buffer is not full
            not_full.wait(lock, [this](){ return buffer.size() < capacity; });
            // add item to buffer
            buffer.push(item);
            cout << "Produced item: " << item << endl;
            // notify consumer that buffer is not empty
            not_empty.notify_all();
        }

        // consumer method to remove item from buffer
        int consume() {
            unique_lock<mutex> lock(mtx);
            // wait until buffer is not empty
            not_empty.wait(lock, [this](){ return !buffer.empty(); });
            // remove item from buffer
            int item = buffer.front();
            buffer.pop();
            cout << "Consumed item: " << item << endl;
            // notify producer that buffer is not full
            not_full.notify_all();
            return item;
        }
};

int main() {
    // create monitor with buffer size of 50
    Monitor monitor(50);

    // simulate producer and consumer activities using a single loop
    int signal = 0;
    int item = 0;
    while (true) {
        if (signal == 0) {
            // produce an item
            monitor.produce(item);
            this_thread::sleep_for(chrono::milliseconds(500)); 
            item++;
        } else {
            // consume an item
            monitor.consume();
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        // toggle the signal (like a switch on and off)
        signal = 1 - signal;
    }

    return 0;
}