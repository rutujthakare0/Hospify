#pragma once
#include <string>

using namespace std;

class Person{
    protected:
    string name;
    int age;
    string contact;
    string gender;
    int id;

    public:
    Person(){}
    Person(string name,int age,string contact,string gender,int id):name(name),age(age),contact(contact),gender(gender),id(id){}

    virtual void displayDetails()const=0;

    void setName(string name){
        this->name=name;
    }
    void setAge(int age){
        this->age=age;
    }
    void setContact(string contact){
        this->contact=contact;
    }
    void setGender(string gender){
        this->gender=gender;
    }

    string getName(){
        return name;
    }
    int getAge(){
        return age;
    }
    string getContact(){
        return contact;
    }
    string getGender(){
        return gender;
    }
    int getId(){
        return id;
    }
    
    virtual ~Person()=default;
};



