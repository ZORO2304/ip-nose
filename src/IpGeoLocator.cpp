#include "IpGeoLocator.h"
#include <nlohmann/json.hpp> // Pour le parsing JSON
#include <iostream>

// Implémentation du constructeur
IpGeoLocator::IpGeoLocator(HttpRequest& req) : httpRequest(req) {
    // Les membres de GeoLocationData sont maintenant publics, donc on n'utilise plus les setters ici
}

// Fonction pour récupérer l'IP publique de l'utilisateur
std::string IpGeoLocator::getPublicIp() {
    std::string publicIpEndpoint = "https://api.ipify.org"; // Un service simple pour obtenir l'IP publique
    std::string response = httpRequest.get(publicIpEndpoint);

    if (response.empty()) {
        std::cerr << TerminalDisplay::BRIGHT_RED << "Erreur: Impossible de récupérer l'IP publique. Réponse vide." << TerminalDisplay::RESET << std::endl;
        return "";
    }

    // api.ipify.org retourne juste l'IP en texte brut
    // Assumons que la réponse est propre et est l'IP
    std::cout << TerminalDisplay::GREEN << "Votre IP publique : " << response << TerminalDisplay::RESET << std::endl;
    return response;
}

// Fonction pour géolocaliser une IP donnée
GeoLocationData IpGeoLocator::locate(const std::string& ipAddress) {
    GeoLocationData data; // Crée un nouvel objet GeoLocationData

    // Stocke l'IP que nous tentons de localiser directement dans le membre public 'ip'
    data.ip = ipAddress; // Utilise le membre public 'ip'

    std::string apiUrl = "http://ip-api.com/json/" + ipAddress;
    // Ajoute un paramètre fields pour obtenir les champs dont tu as besoin et potentiellement le message d'erreur
    apiUrl += "?fields=status,message,country,countryCode,regionName,city,zip,lat,lon,timezone,isp,org,as,query";

    std::string jsonResponse = httpRequest.get(apiUrl);

    if (jsonResponse.empty()) {
        std::cerr << TerminalDisplay::BRIGHT_RED << "Erreur: Réponse vide de l'API de géolocalisation." << TerminalDisplay::RESET << std::endl;
        // Met à jour le statut et le message directement
        data.status = "fail";
        data.message = "Empty API response";
        return data;
    }

    try {
        nlohmann::json j = nlohmann::json::parse(jsonResponse);

        // Assigner les valeurs directement aux membres publics de GeoLocationData
        // Utilise .value() pour obtenir une valeur par défaut si le champ est absent
        std::string status = j.value("status", "fail");
        data.status = status; // Assigner le statut directement

        if (status == "success") {
            data.country = j.value("country", "N/A");
            data.countryCode = j.value("countryCode", "N/A");
            data.regionName = j.value("regionName", "N/A");
            data.city = j.value("city", "N/A");
            data.zip = j.value("zip", "N/A");
            data.lat = j.value("lat", 0.0);
            data.lon = j.value("lon", 0.0);
            data.timezone = j.value("timezone", "N/A");
            data.isp = j.value("isp", "N/A");
            data.org = j.value("org", "N/A");
            data.as = j.value("as", "N/A");
            data.message = ""; // Pas de message d'erreur en cas de succès
            // data.ip = j.value("query", ipAddress); // L'API renvoie la même IP, mais tu peux la mettre à jour
        } else {
            // Si le statut est "fail", récupère le message d'erreur de l'API
            data.message = j.value("message", "Unknown error");
        }
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << TerminalDisplay::BRIGHT_RED << "Erreur de parsing JSON pour la géolocalisation : " << e.what() << TerminalDisplay::RESET << std::endl;
        data.status = "fail";
        data.message = "JSON parsing error: " + std::string(e.what());
    } catch (const nlohmann::json::exception& e) {
        std::cerr << TerminalDisplay::BRIGHT_RED << "Erreur JSON pour la géolocalisation : " << e.what() << TerminalDisplay::RESET << std::endl;
        data.status = "fail";
        data.message = "JSON error: " + std::string(e.what());
    }

    return data;
}
