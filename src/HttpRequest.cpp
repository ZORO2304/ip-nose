// src/HttpRequest.cpp
#include "HttpRequest.h"
#include <iostream>

// Constructeur de la classe HttpRequest
HttpRequest::HttpRequest()
    : curl_handle(nullptr, curl_easy_cleanup), // Initialise le unique_ptr avec le pointeur nul et la fonction de nettoyage
      timeout(10), // Timeout par défaut de 10 secondes
      verboseOutput(false),
      lastError(CURLE_OK), // Initialise sans erreur
      httpResponseCode(0),
      curlHeadersList(nullptr) // Initialise la liste des headers à nullptr
{
    // curl_global_init() doit être appelé au moins une fois par application avant d'utiliser curl
    // C'est souvent fait au début de main ou dans une fonction d'initialisation globale.
    // Nous l'appelons ici pour s'assurer qu'il est fait, mais attention si plusieurs instances de HttpRequest.
    // Pour une application comme ip-nose, un seul appel global dans main est préférable.
    // Pour l'instant, on le met ici pour la complétude du module.
    curl_global_init(CURL_GLOBAL_DEFAULT);
    initializeCurl();
}

// Destructeur de la classe HttpRequest
HttpRequest::~HttpRequest() {
    cleanupCurlResources(); // Nettoie la liste des headers si elle existe
    // curl_easy_cleanup est appelée automatiquement par unique_ptr
    // curl_global_cleanup() devrait être appelé une seule fois à la fin du programme.
}

// Fonction de rappel statique pour CURL
// Cette fonction est appelée par CURL chaque fois qu'il reçoit des données.
// Elle stocke les données dans le buffer de la classe.
size_t HttpRequest::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    // Cast le pointeur utilisateur en std::string* et ajoute les données
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Initialise le handle CURL
void HttpRequest::initializeCurl() {
    // Si un handle existe déjà, le nettoyer avant d'en créer un nouveau
    if (curl_handle) {
        curl_handle.reset(); // Cela appelle curl_easy_cleanup
    }
    CURL* handle = curl_easy_init();
    if (!handle) {
        std::cerr << "Erreur: Impossible d'initialiser CURL." << std::endl;
        // Gérer l'erreur, peut-être lancer une exception
        lastError = -1; // Code d'erreur personnalisé pour l'initialisation
        lastErrorString = "Failed to initialize CURL handle.";
        return;
    }
    curl_handle.reset(handle); // Attribue le handle au unique_ptr

    // Configuration par défaut
    curl_easy_setopt(curl_handle.get(), CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl_handle.get(), CURLOPT_WRITEDATA, &responseBuffer);
    curl_easy_setopt(curl_handle.get(), CURLOPT_FOLLOWLOCATION, 1L); // Suivre les redirections
}

// Nettoie les ressources spécifiques à la requête (comme la liste des headers)
void HttpRequest::cleanupCurlResources() {
    if (curlHeadersList) {
        curl_slist_free_all(curlHeadersList); // Libère la mémoire allouée pour les headers
        curlHeadersList = nullptr;
    }
}

// Définit l'URL pour la requête
void HttpRequest::setUrl(const std::string& url) {
    this->url = url;
}

// Ajoute un en-tête HTTP personnalisé
void HttpRequest::addHeader(const std::string& key, const std::string& value) {
    customHeaders[key] = value;
}

// Définit le User-Agent
void HttpRequest::setUserAgent(const std::string& userAgent) {
    if (curl_handle) {
        curl_easy_setopt(curl_handle.get(), CURLOPT_USERAGENT, userAgent.c_str());
    }
}

// Définit le timeout pour la requête
void HttpRequest::setTimeout(long seconds) {
    timeout = seconds;
    if (curl_handle) {
        curl_easy_setopt(curl_handle.get(), CURLOPT_TIMEOUT, timeout);
    }
}

// Active/désactive le mode verbeux de CURL
void HttpRequest::setVerbose(bool verbose) {
    verboseOutput = verbose;
    if (curl_handle) {
        curl_easy_setopt(curl_handle.get(), CURLOPT_VERBOSE, verbose ? 1L : 0L);
    }
}

// Exécute la requête GET
std::string HttpRequest::get() {
    responseBuffer.clear(); // Nettoie le buffer de la réponse précédente
    lastError = CURLE_OK; // Réinitialise l'erreur
    lastErrorString.clear();
    httpResponseCode = 0;

    if (!curl_handle) {
        lastErrorString = "CURL handle not initialized.";
        lastError = -1; // Code d'erreur personnalisé
        return "";
    }

    if (url.empty()) {
        lastErrorString = "URL not set.";
        lastError = -2; // Code d'erreur personnalisé
        return "";
    }

    // Configure l'URL
    curl_easy_setopt(curl_handle.get(), CURLOPT_URL, url.c_str());

    // Applique le timeout
    curl_easy_setopt(curl_handle.get(), CURLOPT_TIMEOUT, timeout);

    // Applique le mode verbeux
    curl_easy_setopt(curl_handle.get(), CURLOPT_VERBOSE, verboseOutput ? 1L : 0L);

    // Ajoute les en-têtes personnalisés
    cleanupCurlResources(); // Nettoie les headers précédents
    for (const auto& pair : customHeaders) {
        std::string header = pair.first + ": " + pair.second;
        curlHeadersList = curl_slist_append(curlHeadersList, header.c_str());
    }
    if (curlHeadersList) {
        curl_easy_setopt(curl_handle.get(), CURLOPT_HTTPHEADER, curlHeadersList);
    }

    // Exécute la requête
    CURLcode res = curl_easy_perform(curl_handle.get());

    lastError = res; // Stocke le code d'erreur CURL
    if (res != CURLE_OK) {
        lastErrorString = curl_easy_strerror(res);
        std::cerr << "Erreur HTTP Request: " << lastErrorString << " (Code: " << res << ")" << std::endl;
        return ""; // Retourne une chaîne vide en cas d'erreur
    }

    // Récupère le code de réponse HTTP
    curl_easy_getinfo(curl_handle.get(), CURLINFO_RESPONSE_CODE, &httpResponseCode);

    return responseBuffer; // Retourne le contenu de la réponse
}

// Retourne le dernier code d'erreur CURL
int HttpRequest::getLastError() const {
    return lastError;
}

// Retourne le message d'erreur de la dernière opération CURL
std::string HttpRequest::getLastErrorString() const {
    return lastErrorString;
}

// Retourne le code de réponse HTTP de la dernière requête
long HttpRequest::getHttpResponseCode() const {
    return httpResponseCode;
}


