#include <iostream>
#include <string>
#include <ctime>
#include "Patient.h"
#include "json.hpp"
#include "DataStorage.h"
#include "Appointment.h"

using namespace std;
using json=nlohmann::json;

extern string currentUserRole;
extern int pin;
extern int rec_pin;
extern int admin_pin;

class HospitalSystem{
public:
    void start(){
        int login;
        while(true){
            cin.clear();
            cout<<"=============================================\n";
            cout<<"   WELCOME TO XYZ MULTISPECIALITY HOSPITAL   \n";
            cout<<"=============================================\n\n";
            cout<<"Please select your login mode\n";
            cout<<"Patient Login                             - 1\n";
            cout<<"Staff Login                               - 2\n";
            cin>>login;
            switch(login){
                case 1:
                    patientLogin();
                    break;
                case 2:{
                    int trials=3;
                    while(trials--){
                        int code;
                        cout<<"========== Please enter Staff Code ==========\n";
                        if(trials==0)cout<<"            (Last trial!)            \n";
                        cin>>code;
                        if(code==pin){
                            int modeSelector;
                            cout<<"Please select your login mode\n";
                            cout<<"Admin Login                               - 1\n";
                            cout<<"Doctor Login                              - 2\n";
                            cout<<"Reception Login                           - 3\n";
                            cin>>modeSelector;
                            switch(modeSelector){
                                case 1: 
                                adminLogin(); 
                                break;
                                case 2: 
                                doctorLogin(); 
                                break;
                                case 3: 
                                receptionistLogin(); 
                                break;
                                default:return;
                            }
                            break;
                        }else{
                            cout<<"=============== INVALID CODE! ===============\n";
                        }
                    }
                    break;
                }
                default: cout<<"=============== INVALID VALUE ===============\n";
            }
        }
    }

void patientLogin(){
    currentUserRole="Patient";

    cout<<"----------- PATIENT LOGIN SELECTED -----------\n";
    cout<<"Please enter the following details:\n";

    string name,contact,gender,disease;
    int age,g;

    cin.ignore();
    cout<<"Name: ";
    getline(cin,name);

    cout<<"Contact Number: ";
    getline(cin,contact);

    cout<<"Gender: Male(1), Female(2): ";
    cin>>g;
    gender=(g==1)?"Male":"Female";

    cin.ignore();
    cout<<"Please tell us your symptoms in short: ";
    getline(cin,disease);

    cout<<"Enter your Age: ";
    cin>>age;

    json data=DataStorage::load("data/patients.json");

    int ID=getExistingId(name,age,gender,"data/patients.json");

    if(ID==-1){
        ID=getNewId("data/patients.json");
        Patient p(name,age,contact,gender,ID,disease);
        data.push_back(p.toJson());
        DataStorage::save("data/patients.json",data);

        cout<<"\nNew patient registered successfully!\n";
    }else{
        cout<<"\nWelcome back!\n";
    }

    cout<<"Your Patient ID is "<<ID<<".\n";
    cout<<"Please wait for your turn. Doctor and room details will be sent to your registered contact.\n\n";
}


