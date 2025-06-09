// src/HttpRequest.h
#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>
#include <map>
#include <memory> // Pour std::unique_ptr
#include <vector> // Pour stocker les headers de curl
#include <curl/curl.h> // <-- AJOUTE CETTE LIGNE ICI !

// La forward declaration 'struct curl_slist;' n'est plus nécessaire ici
// car <curl/curl.h> la fournit déjà.

class HttpRequest {
public:
    // Constructeur et destructeur
    HttpRequest();
    ~HttpRequest();

    // Méthodes pour configurer la requête
    void setUrl(const std::string& url);
    void addHeader(const std::string& key, const std::string& value);
    void setUserAgent(const std::string& userAgent);
    void setTimeout(long seconds);
    void setVerbose(bool verbose); // Pour le mode débug de curl

    // Méthode pour exécuter la requête GET
    std::string get();

    // Méthodes pour obtenir des informations après la requête
    int getLastError() const;
    std::string getLastErrorString() const;
    long getHttpResponseCode() const;

private:
    // CURL est maintenant connu grâce à l'inclusion de <curl/curl.h>
    std::unique_ptr<CURL, void(*)(CURL*)> curl_handle;
    std::string url;
    std::string responseBuffer; // Buffer pour stocker la réponse de l'API
    std::map<std::string, std::string> customHeaders; // Pour stocker les headers personnalisés
    long timeout;
    bool verboseOutput; // Flag pour l'output verbeux de curl

    int lastError; // Code d'erreur de la dernière opération curl
    std::string lastErrorString; // Message d'erreur de la dernière opération curl
    long httpResponseCode; // Code de réponse HTTP (ex: 200, 404, 500)

    // Pointeur vers la liste des headers gérée par curl_slist
    curl_slist* curlHeadersList;

    // Fonction de rappel statique pour CURL
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

    // Initialise les ressources de CURL
    void initializeCurl();
    // Nettoie les ressources spécifiques à la requête
    void cleanupCurlResources();
};

#endif // HTTP_REQUEST_H

