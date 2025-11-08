#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <string>
#include <vector>

// This class encapsulates all the logic for our file explorer [cite: 2931-2938]
class FileExplorer {
public:
    // Constructor: Initializes the explorer [cite: 3056-3061]
    FileExplorer();
    
    // Main loop for the application
    void run();

private:
    std::string current_path; // The directory we are currently in
    bool running;

    // --- Core Methods ---
    
    // Prints the prompt (e.g., /home/uvaers$ )
    void printPrompt();
    
    // Reads and parses the user's input
    std::vector<std::string> parseInput();
    
    // Executes the given command
    void executeCommand(const std::vector<std::string>& args);
    
    // --- Day 1 Function ---
    void listDirectory();
};

#endif // FILE_EXPLORER_H
