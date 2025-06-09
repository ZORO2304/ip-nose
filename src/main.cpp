// src/main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory> // Pour std::unique_ptr
#include <algorithm> // Pour std::transform
#include <cctype>    // Pour ::tolower
#include <thread>   // Pour std::this_thread::sleep_for
#include <chrono>   // Pour std::chrono::milliseconds
#include <random>   // Pour std::default_random_engine, std::uniform_int_distribution
#include <fstream>  // Pour la lecture de fichiers (banner.txt)

#include "HttpRequest.h"
#include "GeoLocationData.h"
#include "IpGeoLocator.h"
#include "Utils.h"
#include "ConfigManager.h"
#include "HistoryManager.h"
#include "TerminalDisplay.h" // Pour les couleurs et l'affichage terminal

// Prototypes des fonctions d'aide et globales
void displayHelp();
void initializeGlobalCurl();
void cleanupGlobalCurl();

void displayMatrixIntro();
void displayCredits();
void displayWelcomeBanner(); // Son implémentation va maintenant lire uniquement banner.txt

int main(int argc, char* argv[]) {
    // Initialisation globale de Curl. Très important : à faire une seule fois.
    initializeGlobalCurl();

    // Afficher une bannière de bienvenue / intro (Matrix)
    displayWelcomeBanner();
    // displayMatrixIntro(); // Optionnel: activer une intro plus longue et animée (décommenter si désiré)

    // Chemin par défaut pour le fichier de configuration
    const std::string configFilePath = "config.json";
    ConfigManager config(configFilePath);
    config.loadConfig();

    const std::string historyFilePath = config.getValue("history_file", std::string("ip_nose_history.json"));
    const size_t maxHistoryEntries = config.getValue("max_history_entries", 100);

    HistoryManager history(historyFilePath, maxHistoryEntries);

    HttpRequest httpRequest;
    httpRequest.setVerbose(config.getValue("display_verbose", false));

    IpGeoLocator locator(httpRequest);

    // --- Traitement des arguments de la ligne de commande ---
    if (argc < 2) {
        displayHelp();
        std::cout << "\n" << TerminalDisplay::BOLD << TerminalDisplay::GREEN << "Veuillez entrer une adresse IP à géolocaliser (ou 'q' pour quitter) : " << TerminalDisplay::RESET;
        std::string inputIp;
        std::getline(std::cin, inputIp);
        if (inputIp.empty() || inputIp == "q" || inputIp == "Q") {
            std::cout << TerminalDisplay::BRIGHT_RED << "Aucune IP entrée ou 'q' pressé. Arrêt." << TerminalDisplay::RESET << std::endl;
            cleanupGlobalCurl();
            return 0; // Quitter proprement
        }
        GeoLocationData result = locator.locate(inputIp);
        result.display();
        history.addEntry(result); // Ajoute à l'historique si succès
    } else {
        std::string arg1 = argv[1];
        std::transform(arg1.begin(), arg1.end(), arg1.begin(), ::tolower);

        if (arg1 == "--help" || arg1 == "-h") {
            displayHelp();
        } else if (arg1 == "--self" || arg1 == "-s") {
            std::cout << TerminalDisplay::YELLOW << "Tentative de géolocalisation de votre IP publique..." << TerminalDisplay::RESET << std::endl;
            std::string publicIp = locator.getPublicIp();
            if (!publicIp.empty()) {
                GeoLocationData result = locator.locate(publicIp);
                result.display();
                history.addEntry(result);
            } else {
                std::cerr << TerminalDisplay::BRIGHT_RED << "Impossible de récupérer votre IP publique. Veuillez vérifier votre connexion." << TerminalDisplay::RESET << std::endl;
            }
        } else if (arg1 == "--history" || arg1 == "-l") {
            history.displayHistory();
        } else if (arg1 == "--clear-history" || arg1 == "-c") {
            history.clearHistory();
        } else if (arg1 == "--config" || arg1 == "-C") {
            config.displayConfig();
            if (argc > 2) {
                std::string arg2 = argv[2];
                std::transform(arg2.begin(), arg2.end(), arg2.begin(), ::tolower);
                if (arg2 == "reset") {
                    config.resetToDefaults();
                    config.saveConfig();
                } else if (arg2 == "save") {
                    config.saveConfig();
                } else {
                    std::cerr << TerminalDisplay::BRIGHT_RED << "Option '--config' invalide. Utilisez '--config reset' ou '--config save'." << TerminalDisplay::RESET << std::endl;
                }
            }
        } else if (arg1 == "--credits" || arg1 == "-r") {
            displayCredits();
        }
        else if (Utils::isValidIP(arg1)) {
            std::cout << TerminalDisplay::CYAN << "Géolocalisation de l'IP : " << arg1 << TerminalDisplay::RESET << std::endl;
            GeoLocationData result = locator.locate(arg1);
            result.display();
            history.addEntry(result);
        } else {
            std::cerr << TerminalDisplay::BRIGHT_RED << "Argument invalide ou IP non reconnue : " << argv[1] << TerminalDisplay::RESET << std::endl;
            displayHelp();
            cleanupGlobalCurl();
            return 1;
        }
    }

    cleanupGlobalCurl();
    return 0;
}

