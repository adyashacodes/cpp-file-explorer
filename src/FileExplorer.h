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
    std::vector<std::string> parseInput();
    void executeCommand(const std::vector<std::string>& args);
    std::string buildCommand(const std::vector<std::string>& args, int start_index = 1);

    // --- Command Functions ---
    void listDirectory();
    void changeDirectory(const std::vector<std::string>& args);
    void showHelp();
    void copyItem(const std::vector<std::string>& args);
    void moveItem(const std::vector<std::string>& args);
    void deleteItem(const std::vector<std::string>& args);
    void createFile(const std::vector<std::string>& args);
    void createDirectory(const std::vector<std::string>& args);
    void searchFiles(const std::vector<std::string>& args);
    
    // --- NEW FOR DAY 5 ---
    void changePermissions(const std::vector<std::string>& args);
};

#endif // FILE_EXPLORER_H
