#pragma once
#include <string>
#include "json.hpp"

using namespace std;
using json=nlohmann::json;

class DataStorage{
    public:
    static json load(const string &filename);
    static void save(const string &filename, const json &data); 
};