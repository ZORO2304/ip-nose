// src/TerminalDisplay.h
#ifndef TERMINAL_DISPLAY_H
#define TERMINAL_DISPLAY_H

#include <string>
#include <iostream>
#include <cstdlib> // Pour system()

namespace TerminalDisplay {
    // Codes ANSI pour les couleurs et styles
    const std::string RESET = "\x1b[0m";
    const std::string BOLD = "\x1b[1m";
    const std::string FAINT = "\x1b[2m"; // Faible luminosité
    const std::string ITALIC = "\x1b[3m"; // Italique
    const std::string UNDERLINE = "\x1b[4m"; // Souligné

    // Couleurs du texte
    const std::string BLACK = "\x1b[30m";
    const std::string RED = "\x1b[31m";    // Pour les avertissements, échecs
    const std::string GREEN = "\x1b[32m";  // Pour les succès, données "sûres"
    const std::string YELLOW = "\x1b[33m"; // Pour les entêtes, informations importantes
    const std::string BLUE = "\x1b[34m";
    const std::string MAGENTA = "\x1b[35m";
    const std::string CYAN = "\x1b[36m";   // Pour les IPs, coordonnées
    const std::string WHITE = "\x1b[37m";
    const std::string BRIGHT_BLACK = "\x1b[90m"; // Gris clair
    const std::string BRIGHT_RED = "\x1b[91m";
    const std::string BRIGHT_GREEN = "\x1b[92m";
    const std::string BRIGHT_YELLOW = "\x1b[93m";
    const std::string BRIGHT_BLUE = "\x1b[94m";
    const std::string BRIGHT_MAGENTA = "\x1b[95m";
    const std::string BRIGHT_CYAN = "\x1b[96m";
    const std::string BRIGHT_WHITE = "\x1b[97m";

    // Couleurs de fond
    const std::string BG_BLACK = "\x1b[40m";
    const std::string BG_RED = "\x1b[41m";
    const std::string BG_GREEN = "\x1b[42m";
    const std::string BG_YELLOW = "\x1b[43m";
    const std::string BG_BLUE = "\x1b[44m";
    const std::string BG_MAGENTA = "\x1b[45m";
    const std::string BG_CYAN = "\x1b[46m";
    const std::string BG_WHITE = "\x1b[47m";

    // Fonction pour effacer l'écran du terminal
    inline void clearScreen() {
    #ifdef _WIN32
        system("cls"); // Pour Windows
    #else
        system("clear"); // Pour Linux/Termux/macOS
    #endif
    }

    // Fonction pour cacher le curseur (pour des animations plus propres)
    inline void hideCursor() {
        std::cout << "\x1b[?25l";
    }

    // Fonction pour montrer le curseur
    inline void showCursor() {
        std::cout << "\x1b[?25h";
    }

    // Tu peux ajouter d'autres fonctions utilitaires ici si tu le souhaites (ex: moveCursorTo, setWindowTitle, etc.)

} // namespace TerminalDisplay

#endif // TERMINAL_DISPLAY_H

