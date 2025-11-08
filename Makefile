# Compiler
CXX = g++

# Compiler flags
# -std=c++17 is needed for <filesystem>
# -Wall enables all warnings
# -g adds debug symbols
CXXFLAGS = -std=c++17 -Wall -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
EXECUTABLE = $(BIN_DIR)/explorer

# Find all .cpp files in the source directory
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# Create a list of object files in the obj directory
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default target: build the executable
all: $(EXECUTABLE)

# Rule to link the executable
$(EXECUTABLE): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile .cpp files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target to clean up all build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
