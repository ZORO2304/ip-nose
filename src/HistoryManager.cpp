// src/HistoryManager.cpp
#include "HistoryManager.h"
#include <iostream>
#include <algorithm> // Pour std::reverse
#include <vector>    // Pour std::vector (bien que déjà inclus via HistoryManager.h)
#include "TerminalDisplay.h" // Pour les couleurs

// Constructeur
HistoryManager::HistoryManager(const std::string& historyFilePath, size_t maxEntries)
    : filePath(historyFilePath), maxHistoryEntries(maxEntries) {
    // Tente de charger l'historique existant au démarrage
    loadHistory();
}

// Génère un horodatage actuel au format string
std::string HistoryManager::getCurrentTimestamp() const {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&currentTime); // Note: std::localtime n'est pas thread-safe, mais ok pour cet usage

    // Format YYYY-MM-DD HH:MM:SS
    std::stringstream ss;
    ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// Ajoute une nouvelle entrée à l'historique
void HistoryManager::addEntry(const GeoLocationData& data) {
    // N'ajoute les entrées d'échec de géolocalisation à l'historique que si tu le souhaites.
    // Pour l'instant, on n'ajoute que les succès.
    if (data.isSuccess()) {
        history.emplace_back(data, getCurrentTimestamp());
        truncateHistory(); // S'assure que l'historique ne dépasse pas la taille maximale
        saveHistory();     // Sauvegarde automatiquement après chaque ajout
    } else {
        std::cerr << TerminalDisplay::YELLOW << "Note: La géolocalisation de '" << data.getIpAddress() << "' a échoué. Non ajoutée à l'historique." << TerminalDisplay::RESET << std::endl;
    }
}

// Truncate l'historique si sa taille dépasse maxHistoryEntries
void HistoryManager::truncateHistory() {
    if (history.size() > maxHistoryEntries) {
        // Supprime les entrées les plus anciennes (au début du vecteur)
        history.erase(history.begin(), history.begin() + (history.size() - maxHistoryEntries));
    }
}

// Charge l'historique depuis le fichier
bool HistoryManager::loadHistory() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << TerminalDisplay::BRIGHT_BLACK << "Fichier d'historique '" << filePath << "' non trouvé ou inaccessible. L'historique sera vide." << TerminalDisplay::RESET << std::endl;
        return false;
    }

    try {
        json j;
        file >> j;

        // Désérialiser le JSON dans le vecteur d'historique manuellement
        history.clear(); // S'assurer que le vecteur est vide avant de le remplir
        if (j.is_array()) { // S'assurer que le JSON est un tableau
            for (const auto& entry_json : j) {
                try {
                    // Crée une instance vide
                    HistoryEntry entry;
                    // Appelle explicitement from_json pour remplir l'instance
                    from_json(entry_json, entry);
                    // Ajoute l'instance remplie au vecteur
                    history.push_back(entry);
                } catch (const json::exception& e) {
                    std::cerr << TerminalDisplay::RED << "Avertissement: Erreur lors de la lecture d'une entrée de l'historique : " << e.what() << TerminalDisplay::RESET << std::endl;
                    // On continue, ignorant l'entrée corrompue
                }
            }
        } else {
            std::cerr << TerminalDisplay::RED << "Avertissement: Le fichier d'historique n'est pas un tableau JSON valide. L'historique sera vide." << TerminalDisplay::RESET << std::endl;
            history.clear();
        }

        // S'assurer que l'historique chargé ne dépasse pas la taille maximale
        truncateHistory();
        std::cout << TerminalDisplay::BRIGHT_GREEN << "Historique chargé depuis '" << filePath << "' (" << history.size() << " entrées)." << TerminalDisplay::RESET << std::endl;
        return true;
    } catch (const json::parse_error& e) {
        std::cerr << TerminalDisplay::BRIGHT_RED << "Erreur de parsing JSON dans le fichier d'historique '" << filePath << "': " << e.what() << ". L'historique sera vide." << TerminalDisplay::RESET << std::endl;
        history.clear(); // Vide l'historique en cas d'erreur de parsing
        return false;
    } catch (const std::exception& e) {
        std::cerr << TerminalDisplay::BRIGHT_RED << "Erreur inattendue lors du chargement de l'historique: " << e.what() << ". L'historique sera vide." << TerminalDisplay::RESET << std::endl;
        history.clear();
        return false;
    }
}

// Sauvegarde l'historique actuel dans le fichier
bool HistoryManager::saveHistory() const {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << TerminalDisplay::RED << "Erreur: Impossible d'ouvrir le fichier '" << filePath << "' pour la sauvegarde de l'historique." << TerminalDisplay::RESET << std::endl;
        return false;
    }

    try {
        // Sauvegarde l'historique sous forme de tableau JSON
        file << std::setw(4) << json(history) << std::endl;
        // std::cout << "Historique sauvegardé dans '" << filePath << "'." << std::endl; // Commenté pour éviter le spam en console
        return true;
    } catch (const std::exception& e) {
        std::cerr << TerminalDisplay::RED << "Erreur lors de la sauvegarde de l'historique dans '" << filePath << "': " << e.what() << TerminalDisplay::RESET << std::endl;
        return false;
    }
}

// Affiche tout l'historique
void HistoryManager::displayHistory(std::ostream& os) const {
    using namespace TerminalDisplay;

    if (history.empty()) {
        os << YELLOW << "L'historique est vide." << RESET << std::endl;
        return;
    }

    os << BOLD << BRIGHT_GREEN << "\n--- Historique des Recherches (" << history.size() << " entrées) ---" << RESET << std::endl;
    // Afficher du plus récent au plus ancien
    // On copie et inverse pour ne pas modifier l'original.
    std::vector<HistoryEntry> reversedHistory = history;
    std::reverse(reversedHistory.begin(), reversedHistory.end());

    for (size_t i = 0; i < reversedHistory.size(); ++i) {
        os << BOLD << "Recherche #" << (reversedHistory.size() - i) << " - Date: " << BRIGHT_BLACK << reversedHistory[i].timestamp << RESET << std::endl;
        reversedHistory[i].data.display(os); // Utilise la méthode display de GeoLocationData (qui sera colorée)
        os << BOLD << BRIGHT_GREEN << "------------------------------------------" << RESET << std::endl;
    }
    os << BOLD << BRIGHT_GREEN << "Fin de l'historique." << RESET << std::endl;
}

// Efface tout l'historique
void HistoryManager::clearHistory() {
    history.clear();
    saveHistory(); // Sauvegarde un fichier vide pour persister l'effacement
    std::cout << TerminalDisplay::BRIGHT_YELLOW << "Historique effacé." << TerminalDisplay::RESET << std::endl;
}

// Retourne le nombre d'entrées
size_t HistoryManager::getEntryCount() const {
    return history.size();
}

