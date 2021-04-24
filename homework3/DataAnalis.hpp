#ifndef HOMEWORK3_DATAANALIS_HPP
#define HOMEWORK3_DATAANALIS_HPP

#include <cstdio>
#include <string>
#include <vector>
#include "pugixml/pugixml.hpp"
#include <cstring>
#include <map>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cmath>
#include <windows.h>


const double EARTH_RADIUS = 6371.0;

struct Station {
    struct coordinates {
        double first;
        double second;
    };
    std::string type_of_vehicle;
    std::string object_type;
    std::string name_stopping;
    std::string the_official_name;
    std::string location;
    std::vector<std::string> routes;
    coordinates coords;
};


class Route {
    std::string route_;
    std::string vecType_;
    size_t sz;
    double length_;
    std::vector<Station *> stops_;

public:
    Route(std::string vecType, std::string route,  std::vector<Station> &data,
          std::map<std::string, size_t> &stopsPerLocation);

    Route() : route_("NULL"),vecType_("NULL"),  sz(0), length_(0) {}

    double getLength() const { return length_; }

    size_t stopsCount() const { return sz; }

    const std::string *getRoute() const { return &route_; }

private:
    void get_length();

    static double get_distance(Station::coordinates a, Station::coordinates b);

    static double deg2rad(double deg);

};

class CityTransport {
    std::vector<Station> data;
    std::map<std::string, std::map<std::string, Route>> transport_;
    std::map<std::string, size_t> stopsPerLocation_;
public:
    explicit CityTransport(const std::vector<Station> &data);

    CityTransport(const CityTransport &obj) = delete;

    CityTransport operator=(const CityTransport &obj) = delete;

    const Route *get_longest_ride(const std::string &vecType) const;

    const Route *get_max_stations_count(const std::string &vecType) const;

    std::pair<std::string, size_t> get_max_stations_street() const;

private:
    static std::vector<std::string> get_routes_list(const std::vector<Station> &data);

    static std::vector<std::string> get_locations(const std::vector<Station> &data);
};

class XmlReader {
    std::vector<Station> stations;
    pugi::xml_document doc;
public:
    explicit XmlReader(const std::string &file_name);

    void read();

    std::vector<Station> get_vector_Stations() const;
};

#endif //HOMEWORK3_DATAANALIS_HPP
