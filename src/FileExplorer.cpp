#include "FileExplorer.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>     // For chdir(), getcwd()
#include <cstdlib>      // For system()
#include <filesystem>   // For canonical()
#include <limits.h>     // For PATH_MAX

// Constructor
FileExplorer::FileExplorer() {
    this->running = true;
    
    // Get the user's home directory
    const char* home_dir = getenv("HOME");
    if (home_dir != nullptr) {
        this->current_path = home_dir;
    } else {
        // Fallback if HOME is not set
        this->current_path = "/";
    }
    
    // Change the program's working directory
    chdir(this->current_path.c_str());
}

// Main application loop
void FileExplorer::run() {
    // We run 'clear' and 'ls' once at the start
    system("clear");
    listDirectory();

    while (this->running) {
        printPrompt();
        std::vector<std::string> args = parseInput();
        
        if (args.empty()) {
            continue;
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
    
    // --- THIS LINE IS NOW FIXED (was std.vector) ---
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
    else if (command == "cd") { // <-- NEW FOR DAY 2
        changeDirectory(args);
        // After changing directory, list the contents
        listDirectory();
    }
    else if (command == "help") { // <-- NEW FOR DAY 2
        showHelp();
    }
    else if (command == "exit") {
        this->running = false;
    }
    else if (command == "clear") {
        system("clear");
        listDirectory(); // Show files after clearing
    }
    else {
        std::cout << "Unknown command: " << command << std::endl;
        std::cout << "Type 'help' for a list of commands." << std::endl;
    }
}

// --- Command Functions ---

// Interfaces with the 'ls' command
void FileExplorer::listDirectory() {
    system("ls -l --color=auto");
}

// --- NEW FOR DAY 2 ---
// Changes the current working directory
void FileExplorer::changeDirectory(const std::vector<std::string>& args) {
    std::string path;
    
    if (args.size() < 2 || args[1] == "~") {
        // 'cd' or 'cd ~' goes to home
        path = getenv("HOME");
    } else {
        path = args[1];
    }
    
    // Use chdir() to change directory
    if (chdir(path.c_str()) != 0) {
        // chdir() failed
        perror("cd");
    } else {
        // chdir() was successful, update our path variable
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            this->current_path = cwd;
        } else {
            perror("getcwd");
        }
    }
}

// --- NEW FOR DAY 2 ---
// Shows the help menu
void FileExplorer::showHelp() {
    std::cout << "--- C++ File Explorer Help ---" << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "  ls          - List files in the current directory" << std::endl;
    std::cout << "  cd <dir>    - Change directory (e.g., 'cd ..', 'cd /var/log')" << std::endl;
    std::cout << "  clear       - Clear the terminal screen" << std::endl;
    std::cout << "  help        - Show this help menu" << std::endl;
    std::cout << "  exit        - Quit the explorer" << std::endl;
    std::cout << "--------------------------------" << std::endl;
}
