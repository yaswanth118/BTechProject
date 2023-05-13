# Compiler and flags
CC=g++
CFLAGS=-c -w
INCLUDE_DIRS=$(shell find $(SRC_DIR) -type d -exec printf "-I{}\n" \;)

# Directories
SRC_DIR=src
OBJ_DIR=obj

# Source files (recursively)
SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp')

# Object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Targets
all: main

main: $(OBJ_FILES)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o main
