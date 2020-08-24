#include <iostream>
#include "Match.cpp"
#include "FileName.h"
#include "ConstString.h"

#include <unistd.h>

#ifndef DATA_REPOSITORY
#define DATA_REPOSITORY
#include "DataRepository.h"
#endif

using namespace std;

class Handler {
public:
    static void* handle(void* arg) 
    {
        Uri uri = *((Uri*)arg);
        int match = Match::match(uri);
        
        cout<<"match: " << match << endl;

        switch(match) {
            case NUMBER_GEO_ATTRIBUTION: {
                long number = atol(uri.getParameter(NUMBER).c_str());
                long* data = DataRespository::mGeoNumber;
                long count = DataRespository::mGeoCount;
                string* name = DataRespository::mGeoName;

                long left = 0;
                long right = count - 1;

                cout << "start search " << number << endl;
                while (left <= right) {
                    long mid = (left + right) / 2;
                    long tem = data[mid];

                    if (tem < number) {
                        left = mid + 1;
                    } else if (tem == number) {
                        cout << "number : " << number << " area : " << name[mid] << endl;
                        return (void*)&name[mid];
                    } else {
                        right = mid - 1;
                    }
                }

                cout << "unknown number area" << endl;
                return NULL;

            }

            default: {
                cout<< "unknown uri" << endl;
            }
        }



        cout<<uri.getParameter("number")<<endl;

        return (void*)arg;
    }
};