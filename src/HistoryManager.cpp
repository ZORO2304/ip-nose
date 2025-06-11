#include "HistoryManager.h"
#include <algorithm> // Pour std::reverse, std::remove_if
#include <iomanip>   // Pour std::setw, std::left
#include <sstream>   // Pour std::istringstream

HistoryManager::HistoryManager(const std::string& filePath, size_t maxEntries)
    : filePath(filePath), maxEntries(maxEntries) {
    loadHistory();
}

void HistoryManager::addEntry(const GeoLocationData& data) {
    // Ajoute uniquement les entrées réussies ou les entrées avec un message spécifique si tu veux les enregistrer
    // Correction ici : utilise getStatus() à la place de isSuccess()
    if (data.status == "success") { // Accède directement au membre 'status' qui est public

        historyEntries.push_back(data);
        // Si l'historique dépasse la taille maximale, supprime les plus anciennes
        if (historyEntries.size() > maxEntries) {
            historyEntries.erase(historyEntries.begin());
        }
        saveHistory();
        std::cout << TerminalDisplay::GREEN << "[Historique] Entrée ajoutée." << TerminalDisplay::RESET << std::endl;
    } else {
        std::cout << TerminalDisplay::YELLOW << "[Historique] Entrée non ajoutée (status non 'success')." << TerminalDisplay::RESET << std::endl;
    }
}


void HistoryManager::displayHistory() const {
    using namespace TerminalDisplay;
    if (historyEntries.empty()) {
        std::cout << YELLOW << "L'historique est vide." << RESET << std::endl;
        return;
    }

    std::cout << BOLD << BRIGHT_GREEN << "\n--- Historique des Recherches (" << historyEntries.size() << " entrées) ---" << RESET << std::endl;

    // Affiche les entrées de la plus récente à la plus ancienne
    std::vector<GeoLocationData> reversedHistory = historyEntries;
    std::reverse(reversedHistory.begin(), reversedHistory.end()); // Inverse l'ordre

    for (size_t i = 0; i < reversedHistory.size(); ++i) {
        std::cout << BRIGHT_CYAN << "Entrée #" << (reversedHistory.size() - i) << RESET << std::endl;
        // Utilise la méthode display() de GeoLocationData, qui n'attend pas d'argument
        reversedHistory[i].display();
        std::cout << std::endl;
    }
    std::cout << BOLD << BRIGHT_GREEN << "------------------------------------------" << RESET << std::endl;
}

void HistoryManager::clearHistory() {
    historyEntries.clear();
    saveHistory();
    std::cout << TerminalDisplay::GREEN << "[Historique] Historique effacé." << TerminalDisplay::RESET << std::endl;
}

void HistoryManager::loadHistory() {
    std::ifstream ifs(filePath);
    if (!ifs.is_open()) {
        std::cerr << TerminalDisplay::YELLOW << "[Historique] Fichier historique non trouvé : " << filePath << ". Création d'un nouveau." << TerminalDisplay::RESET << std::endl;
        return;
    }

    try {
        nlohmann::json j;
        ifs >> j;
        // Désérialise directement en vector<GeoLocationData> grâce à from_json
        historyEntries = j.get<std::vector<GeoLocationData>>();
        // S'assurer que l'historique ne dépasse pas maxEntries après chargement
        if (historyEntries.size() > maxEntries) {
            historyEntries.erase(historyEntries.begin(), historyEntries.begin() + (historyEntries.size() - maxEntries));
            std::cout << TerminalDisplay::YELLOW << "[Historique] Historique tronqué à " << maxEntries << " entrées lors du chargement." << TerminalDisplay::RESET << std::endl;
        }
        std::cout << TerminalDisplay::GREEN << "[Historique] " << historyEntries.size() << " entrées chargées." << TerminalDisplay::RESET << std::endl;
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << TerminalDisplay::BRIGHT_RED << "[Historique ERROR] Erreur de parsing du fichier historique JSON : " << e.what() << ". Fichier corrompu ?" << TerminalDisplay::RESET << std::endl;
        historyEntries.clear(); // Efface l'historique corrompu
    } catch (const nlohmann::json::exception& e) { // Autres erreurs liées à JSON
        std::cerr << TerminalDisplay::BRIGHT_RED << "[Historique ERROR] Erreur JSON lors du chargement de l'historique : " << e.what() << TerminalDisplay::RESET << std::endl;
        historyEntries.clear();
    }
}

void HistoryManager::saveHistory() {
    std::ofstream ofs(filePath);
    if (!ofs.is_open()) {
        std::cerr << TerminalDisplay::BRIGHT_RED << "[Historique ERROR] Impossible d'ouvrir le fichier historique pour écriture : " << filePath << TerminalDisplay::RESET << std::endl;
        return;
    }

    try {
        nlohmann::json j = historyEntries; // Sérialise directement le vector<GeoLocationData>
        ofs << std::setw(4) << j << std::endl; // Écrit le JSON formaté
        std::cout << TerminalDisplay::GREEN << "[Historique] Historique sauvegardé dans " << filePath << "." << TerminalDisplay::RESET << std::endl;
    } catch (const nlohmann::json::exception& e) {
        std::cerr << TerminalDisplay::BRIGHT_RED << "[Historique ERROR] Erreur JSON lors de la sauvegarde de l'historique : " << e.what() << TerminalDisplay::RESET << std::endl;
    }
}