    void receptionistLogin(){
    currentUserRole="Receptionist";

    int code;
    cout<<"========== RECEPTIONIST LOGIN ==========\n";
    cout<<"Enter Receptionist PIN: ";
    cin>>code;

    if(code!=rec_pin){
        cout<<"Access Denied!\n";
        return;
    }

    cout<<"Receptionist Access Granted\n";

    while(true){
        int ch;
        cout<<"\n------ RECEPTIONIST MENU ------\n";
        cout<<"1. Allocate Doctor & Room\n";
        cout<<"2. Discharge Patient\n";
        cout<<"0. Logout\n";
        cout<<"Enter choice: ";
        cin>>ch;

        switch(ch){
            case 1: allocateDoctorToPatient(); break;
            case 2: dischargePatient(); break;
            case 0: return;
            default: cout<<"Invalid option\n";
        }
    }
}
void allocateDoctorToPatient(){
    int pid;
    cout<<"Enter Patient ID: ";
    cin>>pid;

    json docData = DataStorage::load("data/doctors.json");
    vector<int> availableDoctors;
    cout << "\n------ AVAILABLE DOCTORS ------\n";
    for(auto &d : docData){
        if(d.contains("availability") && d["availability"].get<bool>()){
            availableDoctors.push_back(d["id"]);
            cout << "ID: " << d["id"] << " | Name: " << d["name"] << " | Specialization: " << d["specialization"] << "\n";
        }
    }

    if(availableDoctors.empty()){
        cout << "No doctors currently available.\n";
        return;
    }

    int docId;
    cout<<"Enter Doctor ID from above list: ";
    cin>>docId;

    if(find(availableDoctors.begin(), availableDoctors.end(), docId) == availableDoctors.end()){
        cout << "Invalid choice or doctor not available.\n";
        return;
    }

    int room;
    cout<<"Enter Room Number: ";
    cin>>room;

    json data=DataStorage::load("data/patients.json");

    for(auto &p:data){
        if(p["id"]==pid){
            p["doctorId"]=docId;
            p["roomNumber"]=room;
            p["admittedStatus"]=true;

            Appointment a;
            p["dateOfAdmission"] = a.getCurrentTime();

            DataStorage::save("data/patients.json",data);

            for(auto &d : docData){
                if(d["id"] == docId){
                    d["availability"] = false;
                    break;
                }
            }
            DataStorage::save("data/doctors.json", docData);

            cout<<"Doctor and room allocated successfully\n";
            return;
        }
    }
    cout<<"Patient not found\n";
}

void doctorLogin() {
    currentUserRole = "Doctor";

    int docId;
    cout << "========== DOCTOR LOGIN ==========\n";
    cout << "Enter your Doctor ID: ";
    cin >> docId;

    cout << "Doctor Access Granted\n";

    while(true){
        int ch;
        cout << "\n------ DOCTOR MENU ------\n";
        cout << "1. View My Patients\n";
        cout << "2. Add Notes to Patient\n";
        cout << "3. Update Patient Disease\n";
        cout << "4. Mark Availability\n";
        cout << "5. Search Patient by ID\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch(ch){
            case 1: viewMyPatients(docId); break;
            case 2: addNotesToPatient(docId); break;
            case 3: updatePatientDisease(docId); break;
            case 4: markDoctorAvailability(docId); break;
            case 5: searchPatient(); break;
            case 0: return;
            default: cout << "Invalid option\n";
        }
    }
}
void dischargePatient(){ int pid; cout<<"Enter Patient ID: "; cin>>pid; json data=DataStorage::load("data/patients.json"); for(auto &p:data){ if(p["id"]==pid){ if(!p.contains("billPaid") || !p["billPaid"].get<bool>()){ cout<<"Billing not completed. Cannot discharge patient.\n"; return; } Patient pat=Patient::fromJson(p); cin.ignore(); string info; cout<<"Enter discharge notes: "; getline(cin,info); pat.discharge(info); cout<<"Patient discharged successfully\n"; return; } } cout<<"Patient not found\n"; }
void viewMyPatients(int docId){
    json data = DataStorage::load("data/patients.json");
    bool found = false;

    cout << "\n------ MY PATIENTS ------\n";
    for(auto &p : data){
        if(p["doctorId"] == docId && p["admittedStatus"].get<bool>()){
            found = true;
            cout << "ID: " << p["id"] 
                 << " | Name: " << p["name"] 
                 << " | Age: " << p["age"] 
                 << " | Room: " << p["roomNumber"]
                 << " | Disease: " << p["disease"] 
                 << "\nNotes: " << p["notes"] << "\n\n";
        }
    }
    if(!found) cout << "No admitted patients assigned to you.\n";
}

