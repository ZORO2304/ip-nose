// src/Utils.cpp
#include "Utils.h"
#include <iostream> // Pour d'éventuels messages de débogage (bien que généralement non utilisé dans les utilitaires purs)

// Implémentation de la validation IPv4
bool Utils::isValidIPv4(const std::string& ip) {
    // Expression régulière pour IPv4
    // ^                 début de la chaîne
    // (?:               groupe non-capturant
    //   (?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)  correspond à un nombre de 0 à 255
    //   \.              suivi d'un point échappé
    // ){3}              répété 3 fois (pour les 3 premiers octets)
    // (?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)  le dernier octet
    // $                 fin de la chaîne
    const std::regex ipv4_regex(
        "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
        "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"
    );
    return std::regex_match(ip, ipv4_regex);
}

// Implémentation de la validation IPv6 (une version simplifiée mais fonctionnelle)
// Note: La validation complète d'IPv6 est très complexe à cause de ses nombreuses formes (compression, etc.).
// Cette regex couvre les formes les plus courantes et est un bon compromis pour un projet comme celui-ci.
// Pour une validation 100% complète, une bibliothèque dédiée ou une logique plus complexe serait nécessaire.
bool Utils::isValidIPv6(const std::string& ip) {
    // Regex pour les formes communes d'IPv6
    // Ceci couvre les blocs hexadécimaux et la compression ::
    // Elle ne couvre pas toutes les formes IPv6 (ex: IPv4-mapped IPv6 addresses)
    const std::regex ipv6_regex(
        "(([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}|"  // 1:2:3:4:5:6:7:8
        "([0-9a-fA-F]{1,4}:){1,7}:|"                   // 1::                          1:2:3::
        "([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}|"   // 1::4                         1:2:3::4
        "([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}|" // 1::3:4                       1:2:3::3:4
        "([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3}|" // 1::2:3:4                     1:2:3:4::2:3:4
        "([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}|" // 1::1:2:3:4                   1:2:3:4:5::2:3:4
        "([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5}|" // 1::1:2:3:4:5                 1:2:3:4:5:6::2:3:4
        "[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4}){1,6})|"  // ::2:3:4:5:6:7                ::1:2:3:4:5:6:7
        "::([0-9a-fA-F]{1,4}(:[0-9a-fA-F]{1,4}){1,6})?)" // ::                           ::1:2:3:4:5:6:7:8
    );
    return std::regex_match(ip, ipv6_regex);
}


// Implémentation de la validation IP générique (IPv4 ou IPv6)
bool Utils::isValidIP(const std::string& ip) {
    return isValidIPv4(ip) || isValidIPv6(ip);
}

