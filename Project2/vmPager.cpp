/* --------------------------------------------------------------------------------------------------------- //
Kyungchan Im
CST - 315
Professor Ricardo Citro
Mar 26,2023

Project 2: Pager – A Virtual Memory Manager
// --------------------------------------------------------------------------------------------------------- */
// Define the Packages and Import
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <random>
// --------------------------------------------------------------------------------------------------------- //
// instantiate the page size, memory size, and page count
const int PAGE_SIZE = 4;
const int MEMORY_SIZE = 32;
const int PAGE_COUNT = MEMORY_SIZE / PAGE_SIZE;
const int NUM_PAGES = 4;

// function for generating random 4-byte strings
std::string generate_string() {
    std::string result;
    for (int i = 0; i < PAGE_SIZE; i++) {
        result += static_cast<char>((rand() % 26) + 'a');       // random generation of the string
    }
    return result;
}

// write strings to file
void write_strings_to_file(const std::vector<std::string>& strings, const std::string& filename) {
    std::ofstream outfile(filename);
    for (const auto& str : strings) {
        outfile << str << std::endl;
    }
    outfile.close();
}

// read strings from file
std::vector<std::string> read_strings_from_file(const std::string& filename) {
    std::vector<std::string> strings;
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        strings.push_back(line);
    }
    infile.close();
    return strings;
}


// -------------------------------------------------------------------------------------------------------- //
int main() {
    srand(time(NULL)); // seed the random number generator with the current time

    // generate random 4-byte strings and store them in a text file
    std::vector<std::string> strings;
    for (int i = 0; i < NUM_PAGES; i++) {
        strings.push_back(generate_string());
    }
    write_strings_to_file(strings, "strings.txt");

    // read the strings from the text file
    std::vector<std::string> input_strings = read_strings_from_file("strings.txt");

    // randomly assign physical pages to the logical pages
    std::vector<int> physical_pages(PAGE_COUNT, -1); // vector to store the physical pages assigned to the logical pages
    std::vector<int> unused_pages(PAGE_COUNT); // vector to store the unused physical pages
    std::iota(unused_pages.begin(), unused_pages.end(), 0); // initialize unused_pages with 0 to PAGE_COUNT-1
    std::shuffle(unused_pages.begin(), unused_pages.end(), std::mt19937(std::random_device()())); // randomly shuffle unused_pages
    std::map<int, int> page_table; // maps logical page number to physical page number
    for (int i = 0; i < NUM_PAGES; i++) {
        int logical_page = i;
        int physical_page = unused_pages.back();
        unused_pages.pop_back();
        page_table[logical_page] = physical_page;
        physical_pages[physical_page] = logical_page;
    }

    // print the page numbers and physical page numbers
    std::ofstream outfile("output.txt");
    for (int i = 0; i < NUM_PAGES; i++) {
        int logical_page = i;
        int physical_page = page_table[logical_page];
        std::string str = input_strings[logical_page];
        outfile << "Index " << logical_page << ": " << str << " -> Physical Frame Address: " << physical_page << std::endl;
    }
    outfile.close();

    return 0;
}

