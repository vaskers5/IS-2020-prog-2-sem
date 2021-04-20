#include "DataAnalis.hpp"
#include <iostream>

class StringSplit : public std::string {
    std::vector<std::string> fields;
public:
    explicit StringSplit(const std::string &s) : std::string(s) {};

    std::vector<std::string> &split(char delim, int rep = 0);
};

std::vector<std::string> &StringSplit::split(char delim, int rep) {
    if (!fields.empty()) fields.clear();
    std::string work = data();
    std::string buf;
    for (auto elem : work) {
        if (elem != delim)
            buf += elem;
        else if (rep == 1) {
            fields.push_back(buf);
            buf = "";
        } else if (buf.length() > 0) {
            fields.push_back(buf);
            buf = "";
        }
    }
    if (!buf.empty())
        fields.push_back(buf);
    return fields;
}

double get_first(Station::coordinates coord)  {
    auto [first_coord,second_coord] = coord;
    return first_coord;
}

double get_second(Station::coordinates coord) {
    auto [first_coord,second_coord] = coord;
    return second_coord;
}

XmlReader::XmlReader(const std::string &file_name) {
    pugi::xml_parse_result result = doc.load_file(file_name.c_str());
}

void XmlReader::read() {
    pugi::xml_node node = doc.child("dataset").child("transport_station");
    Station tmp;
    std::string routes;
    std::vector<std::string> coords;
    while (node) {
        tmp.type_of_vehicle = node.child("type_of_vehicle").first_child().value();
        tmp.object_type = node.child("object_type").first_child().value();
        tmp.name_stopping = node.child("name_stopping").first_child().value();
        tmp.the_official_name = node.child("the_official_name").first_child().value();
        tmp.location = node.child("location").first_child().value();
        routes = node.child("routes").first_child().value();

        StringSplit spl(routes);

        if (routes.end() != std::find(routes.begin(), routes.end(), ',')) {
            tmp.routes = spl.split(',');
        } else {
            tmp.routes = spl.split(' ');
        }

        spl = StringSplit(node.child("coordinates").first_child().value());

        coords = spl.split(',');

        tmp.coords.first = std::stof(coords.at(0));
        tmp.coords.second = std::stof(coords.at(1));

        stations.push_back(tmp);
        node = node.next_sibling();
    }
}

std::vector<Station> XmlReader::get_vector_Stations() const {
    return stations;
}

Route::Route(std::string route, std::string vecType, std::vector<Station> &data,
             std::map<std::string, size_t> &stopsPerLocation) : route_(std::move(route)), vecType_(std::move(vecType)),
                                                                sz(0), length_(0) {
    for (auto &elem : data) {
        if ((std::find(elem.routes.begin(), elem.routes.end(), route_) != elem.routes.end()) &&
            (elem.type_of_vehicle == vecType_)) {

            stops_.push_back(&elem);
            std::vector<std::string> location = StringSplit(elem.location).split(',');
            for (const auto &j : location) {
                stopsPerLocation.at(j)++;
            }
            sz++;
        }
    }
    if (sz != 0) {
        get_length();
    }
}
//fuxed 180 strange const
double Route::deg2rad(double deg) {
    return (deg * M_PI / grad);
}


double Route::get_distance(Station::coordinates a, Station::coordinates b) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(get_first(a));
    lon1r = deg2rad(get_second(a));
    lat2r = deg2rad(get_first(b));
    lon2r = deg2rad(get_second(b));
    u = sin((lat2r - lat1r) / 2);
    v = sin((lon2r - lon1r) / 2);
    //fixed const not here
    return 2.0 * EARTH_RADIUS * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

