#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "GeoLocationData.h"
#include "TerminalDisplay.h"

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
