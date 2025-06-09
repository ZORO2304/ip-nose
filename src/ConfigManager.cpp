// src/ConfigManager.cpp
#include "ConfigManager.h"
#include <iostream>
#include "TerminalDisplay.h" // Pour les couleurs

// Constructeur
ConfigManager::ConfigManager(const std::string& configFilePath)
    : filePath(configFilePath) {
    // Initialise la configuration avec les valeurs par défaut
    setDefaults();
}

// Définit les valeurs par défaut de la configuration
void ConfigManager::setDefaults() {
    // API de géolocalisation par défaut et sa clé (si nécessaire)
    configData["api_default"] = "ip-api.com";
    configData["api_keys"]["ip-api.com"] = ""; // ip-api.com est gratuit, pas de clé requise
    configData["api_keys"]["ipinfo.io"] = "YOUR_IPINFO_API_KEY"; // Exemple pour une API nécessitant une clé
    configData["api_keys"]["abstractapi.com"] = "YOUR_ABSTRACTAPI_API_KEY"; // Autre exemple

    // Préférences générales
    configData["display_verbose"] = false; // Affichage détaillé (pour les logs de curl)
    configData["history_file"] = "ip_nose_history.json"; // Nom du fichier d'historique
    configData["max_history_entries"] = 100; // Nombre max d'entrées dans l'historique
    configData["output_format"] = "text"; // "text", "json" (future fonctionnalité)
}

// Charge la configuration depuis le fichier
bool ConfigManager::loadConfig() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        // Le fichier n'existe pas ou ne peut pas être ouvert, ce n'est pas forcément une erreur.
        // Cela signifie que nous utiliserons les valeurs par défaut.
        std::cerr << TerminalDisplay::BRIGHT_BLACK << "Fichier de configuration '" << filePath << "' non trouvé ou inaccessible. Utilisation des valeurs par défaut." << TerminalDisplay::RESET << std::endl;
        setDefaults(); // Assurez-vous que les valeurs par défaut sont bien définies
        return false;
    }

    try {
        file >> configData; // Parse le JSON du fichier directement dans configData
        std::cout << TerminalDisplay::BRIGHT_GREEN << "Configuration chargée depuis '" << filePath << "'." << TerminalDisplay::RESET << std::endl;
        return true;
    } catch (const json::parse_error& e) {
        std::cerr << TerminalDisplay::RED << "Erreur de parsing JSON dans '" << filePath << "': " << e.what() << ". Utilisation des valeurs par défaut." << TerminalDisplay::RESET << std::endl;
        setDefaults(); // Recharger les valeurs par défaut en cas d'erreur de parsing
        return false;
    } catch (const std::exception& e) {
        std::cerr << TerminalDisplay::RED << "Erreur inattendue lors du chargement de la configuration: " << e.what() << ". Utilisation des valeurs par défaut." << TerminalDisplay::RESET << std::endl;
        setDefaults();
        return false;
    }
}

// Sauvegarde la configuration actuelle dans le fichier
bool ConfigManager::saveConfig() const {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << TerminalDisplay::RED << "Erreur: Impossible d'ouvrir le fichier '" << filePath << "' pour la sauvegarde." << TerminalDisplay::RESET << std::endl;
        return false;
    }

    try {
        // Sauvegarde le JSON avec une indentation de 4 espaces pour la lisibilité
        file << std::setw(4) << configData << std::endl;
        std::cout << TerminalDisplay::BRIGHT_GREEN << "Configuration sauvegardée dans '" << filePath << "'." << TerminalDisplay::RESET << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << TerminalDisplay::RED << "Erreur lors de la sauvegarde de la configuration dans '" << filePath << "': " << e.what() << TerminalDisplay::RESET << std::endl;
        return false;
    }
}

// Réinitialise la configuration à ses valeurs par défaut
void ConfigManager::resetToDefaults() {
    setDefaults();
    std::cout << TerminalDisplay::BRIGHT_YELLOW << "Configuration réinitialisée aux valeurs par défaut." << TerminalDisplay::RESET << std::endl;
}

// Affiche la configuration actuelle
void ConfigManager::displayConfig(std::ostream& os) const {
    using namespace TerminalDisplay;
    os << BOLD << BRIGHT_GREEN << "\n--- Configuration Actuelle ---" << RESET << std::endl;
    os << YELLOW << std::setw(4) << configData << RESET << std::endl; // Affiche le JSON formaté
    os << BOLD << BRIGHT_GREEN << "------------------------------" << RESET << std::endl;
}

