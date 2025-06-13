# Makefile for ip-nose

# C++ Compiler
CXX = clang++

# Flags de compilation
# -std=c++17 : utilise la norme C++17 (nécessaire pour regex, chrono, etc.)
# -Wall -Wextra -pedantic : active un grand nombre d'avertissements pour un code de meilleure qualité
# -I : inclut le chemin vers les headers. On ajoute le répertoire 'include' et 'src' pour nos propres headers
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -I./include -I./src

# Bibliothèques à lier
# -lcurl : pour la bibliothèque curl
# La bibliothèque mathématique (-lm) n'est plus nécessaire après la suppression de l'algorithme de triangulation avancé.
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