void addNotesToPatient(int docId){
    int pid;
    cin.ignore();
    cout << "Enter Patient ID to add notes: ";
    cin >> pid;
    cin.ignore();

    json data = DataStorage::load("data/patients.json");
    for(auto &p : data){
        if(p["id"] == pid && p["doctorId"] == docId){
            string note;
            cout << "Enter note: ";
            getline(cin, note);

            p["notes"] = p["notes"].get<string>() + "\nDoctor Note: " + note;

            DataStorage::save("data/patients.json", data);
            cout << "Note added successfully.\n";
            return;
        }
    }
    cout << "Patient not found or not assigned to you.\n";
}

void updatePatientDisease(int docId){
    int pid;
    cin.ignore();
    cout << "Enter Patient ID to update disease: ";
    cin >> pid;
    cin.ignore();

    json data = DataStorage::load("data/patients.json");
    for(auto &p : data){
        if(p["id"] == pid && p["doctorId"] == docId){
            string disease;
            cout << "Enter updated disease/condition: ";
            getline(cin, disease);

            p["disease"] = disease;
            DataStorage::save("data/patients.json", data);
            cout << "Patient disease updated successfully.\n";
            return;
        }
    }
    cout << "Patient not found or not assigned to you.\n";
}

void markDoctorAvailability(int docId){
    json data = DataStorage::load("data/doctors.json");
    for(auto &d : data){
        if(d["id"] == docId){
            bool avail;
            cout << "Set Availability (1 = Available, 0 = Unavailable): ";
            cin >> avail;
            d["availability"] = avail;
            DataStorage::save("data/doctors.json", data);
            cout << "Availability updated successfully.\n";
            return;
        }
    }
    cout << "Doctor not found!\n";
}


void searchPatient(){
    int pid;
    cout << "Enter Patient ID to search: ";
    cin >> pid;

    json data = DataStorage::load("data/patients.json");
    for(auto &p : data){
        if(p["id"] == pid){
            cout << "\n------ PATIENT DETAILS ------\n";
            cout << "Name: " << p["name"] << "\n";
            cout << "Age: " << p["age"] << "\n";
            cout << "Gender: " << p["gender"] << "\n";
            cout << "Contact: " << p["contact"] << "\n";
            cout << "Disease: " << p["disease"] << "\n";
            cout << "Room No.: " << p["roomNumber"] << "\n";
            cout << "Doctor ID: " << p["doctorId"] << "\n";
            cout << "Admitted: " << (p["admittedStatus"].get<bool>() ? "Yes" : "No") << "\n";
            cout << "Notes: " << p["notes"] << "\n";
            cout << "Date of Admission: " << p["dateOfAdmission"] << "\n";
            cout << "Date of Discharge: " << p["dateOfDischarge"] << "\n";
            cout << "-----------------------------\n";
            return;
        }
    }
    cout << "Patient not found.\n";
}

void adminLogin(){
    currentUserRole = "Admin";

    int code;
    cout << "========== ADMIN LOGIN ==========\n";
    cout << "Enter Admin PIN: ";
    cin >> code;

    if(code != admin_pin){
        cout << "Access Denied!\n";
        return;
    }

    cout << "Admin Access Granted\n";

    while(true){
        int ch;
        cout << "\n------ ADMIN MENU ------\n";
        cout << "1. Add Doctor\n";
        cout << "2. Remove Doctor\n";
        cout << "3. Update Doctor Info\n";
        cout << "4. Update Receptionist PIN\n";
        cout << "5. View All Patients\n";
        cout << "6. View Billing Data\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch(ch){
            case 1: addDoctor(); break;
            case 2: removeDoctor(); break;
            case 3: updateDoctorInfo(); break;
            case 4: updateReceptionistPin(); break;
            case 5: viewAllPatients(); break;
            case 6: viewBillingData(); break;
            case 0: return;
            default: cout << "Invalid option\n";
        }
    }
}

