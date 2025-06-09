// src/GeoLocationData.h
#ifndef GEO_LOCATION_DATA_H
#define GEO_LOCATION_DATA_H

#include <string>
#include <iostream> // Pour std::ostream et std::cout
#include "nlohmann/json.hpp" // AJOUTER CETTE LIGNE ICI AUSSI POUR LA SERIALISATION

using json = nlohmann::json; // AJOUTER CETTE LIGNE ICI AUSSI

class GeoLocationData {
public:
    GeoLocationData();

    // Setters (inchangés)
    void setIpAddress(const std::string& ip);
    void setStatus(const std::string& s);
    void setMessage(const std::string& m);
    void setCountry(const std::string& c);
    void setCountryCode(const std::string& cc);
    void setRegion(const std::string& r);
    void setRegionName(const std::string& rn);
    void setCity(const std::string& c);
    void setZip(const std::string& z);
    void setLat(double l);
    void setLon(double l);
    void setTimezone(const std::string& tz);
    void setIsp(const std::string& i);
    void setOrg(const std::string& o);
    void setAs(const std::string& a);
    void setReverse(const std::string& r);
    void setMobile(bool m);
    void setProxy(bool p);
    void setHosting(bool h);

    // Getters (inchangés, implémentation inline)
    std::string getIpAddress() const { return ipAddress; }
    std::string getStatus() const { return status; }
    std::string getMessage() const { return message; }
    std::string getCountry() const { return country; }
    std::string getCountryCode() const { return countryCode; }
    std::string getRegion() const { return region; }
    std::string getRegionName() const { return regionName; }
    std::string getCity() const { return city; }
    std::string getZip() const { return zip; }
    double getLat() const { return lat; }
    double getLon() const { return lon; }
    std::string getTimezone() const { return timezone; }
    std::string getIsp() const { return isp; }
    std::string getOrg() const { return org; }
    std::string getAs() const { return as; }
    std::string getReverse() const { return reverse; }
    bool getMobile() const { return mobile; }
    bool getProxy() const { return proxy; }
    bool getHosting() const { return hosting; }


    void display(std::ostream& os = std::cout) const;
    bool isSuccess() const;

private:
    std::string ipAddress;
    std::string status;
    std::string message;
    std::string country;
    std::string countryCode;
    std::string region;
    std::string regionName;
    std::string city;
    std::string zip;
    double lat;
    double lon;
    std::string timezone;
    std::string isp;
    std::string org;
    std::string as;
    std::string reverse;
    bool mobile;
    bool proxy;
    bool hosting;
};

// Fonctions de sérialisation/désérialisation pour nlohmann/json
// DOIVENT ÊTRE DANS LE MÊME FICHIER D'EN-TÊTE QUE LA CLASSE POUR L'ADL
inline void to_json(json& j, const GeoLocationData& d) {
    j = json::object();
    j["ipAddress"] = d.getIpAddress();
    j["status"] = d.getStatus();
    j["message"] = d.getMessage();
    j["country"] = d.getCountry();
    j["countryCode"] = d.getCountryCode();
    j["region"] = d.getRegion();
    j["regionName"] = d.getRegionName();
    j["city"] = d.getCity();
    j["zip"] = d.getZip();
    j["lat"] = d.getLat();
    j["lon"] = d.getLon();
    j["timezone"] = d.getTimezone();
    j["isp"] = d.getIsp();
    j["org"] = d.getOrg();
    j["as"] = d.getAs();
    j["reverse"] = d.getReverse();
    j["mobile"] = d.getMobile();
    j["proxy"] = d.getProxy();
    j["hosting"] = d.getHosting();
}

inline void from_json(const json& j, GeoLocationData& d) {
    d.setIpAddress(j.value("ipAddress", ""));
    d.setStatus(j.value("status", ""));
    d.setMessage(j.value("message", ""));
    d.setCountry(j.value("country", ""));
    d.setCountryCode(j.value("countryCode", ""));
    d.setRegion(j.value("region", ""));
    d.setRegionName(j.value("regionName", ""));
    d.setCity(j.value("city", ""));
    d.setZip(j.value("zip", ""));
    d.setLat(j.value("lat", 0.0));
    d.setLon(j.value("lon", 0.0));
    d.setTimezone(j.value("timezone", ""));
    d.setIsp(j.value("isp", ""));
    d.setOrg(j.value("org", ""));
    d.setAs(j.value("as", ""));
    d.setReverse(j.value("reverse", ""));
    d.setMobile(j.value("mobile", false));
    d.setProxy(j.value("proxy", false));
    d.setHosting(j.value("hosting", false));
}

#endif // GEO_LOCATION_DATA_H

