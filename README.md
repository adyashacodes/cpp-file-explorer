# C++ Console File Explorer

This is a console-based file explorer application written in C++ for the Capstone Project (Assignment 1). It uses an object-oriented design and interfaces directly with the Linux OS by wrapping standard shell commands.

## Project Overview

The goal of this project is to create a fully functional, console-based file explorer. [cite_start]The design is based on the **Object-Oriented Programming (OOP)** principles covered in the course modules [cite: 2637-2930]. All file and directory operations are encapsulated within a `FileExplorer` class.

[cite_start]To interface with the Linux operating system, this program uses the `system()` call to execute common POSIX commands (like \`ls\`, \`cp\`, \`mv\`, etc.) [cite: 2423-2426]. This demonstrates a practical approach to building a C++ application on a Linux environment.

## Features

* **Object-Oriented Design:** All logic is encapsulated in a \`FileExplorer\` class, managing its own state (like \`current_path\`).
* **Interactive Loop:** A continuous \`run()\` loop that displays a prompt and waits for user input.
* **Dynamic Prompt:** The prompt always shows your full, canonical current working directory (e.g., \`/home/uvaers/my_folder\`).
* **Command Parsing:** User input is parsed into a command and its arguments.
* **Linux Command Interface:** Uses \`system()\` to run core Linux commands, providing real and accurate results.

## Implemented Commands

The explorer supports the following commands:

* **Navigation**
    * \`ls\`: Lists the contents of the current directory with details (\`ls -l\`).
    * \`cd <dir>\`: Changes the current directory. Supports \`..\`, \`~\`, and absolute/relative paths.
* **File Manipulation**
    * \`cp <src> <dest>\`: Copies a file or directory (recursively).
    * \`mv <src> <dest>\`: Moves or renames a file or directory.
    * \`rm <file>\`: Deletes a file.
    * \`rm -r <dir>\`: Deletes a directory recursively.
    * \`touch <file>\`: Creates a new, empty file.
    * \`mkdir <dir>\`: Creates a new directory.
* **File Search**
    * \`search <keyword>\`: Performs a case-insensitive search for files/directories containing the keyword in their name, starting from the current directory.
* **Permission Management**
    * \`chmod <mode> <file>\`: Changes the permissions of a file (e.g., \`chmod 755 script.sh\`).
* **Utility**
    * \`help\`: Displays a list of all available commands.
    * \`clear\`: Clears the terminal screen.
    * \`exit\`: Quits the file explorer.

## How to Build and Run

This project uses a \`Makefile\` for easy compilation.

1.  **Clone the repository:**
    \`\`\`bash
    git clone https://github.com/adyashacodes/cpp-file-explorer.git
    cd cpp-file-explorer
    \`\`\`

2.  **Compile:**
    \`\`\`bash
    make
    \`\`\`
    This will create the executable at \`./bin/explorer\`.

3.  **Run:**
    \`\`\`bash
    ./bin/explorer
    \`\`\`

## Credits

Made by Adyasha Sahoo[Regd. no:-2241019031]
