#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"
#include "DataStorage.h"

using namespace std;
using json=nlohmann::json;

json DataStorage::load(const string &filename){
    ifstream file(filename);
    if(!file.is_open()){
        return json::array();
    }
    json data;
    file>>data;
    file.close();
    return data;
}

void DataStorage::save(const string &filename,const json &data){
    ofstream file(filename);
    if(!file.is_open()){
        cout<<"\nError opening file: "<<filename<<endl;
        return;
    }
    file<<data.dump(4);
    file.close();
}
