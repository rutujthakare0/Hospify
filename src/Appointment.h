#pragma once
#include <string>
#include "Person.h"
#include "json.hpp"
using namespace std;
using json=nlohmann::json;
#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
using namespace std;

class Appointment{
public:
    static string getCurrentTime();
};

#endif
