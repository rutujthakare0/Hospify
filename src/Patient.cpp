#include <iostream>
#include <string>
#include <ctime>
#include "Patient.h"
#include "Appointment.h"
#include "json.hpp"
#include "DataStorage.h"

using namespace std;
using json=nlohmann::json;

extern string currentUserRole;


Patient::Patient(string name,int age,string contact,string gender,int id, string disease,bool admittedStatus, int roomNumber, string notes,int doctorId,string dateOfAdmission,string dateOfDischarge):Person(name,age,contact,gender,id){
this->disease = disease;
this->admittedStatus = admittedStatus;
this->roomNumber = roomNumber;
this->notes = notes;
this->doctorId = doctorId;
this->dateOfAdmission = dateOfAdmission;
this->dateOfDischarge = dateOfDischarge;
}

Patient::Patient(string name,int age,string contact,string gender,int id, string disease):Person(name,age,contact,gender,id){
this->disease = disease;
}

void Patient::setDisease(string disease){
    this->disease=disease;    
}
void Patient::setAdmittedStatus(bool admittedStatus){
    this->admittedStatus=admittedStatus;
}
void Patient::setRoomNumber(int roomNumber){
    this->roomNumber=roomNumber;
}
void Patient::updateNotes(string notes){
    this->notes+=notes;    
}
void Patient::setDoctorId(int doctorId){
    this->doctorId=doctorId;
}
void Patient::setDateOfAdmission(string date){
    this->dateOfAdmission=date;
}
void Patient::setDateOfDischarge(string date){
    this->dateOfDischarge=date;
}

string Patient::getDisease(){
    return disease;
}
bool Patient::getAdmittedStatus(){
    return admittedStatus;
}
int Patient::getRoomNumber(){
    return roomNumber;
}
int Patient::getDoctorId(){
    return doctorId;
}
string Patient::getNotes(){
    return notes;
}
string Patient::getDateOfAdmission(){
    return dateOfAdmission;
}
string Patient::getDateOfDischarge(){
    return dateOfDischarge;
}

json Patient::toJson(){
    json j;
    j["name"]=name;
    j["age"]=age;
    j["contact"]=contact;
    j["gender"]=gender;
    j["id"]=id;
    j["disease"]=disease;
    j["admittedStatus"]=admittedStatus;
    j["roomNumber"]=roomNumber;
    j["notes"]=notes;
    j["doctorId"]=doctorId;
    j["dateOfAdmission"]=dateOfAdmission;
    j["dateOfDischarge"]=dateOfDischarge;
    return j;
}
Patient Patient::fromJson(json &j){
        return Patient(
        j["name"].get<string>(),
        j["age"].get<int>(),
        j["contact"].get<string>(),
        j["gender"].get<string>(),
        j["id"].get<int>(),
        j["disease"].get<string>(),
        j["admittedStatus"].get<bool>(),
        j["roomNumber"].get<int>(),
        j["notes"].get<string>(),
        j["doctorId"].get<int>(),
        j["dateOfAdmission"].get<string>(),
        j["dateOfDischarge"].get<string>()
    );
}

void Patient::discharge(string info){
    if(1){
    string addition;
    {
    dateOfDischarge = Appointment::getCurrentTime();

    }
    if(admittedStatus){
        addition= "\nAdmitted:"+ dateOfAdmission +"\nDischarge: " + dateOfDischarge + "\nDisease: "+disease+"\nRoom No.: " + to_string(roomNumber) + " Treated by: "+ to_string(doctorId)+"\nNotes: "+info+" ";
    }else{
        addition= "\nDate: "+ dateOfAdmission +"\nDisease: "+disease+"\nRoom No.: "+ to_string(roomNumber)+ " Treated by: "+to_string(doctorId)+"\nNotes: "+info+" ";
    }
    notes+=addition;
    roomNumber=0;
    admittedStatus=false;

    json data=DataStorage::load("data/patients.json");
    for(auto &p:data){
        if(p["id"]==id){
            p=toJson();
            DataStorage::save("data/patients.json",data);
            return;
        }
    }
    data.push_back(toJson());
    DataStorage::save("data/patients.json",data);
    }else{
        cout<<"Access Denied!";
    }
}
void Patient::displayDetails() const{
    cout<<"------ Patient Details ------"<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Age: "<<age<<endl;
    cout<<"Gender: "<<gender<<endl;
    cout<<"Contact: "<<contact<<endl;
    cout<<"ID: "<<id<<endl;

    cout<<"Disease: "<<disease<<endl;
    cout<<"Admitted: "<<(admittedStatus?"Yes":"No")<<endl;
    cout<<"Room Number: "<<roomNumber<<endl;
    cout<<"Doctor ID: "<<doctorId<<endl;

    cout<<"Notes: "<<notes<<endl;
    cout<<"Date of Admission: "<<dateOfAdmission<<endl;
    cout<<"Date of Discharge: "<<dateOfDischarge<<endl;

    cout<<"-----------------------------"<<endl;
}


