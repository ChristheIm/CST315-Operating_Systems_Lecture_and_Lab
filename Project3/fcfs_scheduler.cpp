/* --------------------------------------------------------------------------------------------------------- //
Kyungchan Im
CST - 315
Professor Ricardo Citro
Apr 02,2023

Project 3: Short-Term Process Scheduler
// --------------------------------------------------------------------------------------------------------- */
// Define the Packages and Import
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

// Define the State of the Process
enum State {
    RUNNING,
    READY,
    WAITING
};

// Define the Process identification
struct Process {
    int id;
    int burst_time;
    int waiting_time;
    State state;
};

// Function to display the process state
void print_process_info(Process processes[], int size) {
    std::cout << "Burst Time:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << "Process " << processes[i].id << " : " << processes[i].burst_time << " ms | ";
    }
    std::cout << std::endl << "Waiting Time:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << "Process " << processes[i].id << " : " << processes[i].waiting_time << " ms | ";
    }
    std::cout << std::endl;
}

// Function to calculate average waiting time.
double calculate_average_waiting_time(Process processes[], int size) {
    double total_waiting_time = 0;
    for (int i = 0; i < size; i++) {
        total_waiting_time += processes[i].waiting_time;
    }
    return total_waiting_time / size;
}


// Function to calculate the order of the process
void custom_process_order(Process processes[], int size) {
    static int process_index = 0;

    for (int i = 0; i < size; i++) {
        if (i == process_index) {
            processes[i].state = RUNNING;
        } else if (processes[i].state == RUNNING) {
            processes[i].state = WAITING;
        } else if (processes[i].state == WAITING) {
            processes[i].state = READY;
        }
    }

    std::cout << "State of processes: ";
    for (int i = 0; i < size; i++) {
        std::cout << "Process " << processes[i].id << " : ";
        switch (processes[i].state) {
            case RUNNING:
                std::cout << "Running | ";
                break;
            case READY:
                std::cout << "Ready | ";
                break;
            case WAITING:
                std::cout << "Waiting | ";
                break;
        }
    }
    std::cout << std::endl;

    process_index = (process_index + 1) % size;
}

// Main
int main() {
    // Define individual process
    Process processes[3] = {
        {1, 5, 0, WAITING},
        {2, 9, 5, WAITING},
        {3, 2, 14, WAITING}
    };

    // Print the message for the process analysis
    print_process_info(processes, 3);
    std::cout << "Average Waiting Time: " << calculate_average_waiting_time(processes, 3) << " ms" << std::endl << std::endl;

    // Iterate process for the process.
    while (1) {
        custom_process_order(processes, 3);
        std::this_thread::sleep_for(std::chrono::seconds(1)); // sleep for 1 second
    }

    return 0;
}
