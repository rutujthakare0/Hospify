#pragma once
#include <string>
#include "Person.h"
#include "json.hpp"
using namespace std;
using json=nlohmann::json;

class Patient:public Person{
    protected:
    string disease="";
    bool admittedStatus=false;
    int roomNumber=0;
    string notes="";
    int doctorId=0;
    string dateOfAdmission="";
    string dateOfDischarge="";

    public:
    Patient(){}
    Patient(string name,int age,string contact,string gender,int id, string disease,bool admittedStatus, int roomNumber, string notes,int doctorId,string dateOfAdmission,string dateOfDischarge);
    Patient(string name,int age,string contact,string gender,int id, string disease);

    void setDisease(string disease);
    void setAdmittedStatus(bool admittedStatus);
    void setRoomNumber(int roomNumber);
    void updateNotes(string notes);
    void setDoctorId(int doctorId);
    void setDateOfAdmission(string date);
    void setDateOfDischarge(string date);

    string getDisease();
    bool getAdmittedStatus();
    int getRoomNumber();
    int getDoctorId();
    string getNotes();
    string getDateOfAdmission();
    string getDateOfDischarge();

    void discharge(string info);
    void displayDetails() const override;


    json toJson();
    static Patient fromJson(json &j);

};
