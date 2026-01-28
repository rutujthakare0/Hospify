#include <string>
#include "json.hpp"
#include "Person.h"
#include "Patient.h"

using namespace std;
using json=nlohmann::json;

class Doctor:public Person{
    private:
    int salary;
    string joining_date;
    string regnNo;

    public:
    int roomNo;
    string specialisation;
    bool availability;

    Doctor(){}
    Doctor(string name,int age,string contact,string gender,int id,int roomNo,string specialisation,bool availability,int salary,string joining_date,string regnNo);

    void updateSalary(int newSalary);
    void setRoomNo(int roomNo);
    void setAvailability(bool a);
    void setSpecialisation(string s);

    int getRoomNo();
    string getSpecialisation();
    bool getAvailability();
    void displayDetails() const override;

    json toJson();
    static Doctor fromJson(const json &j);

};
