# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Iinclude
LDFLAGS = 

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c) \
      $(wildcard $(SRC_DIR)/BSTree/*.c) \
      $(wildcard $(SRC_DIR)/DLList/*.c) \
      $(wildcard $(SRC_DIR)/Paper/*.c)

# Object files
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

# Executable name
TARGET = build/citetrack

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory structure
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/BSTree
	mkdir -p $(BUILD_DIR)/DLList
	mkdir -p $(BUILD_DIR)/Paper

# Link object files to create executable
$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Phony targets
.PHONY: all clean