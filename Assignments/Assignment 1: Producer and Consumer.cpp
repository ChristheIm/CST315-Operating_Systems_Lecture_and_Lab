/*
Kyungchan Im
CST - 315
Professor Richardo Citro
Jan 29, 2023
Assignment 1: Producer and Consumer

*/
#include <iostream>
#include <queue>
#include <thread>
#include <mutex> 
#include <chrono>   // let the function run per second


// Assign queue for buffer and mutex for synchronize
std::queue<int> queue;
std::mutex mtx;

int product = 0;  // the item number starts with 0
const int product_size = 15;  // number of buffer size

void consume() {
    int item = queue.front();
    queue.pop();
    std::cout << "Consumed item number: " << item << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void produce() {
    int item = product++;   // increment an item when the function is called
    queue.push(item);
    std::cout << "Produced item number : " << item << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));  // this is for the functional time
}


int main() {

    // when loop is running, produce and consume.
    while (true) {
        while (queue.size() < product_size) {
            produce();
        }
        mtx.lock(); // when the producing is done, then go on a consume function
        while (queue.size() > 0) {
            consume();
        }
        mtx.unlock();
    }

    return 0;
}
