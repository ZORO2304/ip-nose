// src/IpGeoLocator.cpp
#include "IpGeoLocator.h"
#include <iostream>

// Définition des constantes statiques
const std::string IpGeoLocator::GEO_API_URL = "http://ip-api.com/json/";
const std::string IpGeoLocator::PUBLIC_IP_DETECTOR_URL = "https://api.ipify.org";

// Constructeur
IpGeoLocator::IpGeoLocator(HttpRequest& req) : httpRequest(req), lastErrorMsg("") {
    // Le constructeur initialise la référence à l'objet HttpRequest.
    // Il peut aussi configurer des options par défaut pour HttpRequest ici,
    // comme le User-Agent ou le timeout, si cela n'est pas déjà fait ailleurs.
    httpRequest.setUserAgent("ip-nose-geo-locator/1.0");
    httpRequest.setTimeout(15); // Timeout de 15 secondes pour les requêtes API
}

// Méthode pour géolocaliser une IP donnée
GeoLocationData IpGeoLocator::locate(const std::string& ipAddress) {
    lastErrorMsg.clear(); // Réinitialise le message d'erreur
    GeoLocationData data; // Crée un objet pour stocker les résultats
    data.setIpAddress(ipAddress); // Enregistre l'IP que nous tentons de localiser

    // Construire l'URL complète pour la requête de géolocalisation
    std::string fullUrl = GEO_API_URL + ipAddress;
    httpRequest.setUrl(fullUrl);

    // Effectuer la requête HTTP
    std::string jsonResponse = httpRequest.get();

    // Vérifier s'il y a eu une erreur au niveau de la requête HTTP (CURL)
    if (httpRequest.getLastError() != CURLE_OK) {
        lastErrorMsg = "Erreur HTTP lors de la géolocalisation de " + ipAddress + ": " + httpRequest.getLastErrorString();
        data.setStatus("fail");
        data.setMessage(lastErrorMsg);
        std::cerr << lastErrorMsg << std::endl;
        return data; // Retourne les données avec le statut d'échec
    }

    // Si la requête HTTP a réussi, parser la réponse JSON
    if (!jsonResponse.empty()) {
        data = parseJsonResponse(jsonResponse, ipAddress);
        // La méthode parseJsonResponse gère déjà les erreurs de parsing JSON
        // et les statuts "fail" de l'API.
    } else {
        lastErrorMsg = "Réponse vide reçue pour la géolocalisation de " + ipAddress;
        data.setStatus("fail");
        data.setMessage(lastErrorMsg);
        std::cerr << lastErrorMsg << std::endl;
    }
    return data;
}

// Méthode pour obtenir l'IP publique de la machine locale
std::string IpGeoLocator::getPublicIp() {
    lastErrorMsg.clear(); // Réinitialise le message d'erreur

    httpRequest.setUrl(PUBLIC_IP_DETECTOR_URL);
    std::string publicIp = httpRequest.get();

    if (httpRequest.getLastError() != CURLE_OK) {
        lastErrorMsg = "Erreur HTTP lors de la détection de l'IP publique: " + httpRequest.getLastErrorString();
        std::cerr << lastErrorMsg << std::endl;
        return ""; // Retourne une chaîne vide en cas d'erreur
    }

    // ipify.org renvoie juste l'IP en texte brut, pas du JSON
    if (publicIp.empty()) {
        lastErrorMsg = "Impossible de récupérer l'IP publique, réponse vide.";
        std::cerr << lastErrorMsg << std::endl;
    }

    return publicIp;
}

// Méthode privée pour parser la réponse JSON et remplir GeoLocationData
GeoLocationData IpGeoLocator::parseJsonResponse(const std::string& jsonResponse, const std::string& targetIp) {
    GeoLocationData data;
    data.setIpAddress(targetIp); // S'assurer que l'IP est définie dans l'objet de données

    try {
        json j = json::parse(jsonResponse);

        // Vérifier le statut de la réponse de l'API (ip-api.com)
        std::string status = j.value("status", "fail");
        data.setStatus(status);

        if (status == "success") {
            data.setCountry(j.value("country", "N/A"));
            data.setCountryCode(j.value("countryCode", "N/A"));
            data.setRegion(j.value("region", "N/A"));
            data.setRegionName(j.value("regionName", "N/A"));
            data.setCity(j.value("city", "N/A"));
            data.setZip(j.value("zip", "N/A"));
            data.setLat(j.value("lat", 0.0));
            data.setLon(j.value("lon", 0.0));
            data.setTimezone(j.value("timezone", "N/A"));
            data.setIsp(j.value("isp", "N/A"));
            data.setOrg(j.value("org", "N/A"));
            data.setAs(j.value("as", "N/A"));
            data.setReverse(j.value("reverse", "N/A"));
            data.setMobile(j.value("mobile", false)); // Booléen
            data.setProxy(j.value("proxy", false));   // Booléen
            data.setHosting(j.value("hosting", false)); // Booléen
        } else {
            // Si le statut est "fail", l'API peut fournir un message d'erreur.
            data.setMessage(j.value("message", "Erreur inconnue de l'API de géolocalisation."));
            lastErrorMsg = "API de géolocalisation a rapporté un échec: " + data.getMessage();
            std::cerr << lastErrorMsg << std::endl;
        }

    } catch (const json::parse_error& e) {
        lastErrorMsg = "Erreur de parsing JSON pour l'IP " + targetIp + ": " + e.what();
        data.setStatus("fail");
        data.setMessage(lastErrorMsg);
        std::cerr << lastErrorMsg << std::endl;
    } catch (const std::exception& e) {
        lastErrorMsg = "Erreur inattendue lors du traitement de la réponse pour l'IP " + targetIp + ": " + e.what();
        data.setStatus("fail");
        data.setMessage(lastErrorMsg);
        std::cerr << lastErrorMsg << std::endl;
    }

    return data;
}

// Retourne le dernier message d'erreur
std::string IpGeoLocator::getLastError() const {
    return lastErrorMsg;
}

// Indique si une erreur est survenue
bool IpGeoLocator::hasError() const {
    return !lastErrorMsg.empty();
}


