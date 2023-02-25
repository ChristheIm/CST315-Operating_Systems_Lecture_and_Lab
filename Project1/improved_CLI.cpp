/*
Kyungchan Im
CST - 315
Professor Ricardo Citro
Feb 26,2023

Project 1: Improved Unix/Linux Command Line Interpreter
*/ 
// Include the packages to use 
#include <iostream>            
#include <unistd.h>            // system package to implement the terminal system
#include <sys/wait.h>          // system package to use wait() call
#include <vector>              // vector package to work with vector
#include <string>              // string package to work with string
#include <fstream>             // file package to write/read file



using namespace std;

// Function for separating the commands by ';'
vector<string> splitCommand(const string &command){

    vector<string> commands_list;                           // It is a command container that will hold commands splitted by ';'
    string curr_commands;                                   // It is a string container that grabs a command by adding the character

    for (char c: command){
        if (c == ';') {                                     // If character given string is ';', then 
            commands_list.push_back(curr_commands);         // push the command to the back of the vector
            curr_commands.clear();                          // clear the current command
        } else {                
            curr_commands += c;                             // if it is not ';', then keep add character to read command
        }
    } if (!curr_commands.empty()){                          // Add last command
        commands_list.push_back(curr_commands);
    }

    return commands_list;                                   // return the commands
}


// Function for running a command given from the vector
void runCommand(const string &command){

    if (command.substr(0, 3) == "cd ") {             // check if command is 'cd'
        string directory = command.substr(3);        // get directory name
        int result = chdir(directory.c_str());      // change directory
    
        if (result != 0) {                          // check if chdir() was successful
            std::cout << "Error: Unable to change directory to " << directory << endl;
        }
        return;                                     // Once changing in directory is completed, terminate the function
    }

    vector<string> commands_list = splitCommand(command);   // splitCommand function will split the command by the separator
    vector<pid_t> pids;                                     // process id will be stacked depends on the user input
    for (const auto &command : commands_list)               // for loop for running a command within the command vector
    {
        pid_t pid = fork();                                 // assign the child process, if the pid==0, then it is first process to perform
        if (pid == 0)
        {
            system(command.c_str());
            exit(0);
        }
        else                                                // if not, push to the vector to perform after
        {
            pids.push_back(pid);
        }
    }
    for (const auto &pid : pids)
    {
        waitpid(pid, nullptr, 0);                           // Calling a rest of commands
    }
}


// Function for writing a file
void writeBatchFile(const string &filename){
    ofstream file(filename);            
    string line;
    getline(cin, line);                                     // The program will grab a name for the file and ask the user input context
    while (line != "quit") {
        if (!line.empty())
            file << line << endl;
        cout << "Enter a command (type 'quit' to stop): "; 
        getline(cin, line);
    }
    file.close();
    cout << "Batch file '" << filename << "' created successfully." << endl;  // Once the program creates the file successfully, prompt the successful message
}

// Function for reading/running a file
void runBatchFile(const string &filename){
    ifstream file(filename);
    if (!file){                                             // If the file doesn't exist, throw a error sign
        cerr << "There is no file name '" << filename << "' exist" << endl;
        return;
    }
    string line;                                            // The function will grab the file name and read through the file line by line
    getline(file,line);  
    cout << line << endl;                                   // It will print the contents of the file and run it
    runCommand(line);
    while (getline(file, line)){
        runCommand(line);                                   // runCommand for running a commands inside the file
    }
    file.close();
}


int main(){
    string command;                                             // Command string 

    string user_number;                                         // user input

    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "Welcome to the mini-shell. Please type the number that you want to perform a task" << endl;
    cout << "Type 'run' if you want to run a command" << endl;
    cout << "Type 'quit' if you want to quit the program" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "$ ";
    getline(cin, user_number);

    while (true)                                        
    {
        if (user_number == "run"){
            cout << "This is running a command mode. If you want to quit, type 'quit'." << endl;
            cout << "If you want to write a batch file, type 'batch'." << endl;
            cout << "If you want to execute the batch file, type 'file'. " << endl;
            while (true) {
                cout << "$ ";
                getline(cin, command);                                      // grab a user input command and read the line)
                // Quit the Program
                if (command == "quit"){
                    break;
                }

                // Open File Section
                if (command == "file"){
                    string filename;
                    cout << "This is running a file stage" << endl;
                    cout << "Enter the name of the file that you want to run: ";
                    cin >> filename;
                    runBatchFile(filename);
                    continue;
                }
                
                // Write a File Section
                if (command == "batch"){
                    string filename;
                    cout << "This is batch stage" << endl;
                    cout << "Enter the name of the batch file that you want to create: ";
                    cin >> filename;
                    writeBatchFile(filename);
                }

                // Running a prompt shell
                else {
                    runCommand(command);
                }                
            }
            cout << "Terminating the program..." << endl;
            break;
        }

        if (user_number == "quit"){
            cout << "Terminating the program..." << endl;
            break;
        }

        else {
            cout << "Wrong Input! Please type valid input" << endl;
            cout << "-----------------------------------------------------------------------------" << endl;
            cout << "$ ";
            getline(cin, user_number);
        }

    }
    return 0;
}
