#ifndef GEOLOCATIONDATA_H
#define GEOLOCATIONDATA_H

#include <string>
#include <iostream>
#include <nlohmann/json.hpp> // Inclure nlohmann/json.hpp
#include "TerminalDisplay.h"

// Déclaration de la classe GeoLocationData
class GeoLocationData {
public:
    // Membres publics pour faciliter la sérialisation/désérialisation avec nlohmann/json
    // Et pour correspondre aux noms d'API courants (lat, lon)
    std::string ip;
    std::string country;
    std::string countryCode;
    std::string regionName;
    std::string city;
    std::string zip;
    double lat; // Rendu public pour nlohmann/json et direct access (comme l'API)
    double lon; // Rendu public pour nlohmann/json et direct access (comme l'API)
    std::string timezone;
    std::string isp;
    std::string org;
    std::string as;
    std::string status;
    std::string message; // Pour les messages d'erreur de l'API par exemple

    // Ces membres semblent être spécifiques à des APIs et si elles ne sont pas toujours présentes,
    // nlohmann::json gérera les champs manquants si tu les laisses publics dans le constructeur.
    // Si tu avais 'region', 'reverse', 'mobile', 'proxy', 'hosting', il faut les ajouter ici aussi
    // et les implémenter dans le .cpp si tu veux qu'ils soient sérialisés.
    // Pour l'instant, je m'en tiens aux membres que tu as déjà définis ou que j'ai ajoutés précédemment.
    // Par exemple, si tu as bien `region`, `reverse`, etc. dans ton .cpp, décommente ou ajoute-les ici:
    // std::string region;
    // std::string reverse;
    // bool mobile;
    // bool proxy;
    // bool hosting;


    // Constructeur par défaut
    GeoLocationData() : ip("N/A"), country("N/A"), countryCode("N/A"), regionName("N/A"),
                        city("N/A"), zip("N/A"), lat(0.0), lon(0.0),
                        timezone("N/A"), isp("N/A"), org("N/A"), as("N/A"), status("N/A"), message("N/A") {}

    // Méthode pour afficher les détails
    void display() const; // Déclaration uniquement, l'implémentation est dans le .cpp

    // Pas besoin de getters/setters si les membres sont publics et qu'ils sont utilisés directement
    // par nlohmann/json via les fonctions to_json/from_json que nous allons définir.
    // Cependant, si d'autres parties de ton code utilisent les getters/setters, tu peux les conserver.
    // Pour la clarté et pour éviter des conflits, je les ai retirés du .h ici si les membres sont publics.
    // Si tu veux les garder, les membres privés devront être de retour et les getters/setters gérés.
    // Pour la sérialisation avec nlohmann/json, il est souvent plus simple de rendre les membres publics
    // ou de définir les fonctions friend `to_json`/`from_json` qui accèdent aux membres privés.
    // Gardons-les publics pour la sérialisation simple.
};

// Fonctions to_json et from_json pour nlohmann/json
// Ces fonctions doivent être dans le même namespace que GeoLocationData
// ou dans le namespace global si GeoLocationData est dans le namespace global.
// Elles permettent à nlohmann::json de sérialiser/désérialiser GeoLocationData.
void to_json(nlohmann::json& j, const GeoLocationData& p);
void from_json(const nlohmann::json& j, GeoLocationData& p);

#endif // GEOLOCATIONDATA_H
