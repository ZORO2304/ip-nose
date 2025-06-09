// src/HistoryManager.h
#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "GeoLocationData.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// Structure pour représenter une entrée unique dans l'historique
struct HistoryEntry {
    // AJOUTE CETTE LIGNE : Constructeur par défaut
    HistoryEntry() = default;

    GeoLocationData data; // Les données de géolocalisation complètes
    std::string timestamp; // Date et heure de la recherche

    // Constructeur existant
    HistoryEntry(const GeoLocationData& d, const std::string& ts) : data(d), timestamp(ts) {}

    // Déclarations des fonctions friend pour la sérialisation/désérialisation JSON
    friend void to_json(json& j, const HistoryEntry& p);
    friend void from_json(const json& j, HistoryEntry& p);
};

// Définitions des fonctions friend to_json et from_json pour HistoryEntry (inchangées)
inline void to_json(json& j, const HistoryEntry& p) {
    j = json::object();
    j["data"] = p.data;
    j["timestamp"] = p.timestamp;
}

inline void from_json(const json& j, HistoryEntry& p) {
    j.at("data").get_to(p.data);
    j.at("timestamp").get_to(p.timestamp);
}

class HistoryManager {
public:
    HistoryManager(const std::string& historyFilePath, size_t maxEntries);
    void addEntry(const GeoLocationData& data);
    bool loadHistory();
    bool saveHistory() const;
    void displayHistory(std::ostream& os = std::cout) const;
    void clearHistory();
    size_t getEntryCount() const;

private:
    std::string filePath;
    size_t maxHistoryEntries;
    std::vector<HistoryEntry> history;

    std::string getCurrentTimestamp() const;
    void truncateHistory();
};

#endif // HISTORY_MANAGER_H

