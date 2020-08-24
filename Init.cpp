#include "FileHandler.cpp"

class Init {
public:
    static void init() {
        FileHandler::loadGeoFile();
    }
};