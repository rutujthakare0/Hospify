#include "Appointment.h"
#include <ctime>

string Appointment::getCurrentTime(){
    time_t now = time(0);
    return string(ctime(&now));
}
