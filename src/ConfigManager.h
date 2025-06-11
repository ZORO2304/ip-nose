// src/ConfigManager.h
#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H
#include <iostream> // Pour std::ostream et std::cout
#include <string>
#include <fstream> // Pour la lecture/écriture de fichiers
#include "nlohmann/json.hpp" // Pour manipuler le JSON

using json = nlohmann::json;

class ConfigManager {
public:
    // Constructeur : prend le chemin du fichier de configuration en paramètre.
    ConfigManager(const std::string& configFilePath);

    // Charge la configuration depuis le fichier.
    // Retourne true si le chargement est un succès, false sinon.
    bool loadConfig();

    // Sauvegarde la configuration actuelle dans le fichier.
    // Retourne true si la sauvegarde est un succès, false sinon.
    bool saveConfig() const;

    // Réinitialise la configuration à ses valeurs par défaut.
    void resetToDefaults();

    // Méthodes pour obtenir les valeurs de configuration.
    // Utilise des templates pour pouvoir récupérer différents types (string, int, bool, etc.).
    template <typename T>
    T getValue(const std::string& key, const T& defaultValue) const {
        if (configData.count(key)) {
            // Tente de convertir la valeur JSON au type T.
            // Si la conversion échoue (type incompatible), une exception sera levée.
            // Nous gérons cela dans le try-catch du .cpp.
            try {
                return configData.at(key).get<T>();
            } catch (const json::type_error& e) {
                std::cerr << "Erreur de type pour la clé '" << key << "' dans la configuration: " << e.what() << std::endl;
                return defaultValue;
            }
        }
        return defaultValue;
    }

    // Méthodes pour définir les valeurs de configuration.
    template <typename T>
    void setValue(const std::string& key, const T& value) {
        configData[key] = value;
    }

    // Affiche la configuration actuelle (pour le débogage ou l'information).
    void displayConfig(std::ostream& os = std::cout) const;

private:
    std::string filePath;  // Chemin du fichier de configuration (ex: config.json)
    json configData;       // Objet JSON qui stockera la configuration

    // Valeurs par défaut de la configuration.
    // Nous définirons ici les API keys par défaut, l'API préférée, etc.
    void setDefaults();
};

#endif // CONFIG_MANAGER_H


