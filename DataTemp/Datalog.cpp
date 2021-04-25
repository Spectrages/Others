#include <DataStruct.h>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

ostream& operator<<(ostream& os, const Coord& c)
{
    return os << c.deg << '*' << c.min << "\'" << c.sec << '"';
}

string Coord::toString() const
{
    ostringstream os;
    os << *this;
    return os.str();
}

ostream& operator<<(ostream& os, const DataPoint& d)
{
    os.setf(ios::fixed, ios::floatfield);
    char fillc = os.fill('0');
    tm* tdata = localtime(&d.timestamp);
    os << setw(2) << tdata->tm_mon + 1 << "\\"
       << setw(2) << tdata->tm_mday << "\\"
       << setw(2) << tdata->tm_year + 1900 << "  "
       << setw(2) << tdata->tm_hour << ':'
       << setw(2) << tdata->tm_min << ':'
       << setw(2) << tdata->tm_sec;
    os.fill(' ');
    streamsize prec = os.precision(4);
    os << " Lat:" << setw(9) << d.latitude.toString() <<
          ". Long:" << setw(9) << d.longitude.toString() <<
          ". Depth:" << setw(9) << d.depth <<
          ". Temperature:" << setw(9) << d.temperature;
    os.fill(fillc);
    os.precision(prec);
    return os;
}
