#include <string.h>
#include <regex>
#include <iostream>
using namespace std;
class Uri {
public:
    string mUri;
    
    Uri(string uri) {
        mUri = uri;
    }

    string getParameter(string key) {
        string s1 = ".+\\?(";
        string s2 = ")=([^?]+).*";
        string s3 = s1 + key + s2;
        regex reg(s3,regex_constants::icase);
        smatch m;
        if (regex_match(mUri,m,reg)) 
        {
            return m[2];
        }
        return "";
    }

private:
    
};