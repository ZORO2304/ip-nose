# Makefile for ip-nose

# C++ Compiler
CXX = clang++

# Compilation Flags
# -std=c++17: uses C++17 standard (needed for regex, chrono, etc.)
# -Wall -Wextra -pedantic: enables many warnings for better code quality
# -I: includes path to headers. Adding 'include' and 'src' directories for our own headers
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -I./include -I./src

# Libraries to link
# -lcurl: for the curl library
# The mathematical library (-lm) is no longer necessary after removing the advanced triangulation algorithm.
LIBS = -lcurl

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Corresponding object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Final executable name
TARGET = $(BUILD_DIR)/ip-nose

# Installation directory for the executable
# On Termux, /data/data/com.termux/files/usr/bin/ is a good choice for binaries
INSTALL_DIR = /data/data/com.termux/files/usr/bin

# Add 'install' and 'uninstall' to the list of "phony targets"
.PHONY: all clean run debug install uninstall

all: $(TARGET)

# Rule for the final executable
$(TARGET): $(OBJ_DIR) $(OBJS)
	@echo "Linking $(TARGET)..."
	$(CXX) $(OBJS) -o $@ $(LIBS)

# Rule to create the object directory
$(OBJ_DIR):
	@echo "Creating object directory: $@"
	@mkdir -p $@

# Generic rule to compile source files into objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule: deletes compiled files and the build directory
clean:
	@echo "Cleaning up build directory..."
	@rm -rf $(BUILD_DIR)

# Run rule: compiles and executes the program
# Uses RUN_ARGS to pass arguments to the executable
run: all
	@echo "Running $(TARGET)..."
	$(TARGET) $(RUN_ARGS)

# Debug rule: compiles in debug mode with gdb (if gdb is installed on Termux)
debug: CXXFLAGS += -g # Adds -g flag for debug info
debug: all
	@echo "Running $(TARGET) with GDB..."
	gdb $(TARGET)

# New rule: install
# Installs the executable in a directory on the PATH
install: all
	@echo "Installing $(TARGET) to $(INSTALL_DIR)/$(notdir $(TARGET))..."
	@rm -f $(INSTALL_DIR)/$(notdir $(TARGET))
	@ln -s $(realpath $(TARGET)) $(INSTALL_DIR)/$(notdir $(TARGET))
	@echo "$(notdir $(TARGET)) installed. You can now run it by typing '$(notdir $(TARGET))'."

# New rule: uninstall (optional, for cleaning up the installation)
uninstall:
	@echo "Uninstalling $(notdir $(TARGET)) from $(INSTALL_DIR)/..."
	@rm -f $(INSTALL_DIR)/$(notdir $(TARGET))
	@echo "$(notdir $(TARGET)) uninstalled."
