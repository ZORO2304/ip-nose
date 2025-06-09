// src/GeoLocationData.cpp
#include "GeoLocationData.h"
#include <iomanip> // Pour std::fixed et std::setprecision
#include "TerminalDisplay.h" // Pour les couleurs

// Constructeur par défaut
GeoLocationData::GeoLocationData() :
    ipAddress(""), status(""), message(""),
    country(""), countryCode(""), region(""), regionName(""),
    city(""), zip(""),
    lat(0.0), lon(0.0),
    timezone(""), isp(""), org(""), as(""), reverse(""),
    mobile(false), proxy(false), hosting(false)
{}

// Implémentation des Setters
void GeoLocationData::setIpAddress(const std::string& ip) { ipAddress = ip; }
void GeoLocationData::setStatus(const std::string& s) { status = s; }
void GeoLocationData::setMessage(const std::string& m) { message = m; }
void GeoLocationData::setCountry(const std::string& c) { country = c; }
void GeoLocationData::setCountryCode(const std::string& cc) { countryCode = cc; }
void GeoLocationData::setRegion(const std::string& r) { region = r; }
void GeoLocationData::setRegionName(const std::string& rn) { regionName = rn; }
void GeoLocationData::setCity(const std::string& c) { city = c; }
void GeoLocationData::setZip(const std::string& z) { zip = z; }
void GeoLocationData::setLat(double l) { lat = l; }
void GeoLocationData::setLon(double l) { lon = l; }
void GeoLocationData::setTimezone(const std::string& tz) { timezone = tz; }
void GeoLocationData::setIsp(const std::string& i) { isp = i; }
void GeoLocationData::setOrg(const std::string& o) { org = o; }
void GeoLocationData::setAs(const std::string& a) { as = a; }
void GeoLocationData::setReverse(const std::string& r) { reverse = r; }
void GeoLocationData::setMobile(bool m) { mobile = m; }
void GeoLocationData::setProxy(bool p) { proxy = p; }
void GeoLocationData::setHosting(bool h) { hosting = h; }


// Vérifie si la géolocalisation a réussi
bool GeoLocationData::isSuccess() const {
    return status == "success";
}

// Méthode pour afficher les données avec des couleurs "Matrix"
void GeoLocationData::display(std::ostream& os) const {
    using namespace TerminalDisplay; // Simplifier l'accès aux constantes de couleur

    os << BOLD << BRIGHT_GREEN << "\n--- Données IP pour " << ipAddress << " ---" << RESET << std::endl;
    os << BOLD << YELLOW << "Statut         : " << RESET;
    if (status == "success") {
        os << BRIGHT_GREEN << status << RESET << std::endl;
    } else {
        os << BRIGHT_RED << status << RESET << std::endl;
    }

    if (status == "fail") {
        os << RED << "Message d'erreur: " << message << RESET << std::endl;
    } else {
        os << BOLD << "Pays           : " << RESET << GREEN << country << RESET << " (" << countryCode << ")" << std::endl;
        os << BOLD << "Région         : " << RESET << BRIGHT_CYAN << regionName << RESET << " (" << region << ")" << std::endl;
        os << BOLD << "Ville          : " << RESET << BRIGHT_MAGENTA << city << RESET << std::endl;
        os << BOLD << "Code Postal    : " << RESET << WHITE << zip << RESET << std::endl;
        os << BOLD << "Fuseau Horaire : " << RESET << BRIGHT_BLACK << timezone << RESET << std::endl; // Gris
        os << BOLD << "ISP (Fournisseur) : " << RESET << BLUE << isp << RESET << std::endl;
        os << BOLD << "Organisation   : " << RESET << BLUE << org << RESET << std::endl;
        os << BOLD << "AS (Système Autonome) : " << RESET << BLUE << as << RESET << std::endl;

        os << std::fixed << std::setprecision(4);
        os << BOLD << "Latitude       : " << RESET << BRIGHT_YELLOW << lat << RESET << std::endl;
        os << BOLD << "Longitude      : " << RESET << BRIGHT_YELLOW << lon << RESET << std::endl;
        os << std::setprecision(6);

        os << BOLD << "DNS Inverse    : " << RESET << WHITE << reverse << RESET << std::endl;

        // Couleurs conditionnelles pour les drapeaux "risqués"
        // Correction : Utilisation de la concaténation de string pour éviter l'ambiguïté des opérateurs ternaires
        os << BOLD << "Mobile         : " << RESET << (mobile ? (BRIGHT_RED + "Oui") : (BRIGHT_GREEN + "Non")) << RESET << std::endl;
        os << BOLD << "Proxy/VPN      : " << RESET << (proxy ? (BRIGHT_RED + "Oui") : (BRIGHT_GREEN + "Non")) << RESET << std::endl;
        os << BOLD << "Hébergement    : " << RESET << (hosting ? (BRIGHT_RED + "Oui") : (BRIGHT_GREEN + "Non")) << RESET << std::endl;

        os << FAINT << BRIGHT_BLACK << "\nRemarque : L'adresse physique exacte n'est pas disponible via la géolocalisation d'IP." << RESET << std::endl;
    }
    os << BOLD << BRIGHT_GREEN << "------------------------------------------" << RESET << std::endl;
}

