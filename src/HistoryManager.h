<<<<<<< HEAD
#ifndef HISTORYMANAGER_H
=======
ifndef HISTORYMANAGER_H
>>>>>>> 9621915b40066bc9ccea2304e6fbdf84277aee47
#define HISTORYMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "GeoLocationData.h"
#include "TerminalDisplay.h" // Assure-toi que c'est inclus

class HistoryManager {
public:
    HistoryManager(const std::string& filePath, size_t maxEntries = 100);
    void addEntry(const GeoLocationData& data);
    void displayHistory() const;
    void clearHistory();

private:
    std::string filePath;
    size_t maxEntries;
    std::vector<GeoLocationData> historyEntries;

    void loadHistory();
    void saveHistory();
};

#endif // HISTORYMANAGER_H
<<<<<<< HEAD

=======
>>>>>>> 9621915b40066bc9ccea2304e6fbdf84277aee47
