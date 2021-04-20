#include <iostream>
#include "DataAnalis.hpp"
#include "pugixml/pugixml.hpp"
#include <windows.h>
#include <cmath>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::string path;
    path = "data.xml";
    XmlReader reader(path);
    reader.read();
    std::vector<Station> data = reader.get_vector_Stations();
    CityTransport tr(data);
    const Route *LongestBus = tr.get_longest_ride("Автобус");
    const Route *LongestTram = tr.get_longest_ride("Трамвай");
    const Route *LongestTroll = tr.get_longest_ride("Троллейбус");
    const Route *maxStopsCountBus = tr.get_max_stations_count("Автобус");
    const Route *maxStopsCountTram = tr.get_max_stations_count("Трамвай");
    const Route *maxStopsCountTroll = tr.get_max_stations_count("Троллейбус");
    auto maxStopsPerStreet = tr.get_max_stations_street();
    std::cout << "Longest rides:" << std::endl;
    std::cout << "    Автобуc: №" << *(LongestBus->getRoute()) << " length: " << LongestBus->getLength() << std::endl;
    std::cout << "    Трамвай: №" << *(LongestTram->getRoute()) << " length: " << LongestTram->getLength() << std::endl;
    std::cout << "    Троллейбус: №" << *(LongestTroll->getRoute()) << " length: " << LongestTroll->getLength()
              << std::endl;
    std::cout << "Rides with max stops count" << std::endl;
    std::cout << "    Автобуc: №" << *(maxStopsCountBus->getRoute()) << " stops count: "
              << maxStopsCountBus->stopsCount() << std::endl;
    std::cout << "    Трамвай: №" << *(maxStopsCountTram->getRoute()) << " stops count: "
              << maxStopsCountTram->stopsCount() << std::endl;
    std::cout << "    Троллейбус: №" << *(maxStopsCountTroll->getRoute()) << " stops count: "
              << maxStopsCountTroll->stopsCount() << std::endl;
    std::cout << "Street with max stops count:" << std::endl;
    std::cout << "    " << maxStopsPerStreet.first << " stops count: " << maxStopsPerStreet.second << std::endl;

    return 0;
}