// Fonction d'aide pour afficher les options (MISE À JOUR AVEC COULEURS)
void displayHelp() {
    using namespace TerminalDisplay;

    std::cout << BOLD << BRIGHT_GREEN << "\n--- ip-nose : Localisateur d'IP (Matrix Edition) ---" << RESET << std::endl;
    std::cout << BOLD << YELLOW << "Utilisation :" << RESET << std::endl;
    std::cout << "  " << GREEN << "ip-nose" << RESET << " [OPTIONS] " << BRIGHT_CYAN << "[ADRESSE_IP]" << RESET << std::endl;
    std::cout << BOLD << YELLOW << "\nOptions :" << RESET << std::endl;
    std::cout << "  " << BRIGHT_CYAN << "<ADRESSE_IP>" << RESET << "     Géolocalise l'adresse IP spécifiée." << std::endl;
    std::cout << "                   Ex: " << BRIGHT_YELLOW << "ip-nose 8.8.8.8" << RESET << std::endl;
    std::cout << "  " << BRIGHT_YELLOW << "--self, -s" << RESET << "       Géolocalise votre adresse IP publique." << std::endl;
    std::cout << "  " << BRIGHT_YELLOW << "--history, -l" << RESET << "    Affiche l'historique des recherches." << std::endl;
    std::cout << "  " << BRIGHT_YELLOW << "--clear-history, -c" << RESET << "  Efface tout l'historique des recherches." << std::endl;
    std::cout << "  " << BRIGHT_YELLOW << "--config, -C" << RESET << "     Affiche la configuration actuelle." << std::endl;
    std::cout << "                   Ajouter 'reset' pour réinitialiser la config par défaut." << std::endl;
    std::cout << "                   Ajouter 'save' pour sauvegarder la config actuelle." << std::endl;
    std::cout << "                   Ex: " << BRIGHT_YELLOW << "ip-nose --config reset" << RESET << std::endl;
    std::cout << "  " << BRIGHT_YELLOW << "--credits, -r" << RESET << "    Affiche les crédits et le dépôt GitHub." << std::endl;
    std::cout << "  " << BRIGHT_YELLOW << "--help, -h" << RESET << "       Affiche cette aide." << std::endl;
    std::cout << FAINT << BRIGHT_BLACK << "\nSi aucune IP n'est fournie, le programme vous invitera à en entrer une." << RESET << std::endl;
    std::cout << BOLD << BRIGHT_GREEN << "-----------------------------------" << RESET << std::endl;
}

// Initialisation globale de Curl
void initializeGlobalCurl() {
    CURLcode res = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (res != CURLE_OK) {
        std::cerr << TerminalDisplay::BRIGHT_RED << "Erreur critique: Impossible d'initialiser CURL globalement : " << curl_easy_strerror(res) << TerminalDisplay::RESET << std::endl;
        exit(1);
    }
}

// Nettoyage global de Curl
void cleanupGlobalCurl() {
    curl_global_cleanup();
}

