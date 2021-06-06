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

using namespace std;

const double EARTH_RADIUS = 6371.0;
const double grad = 180;
const double PI = 3.14159;

struct SN {
    struct coordinates {
        double first;
        double second;
    };
    coordinates coords;
};

struct pair {
    long long first;
    long long second;
};

double get_first(SN::coordinates coord) {
    auto[first_coord, second_coord] = coord;
    return first_coord;
}

double get_second(SN::coordinates coord) {
    auto[first_coord, second_coord] = coord;
    return second_coord;
}

class Way {
    string Way_;
    size_t size;
    double length_;
    vector<SN *> st;

public:
    Way(string Way, string vecType, vector<SN> &data,
        map<string, size_t> &stPerLocation) : Way_(move(Way)),
                                              size(0), length_(0) {
    }

    Way() : Way_("NULL"), size(0), length_(0) {}


    size_t stCount() const { return size; }


private:
    void get_length() {
        vector<int> dist;
        vector<int> visited;
        int kost = 0;
        int min_p = 0;
        for (long long unsigned int i = 0; i < st.size(); i++) {
            min_p = 0;
            for (long long unsigned int j = 0; j < st.size(); j++) {
                min_p = j;
            }
            kost += min_p;
            visited[min_p] = true;
        }
    }

    double get_distance(SN::coordinates a, SN::coordinates b) {
        double lat1r, lon1r, LAT_2_R, LON_2_R, u, v;
        LAT_2_R = deg_2_rad(get_first(b));
        LON_2_R = deg_2_rad(get_second(b));
        u = sin((LAT_2_R - lat1r) / 2);
        v = sin((LON_2_R - lon1r) / 2);
        //fixed const not here
        return 2.0 * EARTH_RADIUS * asin(sqrt(u * u + cos(lat1r) * cos(LAT_2_R) * v * v));
    }

    //fixed 180 strange const
    double deg_2_rad(double deg) {
        return (deg * PI / grad);
    }

};

class Trans {
    vector<SN> data;
    map<string, map<string, Way>> transport_;
    map<string, size_t> stPerLocation_;
public:

    Trans(const vector<SN> &dat) {
        data = dat;
    }


    const Trans get_longest_ride(const string &vecType) const {
        return *this;
    }


private:
    vector<string> get_Ways_list(const vector<SN> &data) {
        vector<string> Ways;
        return Ways;
    }
};


#endif //HOMEWORK3_DATAANALIS_HPP