# Makefile for ProjectName

# Version
VERSION := 1.0.0

# Compiler
CC := gcc

# Compiler flags
CFLAGS := -Wall -Wextra -std=c11

# Debug flags
DFLAGS := -g -DDEBUG

# Optimization flags
OFLAGS := -O2

# Source directories
SRC_DIRS := src include

# Find all .c files in the source directories
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

# Build Folder
BUILD_DIR := build

# Object files
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Dependency files
DEPS := $(OBJS:.o=.d)

# Executable name
TARGET := $(BUILD_DIR)/main

# Installation directory
INSTALL_DIR := /usr/local/bin

# Include directories
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Add include flags to CFLAGS
CFLAGS += $(INC_FLAGS) -MMD -MP

# Default target
all: $(TARGET)

# Create build directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Linking
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^
	@echo 'Build complete: $(TARGET) (Version $(VERSION))'

# Compiling
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug build
debug: CFLAGS += $(DFLAGS)
debug: all

# Release build
release: CFLAGS += $(OFLAGS)
release: all

# Clean
clean:
	rm -rf $(BUILD_DIR)

# Install
install: $(TARGET)
	install -m 755 $(TARGET) $(INSTALL_DIR)

# Uninstall
uninstall:
	rm -f $(INSTALL_DIR)/$(notdir $(TARGET))

# Include the dependency files
-include $(DEPS)

# Generate version information
version:
	@echo 'Version: $(VERSION)'

# Phony targets
.PHONY: all debug release clean install uninstall version $(BUILD_DIR)