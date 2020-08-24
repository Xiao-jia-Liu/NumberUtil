#include "Uri.cpp"


#define NUMBER_GEO_ATTRIBUTION 0
#define UNKNOWN -1

#ifndef CONST_STRING
#define CONST_STRING
#include "ConstString.h"
#endif



class Match {


public:
    static int match(Uri uri)
    {
        if (uri.mUri.find(PARAMETER_START_SYMBOL) == string(NUMBER_GEO_ATTRIBUTION_HEAD).length())
        {
            return NUMBER_GEO_ATTRIBUTION;
        } else {
            return UNKNOWN;
        }
    }
};