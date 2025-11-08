#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <string>
#include <vector>

class FileExplorer {
public:
    FileExplorer();
    void run();

private:
    std::string current_path;
    bool running;

    // --- Core Methods ---
    void printPrompt();
    // --- THIS LINE IS NOW FIXED (was std.vector) ---
    std::vector<std::string> parseInput(); 
    void executeCommand(const std::vector<std::string>& args);
    
    // --- Command Functions ---
    void listDirectory();
    void changeDirectory(const std::vector<std::string>& args); 
    void showHelp(); 
};

#endif // FILE_EXPLORER_H
