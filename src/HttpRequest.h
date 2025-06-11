#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>
#include <curl/curl.h> // Inclure la bibliothèque curl

class HttpRequest {
public:
    HttpRequest();
    ~HttpRequest();

    // Méthode GET pour effectuer une requête HTTP
    std::string get(const std::string& url); // Assure-toi que cette ligne est correcte

    void setVerbose(bool verbose);

private:
    CURL* curl; // Handle CURL
    std::string responseBuffer; // Buffer pour stocker la réponse HTTP
    bool verboseMode; // Pour activer/désactiver la sortie verbose de curl

    // Callback statique pour écrire les données reçues
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};

#endif // HTTPREQUEST_H

