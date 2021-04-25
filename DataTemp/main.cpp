#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include "requare.h"
#include "DataStruct.h"
using namespace std;

int main()
{
    time_t timer;
    srand(time(&timer));
    ofstream data("data.txt");
    assure(data, "data.txt");
    ofstream bdata("data.bin", ios::binary);
    assure(bdata, "data.bin");

    for(int i = 0; i < 100; timer += 55)
    {
        double newdepth = rand() % 200;
        double fraction = rand() % 100 + 1;
        newdepth += 1.0 / fraction;
        double newtemp = 150 + rand() % 200;
        const DataPoint d(timer, Coord(45, 20, 31), Coord(20, 34, 18), newdepth, newtemp);
        data << d << endl;
        bdata.write(reinterpret_cast<const char*>(&d), sizeof (d));
    }
    return 0;
}
