# Makefile for ip-nose

# Compilateur C++
CXX = clang++

# Flags de compilation
# -std=c++17 : utilise la norme C++17 (nécessaire pour nlohmann/json et d'autres fonctionnalités)
# -Wall -Wextra -pedantic : active un grand nombre d'avertissements pour un code de meilleure qualité
# -I : inclut le chemin vers les headers. On ajoute le répertoire 'include' pour nlohmann/json et 'src' pour nos propres headers
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -I./include -I./src

# Bibliothèques à lier
# -lcurl : pour la bibliothèque curl
# Pas de -lstdc++fs : nous avons supprimé cette dépendance car elle n'était pas trouvée
LIBS = -lcurl

# Répertoires
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Fichiers sources
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Fichiers objets correspondants
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Nom de l'exécutable final
TARGET = $(BUILD_DIR)/ip-nose

# Répertoire d'installation pour l'exécutable
# Sur Termux, /data/data/com.termux/files/usr/bin/ est un bon choix pour les binaires
INSTALL_DIR = /data/data/com.termux/files/usr/bin

# Ajout de 'install' et 'uninstall' à la liste des "phony targets"
.PHONY: all clean run debug install uninstall

all: $(TARGET)

# Règle pour l'exécutable final
$(TARGET): $(OBJ_DIR) $(OBJS)
	@echo "Linking $(TARGET)..."
	$(CXX) $(OBJS) -o $@ $(LIBS)

# Règle pour créer le répertoire des objets
$(OBJ_DIR):
	@echo "Creating object directory: $@"
	@mkdir -p $@

# Règle générique pour compiler les fichiers source en objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle clean : supprime les fichiers compilés et le répertoire build
clean:
	@echo "Cleaning up build directory..."
	@rm -rf $(BUILD_DIR)

# Règle run : compile et exécute le programme
# Utilise RUN_ARGS pour passer des arguments à l'exécutable
run: all
	@echo "Running $(TARGET)..."
	$(TARGET) $(RUN_ARGS)

# Règle debug : compile en mode debug avec gdb (si gdb est installé sur Termux)
debug: CXXFLAGS += -g # Ajoute le flag -g pour les infos de debug
debug: all
	@echo "Running $(TARGET) with GDB..."
	gdb $(TARGET)

# Nouvelle règle : install
# Installe l'exécutable dans un répertoire du PATH
install: all
	@echo "Installing $(TARGET) to $(INSTALL_DIR)/$(notdir $(TARGET))..."
	@rm -f $(INSTALL_DIR)/$(notdir $(TARGET))
	@ln -s $(realpath $(TARGET)) $(INSTALL_DIR)/$(notdir $(TARGET))
	@echo "$(notdir $(TARGET)) installé. Tu peux maintenant l'exécuter en tapant '$(notdir $(TARGET))'."

# Nouvelle règle : uninstall (optionnel, pour nettoyer l'installation)
uninstall:
	@echo "Uninstalling $(notdir $(TARGET)) from $(INSTALL_DIR)/..."
	@rm -f $(INSTALL_DIR)/$(notdir $(TARGET))
	@echo "$(notdir $(TARGET)) désinstallé."

