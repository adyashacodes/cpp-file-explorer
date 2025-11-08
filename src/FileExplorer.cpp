#include "FileExplorer.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>     // For chdir(), getcwd()
#include <cstdlib>      // For system()
#include <filesystem>   // For canonical()

// Constructor
FileExplorer::FileExplorer() {
    this->running = true;
    // Set the initial path to the user's home directory
    this->current_path = getenv("HOME");
    // Change the program's directory to home
    chdir(this->current_path.c_str());
}

// Main application loop
void FileExplorer::run() {
    // Show the initial file list
    listDirectory();

    while (this->running) {
        printPrompt();
        std::vector<std::string> args = parseInput();
        
        if (args.empty()) {
            continue; // Show prompt again
        }
        
        executeCommand(args);
    }
}

// Prints the user prompt
void FileExplorer::printPrompt() {
    // Get the canonical path (cleans up ".." and ".")
    std::string prompt_path = std::filesystem::canonical(this->current_path);
    std::cout << prompt_path << "$ ";
    std::flush(std::cout);
}

// Reads and parses a line of input
std::vector<std::string> FileExplorer::parseInput() {
    std::string line;
    std::getline(std::cin, line);
    
    std::vector<std::string> args;
    std::stringstream ss(line);
    std::string word;
    
    while (ss >> word) {
        args.push_back(word);
    }
    return args;
}

// Decides which function to call
void FileExplorer::executeCommand(const std::vector<std::string>& args) {
    if (args.empty()) {
        return;
    }
    
    std::string command = args[0];
    
    if (command == "ls") {
        listDirectory();
    } 
    // Handle 'exit'
    else if (command == "exit") {
        this->running = false;
    }
    // Handle 'clear'
    else if (command == "clear") {
        system("clear");
    }
    else {
        std::cout << "Unknown command: " << command << std::endl;
        std::cout << "Available: ls, exit, clear" << std::endl;
    }
}

// --- Day 1 Function ---
// Interfaces with the 'ls' command [cite: 2426]
void FileExplorer::listDirectory() {
    // We use "ls -l --color=auto" for a nice, readable list
    // system() executes a shell command
    system("ls -l --color=auto");
}
