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
    const char* home_dir = getenv("HOME");
    if (home_dir != nullptr) {
        this->current_path = home_dir;
    } else {
        this->current_path = "/";
    }
    chdir(this->current_path.c_str());
}

// Main application loop
void FileExplorer::run() {
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
    } else if (command == "cd") {
        changeDirectory(args);
        listDirectory();
    } else if (command == "help") {
        showHelp();
    } else if (command == "exit") {
        this->running = false;
    } else if (command == "clear") {
        system("clear");
        listDirectory();
    } else if (command == "cp") {
        copyItem(args);
        listDirectory();
    } else if (command == "mv") {
        moveItem(args);
        listDirectory();
    } else if (command == "rm") {
        deleteItem(args);
        listDirectory();
    } else if (command == "touch") {
        createFile(args);
        listDirectory();
    } else if (command == "mkdir") {
        createDirectory(args);
        listDirectory();
    } else if (command == "search") {
        searchFiles(args);
    }
    // --- NEW FOR DAY 5 ---
    else if (command == "chmod") {
        changePermissions(args);
        listDirectory();
    }
    // ---------------------
    else {
        std::cout << "Unknown command: " << command << std::endl;
        std::cout << "Type 'help' for a list of commands." << std::endl;
    }
}

// --- Command Functions ---

void FileExplorer::listDirectory() {
    system("ls -l --color=auto");
}

void FileExplorer::changeDirectory(const std::vector<std::string>& args) {
    std::string path;
    if (args.size() < 2 || args[1] == "~") {
        path = getenv("HOME");
    } else {
        path = args[1];
    }
    if (chdir(path.c_str()) != 0) {
        perror("cd");
    } else {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            this->current_path = cwd;
        } else {
            perror("getcwd");
        }
    }
}

// Shows the help menu
void FileExplorer::showHelp() {
    std::cout << "--- C++ File Explorer Help ---" << std::endl;
    std::cout << "  ls                - List files in the current directory" << std::endl;
    std::cout << "  cd <dir>          - Change directory (e.g., 'cd ..')" << std::endl;
    std::cout << "  cp <src> <dest>   - Copy a file or directory" << std::endl;
    std::cout << "  mv <src> <dest>   - Move or rename a file or directory" << std::endl;
    std::cout << "  rm <file>         - Delete a file (use 'rm -r' for dirs)" << std::endl;
    std::cout << "  touch <file>      - Create a new empty file" << std::endl;
    std::cout << "  mkdir <dir>       - Create a new directory" << std::endl;
    std::cout << "  search <keyword>  - Search for files by name (case-insensitive)" << std::endl;
    std::cout << "  chmod <mode> <file> - Change file permissions (e.g., 'chmod 755 script.sh')" << std::endl;
    std::cout << "  clear             - Clear the terminal screen" << std::endl;
    std::cout << "  help              - Show this help menu" << std::endl;
    std::cout << "  exit              - Quit the explorer" << std::endl;
    std::cout << "--------------------------------" << std::endl;
}

// Helper function to build a command string from args
std::string FileExplorer::buildCommand(const std::vector<std::string>& args, int start_index) {
    std::string cmd_string;
    // Build the command string, handling spaces in paths
    for (size_t i = start_index; i < args.size(); ++i) {
        cmd_string += "\"" + args[i] + "\" ";
    }
    return cmd_string;
}

void FileExplorer::copyItem(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        std::cout << "Usage: cp <source> <destination>" << std::endl;
        return;
    }
    // We must add '-r' for directories
    std::string cmd_string = "cp -r " + buildCommand(args, 1);
    system(cmd_string.c_str());
}

void FileExplorer::moveItem(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        std::cout << "Usage: mv <source> <destination>" << std::endl;
        return;
    }
    std::string cmd_string = "mv " + buildCommand(args, 1);
    system(cmd_string.c_str());
}

void FileExplorer::deleteItem(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Usage: rm <file>  (use 'rm -r <dir>' for directories)" << std::endl;
        return;
    }
    std::string cmd_string = "rm " + buildCommand(args, 1);
    system(cmd_string.c_str());
}

void FileExplorer::createFile(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Usage: touch <filename>" << std::endl;
        return;
    }
    std::string cmd_string = "touch " + buildCommand(args, 1);
    system(cmd_string.c_str());
}

void FileExplorer::createDirectory(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Usage: mkdir <dirname>" << std::endl;
        return;
    }
    std::string cmd_string = "mkdir " + buildCommand(args, 1);
    system(cmd_string.c_str());
}

void FileExplorer::searchFiles(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Usage: search <keyword>" << std::endl;
        return;
    }
    std::string keyword = args[1];
    std::string cmd_string = "find . -iname \"*" + keyword + "*\"";
    std::cout << "Searching for files containing '" << keyword << "'..." << std::endl;
    system(cmd_string.c_str());
}

// --- NEW FOR DAY 5 ---
// Changes file permissions
void FileExplorer::changePermissions(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        std::cout << "Usage: chmod <mode> <filename>" << std::endl;
        std::cout << "Example: chmod 755 my_script.sh" << std::endl;
        return;
    }
    
    // Build 'chmod <mode> <file>'
    // We don't use the helper here to keep mode and file separate
    std::string cmd_string = "chmod " + args[1] + " " + args[2];
    system(cmd_string.c_str());
}
