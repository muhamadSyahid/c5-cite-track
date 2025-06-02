# Compiler and flags
CC = gcc -g -Wall
CFLAGS = -Iinclude

ifeq ($(OS),Windows_NT)
	CFLAGS += -Llib/windows
else
	UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
		CFLAGS += -Llib/linux
	else ifeq ($(UNAME_S),Darwin)
		CFLAGS += -Llib/macos
	endif
endif

LDFLAGS = -lm -lcJSON

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c) \
      $(wildcard $(SRC_DIR)/BSTree/*.c) \
      $(wildcard $(SRC_DIR)/DLList/*.c) \
      $(wildcard $(SRC_DIR)/Paper/*.c) \
      $(wildcard $(SRC_DIR)/Parser/*.c)

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
	mkdir -p $(BUILD_DIR)/Parser

# Link object files to create executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Phony targets
.PHONY: all clean