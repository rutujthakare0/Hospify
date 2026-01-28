#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>
#include "Doctor.h"

using namespace std;
using json=nlohmann::json;

extern string currentUserRole;

Doctor::Doctor(string name,int age,string contact,string gender,int id,int roomNo,string specialisation,bool availability,int salary,string joining_date,string regnNo):Person(name,age,contact,gender,id){
    this->specialisation=specialisation;
    this->roomNo=roomNo;
    this->availability=availability;
    this->salary=salary;
    this->joining_date=joining_date;
    this->regnNo=regnNo;
}

void Doctor::updateSalary(int newSalary){
    if(currentUserRole=="Admin"){
        this->salary=newSalary;
    }
    else
    cout<<"\nAccess Denied!"<<endl;
}
void Doctor::setRoomNo(int roomNo){
    if(currentUserRole=="Admin"){
        this->roomNo=roomNo;
    }
    else
    cout<<"\nAccess Denied!"<<endl;
}
void Doctor::setSpecialisation(string s){
    if(currentUserRole=="Admin"){
        this->specialisation=s;
    }
    else
    cout<<"\nAccess Denied!"<<endl;
}
void Doctor::setAvailability(bool a){
    if(currentUserRole=="Admin"||currentUserRole=="Doctor"){
        this->availability=a;
    }
    else
    cout<<"\nAccess Denied!"<<endl;
}

int Doctor::getRoomNo(){
    return this->roomNo;
}
string Doctor::getSpecialisation(){
    return this->specialisation;
}
bool Doctor::getAvailability(){
    return this->availability;
}
void Doctor::displayDetails() const{
    cout<<"------ Doctor Details ------"<<endl;

    cout<<"Name: "<<name<<endl;
    cout<<"Age: "<<age<<endl;    
    cout<<"Contact: "<<contact<<endl;
    cout<<"Gender: "<<gender<<endl;
    cout<<"ID: "<<id<<endl;

    cout<<"Room Number: "<<roomNo<<endl;
    cout<<"Specialisation: "<<specialisation<<endl;
    cout<<"Availability: "<<availability<<endl;

    cout<<"-----------------------------"<<endl;
}

json Doctor::toJson(){
    json j;
    j["name"]=name;
    j["age"]=age;    
    j["contact"]=contact;
    j["gender"]=gender;
    j["id"]=id;
    j["roomNo"]=roomNo;
    j["specialisation"]=specialisation;
    j["availability"]=availability;
    j["salary"]=salary;
    j["joining_date"]=joining_date;
    j["regnNo"]=regnNo;
    return j;
}

Doctor Doctor::fromJson(const json &j){
    return Doctor(
        j["name"].get<string>(),
        j["age"].get<int>(),       
        j["contact"].get<string>(), 
        j["gender"].get<string>(),
        j["id"].get<int>(),
        j["roomNo"].get<int>(),
        j["specialisation"].get<string>(),
        j["availability"].get<bool>(),
        j["salary"].get<int>(),
        j["joining_date"].get<string>(),
        j["regnNo"].get<string>()
    );
}