void Route::get_length() {
    std::vector<std::vector<double>> stops(stops_.size(), std::vector<double>(stops_.size()));
    for (int i = 0; i < stops_.size(); i++) {
        for (int j = 0; j < stops_.size(); j++) {
            stops.at(i).at(j) = get_distance(stops_.at(i)->coords, stops_.at(j)->coords);
        }
    }
    std::vector<double> dist(stops_.size(), std::numeric_limits<double>::max());
    std::vector<bool> visited(stops_.size(), false);

    double res = 0;

    dist.at(0) = 0;

    for (int i = 0; i < stops_.size(); i++) {
        double min = std::numeric_limits<double>::max();
        int minpos = 0;
        for (int j = 0; j < stops_.size(); j++) {
            if (!visited.at(j) && dist.at(j) < min) {
                min = dist.at(j);
                minpos = j;
            }
        }
        res += min;
        visited.at(minpos) = true;
        for (int j = 0; j < stops_.size(); j++) {
            dist.at(j) = std::min(dist.at(j), stops.at(minpos).at(j));
        }
        this->length_ = res;
    }
}

CityTransport::CityTransport(const std::vector<Station> &dat) {
    data = dat;
    std::vector<std::string> stops = get_routes_list(data);
    std::vector<std::string> locations = get_locations(data);
    for (const std::string &i : locations) {
        stopsPerLocation_.insert({i, 0});
    }
    std::map<std::string, Route> stopsListBus;
    std::map<std::string, Route> stopsListTram;
    std::map<std::string, Route> stopsListTroll;
    {
        for (const std::string &i : stops) {
            Route tmpBus(i, "Автобус", data, stopsPerLocation_);
            Route tmpTram(i, "Трамвай", data, stopsPerLocation_);
            Route tmpTroll(i, "Троллейбус", data, stopsPerLocation_);
            if (tmpBus.stopsCount() != 0)
                stopsListBus.insert({i, tmpBus});
            if (tmpTram.stopsCount() != 0)
                stopsListTram.insert({i, tmpTram});
            if (tmpTroll.stopsCount() != 0)
                stopsListTroll.insert({i, tmpTroll});
        }
        transport_.insert({"Автобус", stopsListBus});
        transport_.insert({"Трамвай", stopsListTram});
        transport_.insert({"Троллейбус", stopsListTroll});
    }
}

std::vector<std::string> CityTransport::get_routes_list(const std::vector<Station> &data) {
    std::vector<std::string> routes;
    for (const Station &i : data) {
        for (const std::string &j : i.routes) {
            routes.push_back(j);
        }
    }
    std::sort(routes.begin(), routes.end());
    std::vector<std::string>::iterator it;
    it = unique(routes.begin(), routes.end());
    routes.resize(distance(routes.begin(), it));
    return routes;
}

std::vector<std::string> CityTransport::get_locations(const std::vector<Station> &data) {
    std::vector<std::string> locations;
    for (const Station &i : data) {
        StringSplit spl(i.location);
        for (const std::string &j : spl.split(','))
            locations.push_back(j);
    }
    std::sort(locations.begin(), locations.end());
    std::vector<std::string>::iterator it;
    it = unique(locations.begin(), locations.end());
    locations.resize(distance(locations.begin(), it));
    return locations;
}

const Route *CityTransport::get_longest_ride(const std::string &vecType) const {
    auto x = std::max_element(transport_.at(vecType).begin(), transport_.at(vecType).end(),
                              [](const std::pair<std::string, Route> &p1, const std::pair<std::string, Route> &p2) {
                                  return p1.second.getLength() < p2.second.getLength();
                              });
    return &(x->second);
}

const Route *CityTransport::get_max_stations_count(const std::string &vecType) const {
    auto x = std::max_element(transport_.at(vecType).begin(), transport_.at(vecType).end(),
                              [](const std::pair<std::string, Route> &p1, const std::pair<std::string, Route> &p2) {
                                  return p1.second.stopsCount() < p2.second.stopsCount();
                              });
    return &(x->second);
}

std::pair<std::string, size_t> CityTransport::get_max_stations_street() const {
    auto x = std::max_element(stopsPerLocation_.begin(), stopsPerLocation_.end(),
                              [](const std::pair<std::string, size_t> &p1, const std::pair<std::string, size_t> &p2) {
                                  return p1.second < p2.second;
                              });
    return *x;
}