void addDoctor(){
    cin.ignore();
    string name, spec, contact;
    cout << "Enter Doctor Name: ";
    getline(cin, name);
    cout << "Enter Specialization: ";
    getline(cin, spec);
    cout << "Enter Contact Number: ";
    getline(cin, contact);

    json data = DataStorage::load("data/doctors.json");

    int id = 1;
    for(auto &d : data){
        if(d["id"].get<int>() >= id) id = d["id"].get<int>() + 1;
    }

    json doc;
    doc["id"] = id;
    doc["name"] = name;
    doc["specialization"] = spec;
    doc["contact"] = contact;

    data.push_back(doc);
    DataStorage::save("data/doctors.json", data);

    cout << "Doctor added successfully with ID: " << id << "\n";
}

void removeDoctor(){
    int id;
    cout << "Enter Doctor ID to remove: ";
    cin >> id;

    json data = DataStorage::load("data/doctors.json");
    bool found = false;

    for(auto it = data.begin(); it != data.end(); ++it){
        if((*it)["id"] == id){
            data.erase(it);
            DataStorage::save("data/doctors.json", data);
            cout << "Doctor removed successfully\n";
            found = true;
            break;
        }
    }
    if(!found) cout << "Doctor ID not found\n";
}

void updateDoctorInfo(){
    int id;
    cout << "Enter Doctor ID to update: ";
    cin >> id;
    cin.ignore();

    json data = DataStorage::load("data/doctors.json");
    for(auto &d : data){
        if(d["id"] == id){
            string name, spec, contact;
            cout << "Enter new Name (or leave blank to keep current): ";
            getline(cin, name);
            cout << "Enter new Specialization (or leave blank): ";
            getline(cin, spec);
            cout << "Enter new Contact (or leave blank): ";
            getline(cin, contact);

            if(!name.empty()) d["name"] = name;
            if(!spec.empty()) d["specialization"] = spec;
            if(!contact.empty()) d["contact"] = contact;

            DataStorage::save("data/doctors.json", data);
            cout << "Doctor info updated successfully\n";
            return;
        }
    }
    cout << "Doctor ID not found\n";
}

void updateReceptionistPin(){
    extern int rec_pin;
    int newPin;
    cout << "Enter new Receptionist PIN: ";
    cin >> newPin;
    rec_pin = newPin;
    cout << "Receptionist PIN updated successfully\n";
}

void viewAllPatients(){
    json data = DataStorage::load("data/patients.json");
    cout << "\n------ ALL PATIENTS ------\n";
    for(auto &p : data){
        cout << "ID: " << p["id"] 
             << " | Name: " << p["name"] 
             << " | Age: " << p["age"] 
             << " | Gender: " << p["gender"]
             << " | Doctor ID: " << p["doctorId"]
             << " | Room: " << p["roomNumber"]
             << " | Admitted: " << (p["admittedStatus"].get<bool>() ? "Yes" : "No")
             << "\n";
    }
    cout << "---------------------------\n";
}

void viewBillingData(){
    json data = DataStorage::load("data/billing.json");
    cout << "\n------ BILLING DATA ------\n";
    for(auto &b : data){
        cout << "Patient ID: " << b["patientId"]
             << " | Amount: " << b["amount"]
             << " | Status: " << (b["paid"].get<bool>() ? "Paid" : "Pending")
             << "\n";
    }
    cout << "--------------------------\n";
}



    int getExistingId(const string &name, int age, const string &gender, const string &filename) {
    json data = DataStorage::load(filename);
    for(auto &item : data) {
        if(item["name"] == name &&
           item["age"] == age &&
           item["gender"] == gender)
        {
            return item["id"];
        }
    }
    return -1;
    }

    int getNewId(const string &filename){
    json data = DataStorage::load(filename);
    int mx = 0;
    for(auto &p:data){
        if(p["id"].get<int>() > mx) mx = p["id"].get<int>();
    }
    return mx + 1;
    }

};

