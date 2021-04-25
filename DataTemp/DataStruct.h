#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <iostream>
#include <iosfwd>
#include <string>
#include <ctime>
using std::ostream;

struct Coord
{
    int deg, min, sec;
    Coord(int d = 0,int  m = 0, int s = 0) : deg(d), min(m), sec(s) {}
    std::string toString() const;
};
ostream& operator<<(ostream&, const Coord&);

class DataPoint
{
    std::time_t timestamp;
    Coord latitude, longitude;
    double depth, temperature;
public:
    DataPoint(std::time_t ts, const Coord& lat, const Coord& lon, double dep, double temp):
        timestamp(ts), latitude(lat), longitude(lon), depth(dep), temperature(temp) {}
    DataPoint() : timestamp(0), depth(0), temperature(0) {}
    friend ostream& operator<<(ostream&, const DataPoint&);
};
#endif // DATASTRUCT_H