// NOUVELLE FONCTION : Affiche la bannière de bienvenue à partir d'un fichier
void displayWelcomeBanner() {
    using namespace TerminalDisplay;
    TerminalDisplay::clearScreen(); // Efface l'écran avant la bannière

    std::ifstream bannerFile("banner.txt"); // Tente d'ouvrir le fichier banner.txt
    if (bannerFile.is_open()) {
        std::string line;
        while (std::getline(bannerFile, line)) {
            std::cout << BRIGHT_GREEN << BOLD << line << RESET << std::endl; // Affiche chaque ligne colorée
        }
        bannerFile.close();
    } else {
        // Si le fichier n'est pas trouvé, affiche un message d'avertissement
        std::cerr << BRIGHT_RED << "Erreur: Le fichier 'banner.txt' est introuvable. Veuillez le créer à la racine du projet." << RESET << std::endl;
    }

    std::cout << BRIGHT_YELLOW << BOLD << "        -=[ IP-NOSE - Matrix Edition ]=-" << RESET << std::endl;
    std::cout << BRIGHT_CYAN << "           Déchiffrez le monde des IPs" << RESET << std::endl;
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Pause de 1 seconde
}

// NOUVELLE FONCTION : Animation d'introduction style Matrix
void displayMatrixIntro() {
    using namespace TerminalDisplay;
    TerminalDisplay::hideCursor(); // Cacher le curseur pour une meilleure animation

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(0, 99); // 0-99 pour caractères variés

    // Définir la taille de l'écran pour l'animation (peut être ajusté)
    int screen_width = 80; // Largeur typique du terminal
    int screen_height = 24; // Hauteur typique du terminal

    for (int frame = 0; frame < 50; ++frame) { // 50 frames d'animation
        TerminalDisplay::clearScreen();

        for (int y = 0; y < screen_height; ++y) {
            for (int x = 0; x < screen_width; ++x) {
                int r = distribution(generator);
                if (r < 70) { // 70% de chances d'avoir un caractère vert
                    std::cout << BRIGHT_GREEN << (char)('0' + (r % 10)) << RESET; // Chiffres
                } else if (r < 85) { // 15% de chances d'avoir un caractère blanc
                    std::cout << BRIGHT_WHITE << (char)('A' + (r % 26)) << RESET; // Lettres majuscules
                } else if (r < 95) { // 10% de chances d'avoir un caractère vert foncé (moins intense)
                    std::cout << GREEN << (char)('a' + (r % 26)) << RESET; // Lettres minuscules
                } else { // 5% de chances d'avoir un espace ou un symbole (pour un effet plus "aéré")
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(80)); // Délai entre les frames
    }

    TerminalDisplay::clearScreen(); // Nettoyer l'écran après l'animation
    TerminalDisplay::showCursor(); // Afficher le curseur
}

// NOUVELLE FONCTION : Affichage des crédits avec appel à l'action GitHub
void displayCredits() {
    using namespace TerminalDisplay;
    TerminalDisplay::clearScreen();

    std::cout << BOLD << BRIGHT_GREEN << "\n--- Crédits ip-nose ---" << RESET << std::endl;
    std::cout << YELLOW << "Développé avec passion pour la communauté C++." << RESET << std::endl;
    std::cout << std::endl;
    std::cout << BOLD << WHITE << "Projet : " << GREEN << "ip-nose" << RESET << std::endl;
    std::cout << BOLD << WHITE << "Auteur : " << GREEN << "Karim93160" << RESET << std::endl;
    std::cout << std::endl;
    std::cout << BOLD << CYAN << "Si cet outil vous a été utile et que vous appréciez le travail :" << RESET << std::endl;
    std::cout << BOLD << MAGENTA << "Veuillez envisager de laisser une " << YELLOW << "*" << MAGENTA << " (étoile) sur le dépôt GitHub !" << RESET << std::endl;
    std::cout << BOLD << BRIGHT_BLUE << "Accéder au dépôt : " << UNDERLINE << "https://github.com/karim93160/ip-nose" << RESET << std::endl; // Lien direct
    std::cout << std::endl;
    std::cout << BRIGHT_GREEN << "Merci pour votre soutien !" << RESET << std::endl;
    std::cout << BOLD << BRIGHT_GREEN << "-----------------------" << RESET << std::endl;
    std::cout << std::endl;
    std::cout << BRIGHT_BLACK << "Copyright (c) 2024 Karim93160. Tous droits réservés." << RESET << std::endl;
}

