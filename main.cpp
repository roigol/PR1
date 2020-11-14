#include <iostream>
#include "./headers/Session.h"
#include <fstream>
#include "./headers/json.hpp"
#include <boost/algorithm/string.hpp> // check if it possible
using json = nlohmann::json;
using namespace std;


int main(int argc, char** argv){
    if(argc != 2){
        cout << "usage cTrace <config_path>" << endl;
        return 0;
    }

    Session sess(argv[1]);
    sess.simulate();


    return 0;
}
