#include "HttpRequest.h"
#include <iostream>

// Constructeur
HttpRequest::HttpRequest() : verboseMode(false) {
    curl = curl_easy_init();
    if (curl == nullptr) {
        std::cerr << "Erreur: Impossible d'initialiser CURL." << std::endl;
        // Gérer l'erreur, par exemple, jeter une exception
    }
    // Configuration commune de CURL
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Suivre les redirections
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Ne pas vérifier le certificat SSL (pour HTTPS) - À éviter en production
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); // Ne pas vérifier le nom d'hôte SSL - À éviter en production
}

// Destructeur
HttpRequest::~HttpRequest() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
}

// Méthode GET
std::string HttpRequest::get(const std::string& url) {
    responseBuffer.clear(); // Vider le buffer avant chaque nouvelle requête
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    if (verboseMode) {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // Activer la sortie verbose de curl
    } else {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L); // Désactiver la sortie verbose
    }

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Erreur CURL: " << curl_easy_strerror(res) << std::endl;
        return ""; // Retourne une chaîne vide en cas d'erreur
    }
    return responseBuffer; // Retourne la réponse
}

// Callback statique
size_t HttpRequest::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Définir le mode verbose
void HttpRequest::setVerbose(bool verbose) {
    verboseMode = verbose;
}
