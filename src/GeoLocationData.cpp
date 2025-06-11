#include "GeoLocationData.h"
#include <iomanip> // Pour std::fixed, std::setprecision

// Implémentation de la fonction display()
void GeoLocationData::display() const {
    using namespace TerminalDisplay;
    std::cout << BOLD << GREEN << "\n--- Détails de Géolocalisation ---" << RESET << std::endl;
    std::cout << CYAN << "  IP           : " << WHITE << ip << RESET << std::endl; // Utilise le membre ip
    std::cout << CYAN << "  Pays         : " << WHITE << country << " (" << countryCode << ")" << RESET << std::endl;
    std::cout << CYAN << "  Région       : " << WHITE << regionName << RESET << std::endl;
    std::cout << CYAN << "  Ville        : " << WHITE << city << RESET << std::endl;
    std::cout << CYAN << "  Code Postal  : " << WHITE << zip << RESET << std::endl;
    std::cout << CYAN << "  Lat/Lon      : " << WHITE << std::fixed << std::setprecision(6) << lat << ", " << std::fixed << std::setprecision(6) << lon << RESET << std::endl;
    std::cout << CYAN << "  Fuseau horaire : " << WHITE << timezone << RESET << std::endl;
    std::cout << CYAN << "  FAI          : " << WHITE << isp << RESET << std::endl;
    std::cout << CYAN << "  Organisation : " << WHITE << org << RESET << std::endl;
    std::cout << CYAN << "  AS           : " << WHITE << as << RESET << std::endl;
    // Si tu as d'autres membres comme message, mobile, proxy, hosting, etc.
    // std::cout << CYAN << "  Message      : " << WHITE << message << RESET << std::endl;
    // std::cout << CYAN << "  Mobile       : " << WHITE << (mobile ? "Oui" : "Non") << RESET << std::endl;
    // std::cout << CYAN << "  Proxy        : " << WHITE << (proxy ? "Oui" : "Non") << RESET << std::endl;
    // std::cout << CYAN << "  Hosting      : " << WHITE << (hosting ? "Oui" : "Non") << RESET << std::endl;

    std::cout << CYAN << "  Statut       : " << (status == "success" ? TerminalDisplay::BRIGHT_GREEN : TerminalDisplay::BRIGHT_RED) << status << RESET << std::endl;
    std::cout << BOLD << GREEN << "------------------------------------" << RESET << std::endl;
}

// Implémentation des fonctions to_json et from_json pour nlohmann/json
// Ces fonctions permettent de convertir GeoLocationData en JSON et vice-versa.
void to_json(nlohmann::json& j, const GeoLocationData& p) {
    j = nlohmann::json{
        {"ip", p.ip},
        {"country", p.country},
        {"countryCode", p.countryCode},
        {"regionName", p.regionName},
        {"city", p.city},
        {"zip", p.zip},
        {"lat", p.lat},
        {"lon", p.lon},
        {"timezone", p.timezone},
        {"isp", p.isp},
        {"org", p.org},
        {"as", p.as},
        {"status", p.status},
        {"message", p.message} // Inclure le message aussi
        // Si tu as d'autres membres (region, reverse, mobile, proxy, hosting), ajoute-les ici aussi
        // {"region", p.region},
        // {"reverse", p.reverse},
        // {"mobile", p.mobile},
        // {"proxy", p.proxy},
        // {"hosting", p.hosting}
    };
}

void from_json(const nlohmann::json& j, GeoLocationData& p) {
    // Utilise .get<>() pour une désérialisation plus robuste
    j.at("ip").get_to(p.ip);
    j.at("country").get_to(p.country);
    j.at("countryCode").get_to(p.countryCode);
    j.at("regionName").get_to(p.regionName);
    j.at("city").get_to(p.city);
    j.at("zip").get_to(p.zip);
    j.at("lat").get_to(p.lat);
    j.at("lon").get_to(p.lon);
    j.at("timezone").get_to(p.timezone);
    j.at("isp").get_to(p.isp);
    j.at("org").get_to(p.org);
    j.at("as").get_to(p.as);
    j.at("status").get_to(p.status);
    // Le champ "message" peut ne pas toujours être présent, gérons-le avec un find
    if (j.find("message") != j.end() && !j.at("message").is_null()) {
        j.at("message").get_to(p.message);
    } else {
        p.message = ""; // Ou N/A
    }

    // Si tu as d'autres membres (region, reverse, mobile, proxy, hosting), ajoute-les ici aussi
    // j.at("region").get_to(p.region);
    // if (j.find("reverse") != j.end() && !j.at("reverse").is_null()) { j.at("reverse").get_to(p.reverse); }
    // if (j.find("mobile") != j.end() && !j.at("mobile").is_null()) { p.mobile = j.at("mobile"); }
    // if (j.find("proxy") != j.end() && !j.at("proxy").is_null()) { p.proxy = j.at("proxy"); }
    // if (j.find("hosting") != j.end() && !j.at("hosting").is_null()) { p.hosting = j.at("hosting"); }
}
<<<<<<< HEAD


=======
>>>>>>> 9621915b40066bc9ccea2304e6fbdf84277aee47
