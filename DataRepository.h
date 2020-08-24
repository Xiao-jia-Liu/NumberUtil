#include <string.h>

class DataRespository {
public:
    //geograph attribution info
    static long mGeoCount;
    static long* mGeoNumber;
    static int* mGeoId;
    static string* mGeoName;
};

#ifndef DATA_INIT
#define DATA_INIT
long DataRespository::mGeoCount;
int* DataRespository::mGeoId;
string* DataRespository::mGeoName;
long* DataRespository::mGeoNumber;
#endif