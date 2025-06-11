// src/Utils.h
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <regex> // Pour la validation d'IP par expression régulière

// La classe Utils fournit des fonctions utilitaires statiques
// Cela signifie que tu n'as pas besoin de créer un objet Utils pour les utiliser.
// Tu peux les appeler directement via Utils::nomDeLaFonction(...).
class Utils {
public:
    // Valide si une chaîne de caractères est une adresse IPv4 valide.
    static bool isValidIPv4(const std::string& ip);

    // Valide si une chaîne de caractères est une adresse IPv6 valide.
    static bool isValidIPv6(const std::string& ip);

    // Valide si une chaîne de caractères est une adresse IP valide (IPv4 ou IPv6).
    static bool isValidIP(const std::string& ip);

    // Pourrait contenir d'autres fonctions utilitaires à l'avenir, par exemple:
    // static void logMessage(const std::string& message, const std::string& level = "INFO");
    // static std::string getTimestamp();
};

#endif // UTILS_H

