#include <fstream>
#include <string.h>
#include <algorithm>
#include "FileName.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

#ifndef DATA_REPOSITORY
#define DATA_REPOSITORY
#include "DataRepository.h"
#endif

#ifndef INCLUDE_CONST_STRING
#define INCLUDE_CONST_STRING
#include "ConstString.h"
#endif

using namespace std;
class FileHandler {
private:
    static bool cmp(string x,string y) {
        string sx = x.substr(0,x.find(SPLIT_SYMBOL));
        string sy = y.substr(0,y.find(SPLIT_SYMBOL));
        //cout << "sort " << sx << " " << sy << " number : " << atol(sx.c_str()) << "  " << atol(sy.c_str()) << endl;
        return atol(sx.c_str()) < atol(sy.c_str());
    }
public:
    static void loadGeoFile() {
        ifstream file(GEO_FILE_NAME);

        if (!file) {
            cout<< "geo file not exist" << endl;
            return;
        }

        vector<string> tem;
        string line;
        
        while (getline(file,line)) {
            tem.push_back(line);
        }
        
        sort(tem.begin(),tem.end(),cmp);

        long count = tem.size();
        DataRespository::mGeoCount = count;
        DataRespository::mGeoId = new int[count];
        DataRespository::mGeoName = new string[count];
        DataRespository::mGeoNumber = new long[count];

        for (int i = 0; i < count; i++) 
        {
            string str = tem[i];
            int pos = str.find(SPLIT_SYMBOL);
            DataRespository::mGeoNumber[i] = atol(str.substr(0,pos).c_str());
            DataRespository::mGeoName[i] = str.substr(pos + 1);
        }

        cout << "has read " << count << "s number " << DataRespository::mGeoNumber[0] << DataRespository::mGeoName[0] << endl;
        file.close();
    }
};