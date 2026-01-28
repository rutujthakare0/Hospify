# Hospify – Hospital Management System

Hospify is a console-based Hospital Management System built entirely in **C++**, designed to simulate how core hospital operations are handled in a structured, modular, and persistent backend system. The project focuses on clean architecture, object-oriented design, and reliable data storage using JSON files.

This system allows hospitals to digitally manage patients, doctors, appointments, emergency cases, and billing records while enforcing role-based access control.

---

## Features

* Patient management (add, view, update records)
* Doctor management with specialization and availability
* Appointment scheduling and tracking
* Emergency case handling
* Multiple billing workflows (OPD, surgery, emergency)
* Role-based access control (Admin, Receptionist, Doctor)
* Persistent storage using JSON files
* Modular, object-oriented architecture

---

## Project Architecture

The project follows a **layered and modular architecture**:

* **Presentation Layer**: Console-based menus and user interaction
* **Business Logic Layer**: Core logic for hospital operations
* **Data Layer**: JSON-based persistent storage

Each entity is implemented using separate header (`.h`) and source (`.cpp`) files to ensure separation of concerns and maintainability.

---

## Folder Structure

```
Hospify/
│
├── data/
│   ├── patients.json       # Stores patient records
│   ├── doctors.json        # Stores doctor records
│   ├── appointments.json   # Stores appointment data
│   └── billing.json        # Stores billing information
│
├── include/
│   └── json.hpp            # nlohmann JSON library
│
├── src/
│   ├── Person.h            # Base class for Patient and Doctor
│   ├── Patient.h / .cpp    # Patient entity and logic
│   ├── Doctor.h / .cpp     # Doctor entity and logic
│   ├── Appointment.h / .cpp# Appointment handling
│   ├── billing.h / .cpp    # Billing workflows
│   ├── DataStorage.h / .cpp# JSON file handling and persistence
│   ├── hospitalSystem.cpp  # Core system controller
│   └── main.cpp            # Program entry point
│
└── myProgram.exe           # Compiled executable (Windows)
```

---

## Core Components Explained

### 1. Person (Base Class)

* Acts as a parent class for both `Patient` and `Doctor`
* Contains common attributes like name, age, gender, contact, and ID
* Promotes code reuse and inheritance

### 2. Patient Module

* Manages patient details and medical records
* Supports adding, updating, and viewing patient information
* Data is persisted in `patients.json`

### 3. Doctor Module

* Stores doctor details such as specialization, room number, availability, and salary
* Enables doctor lookup and appointment mapping
* Data is persisted in `doctors.json`

### 4. Appointment Module

* Handles scheduling and tracking of appointments
* Links patients and doctors using unique IDs
* Stored in `appointments.json`

### 5. Billing Module

* Manages OPD, surgery, and emergency billing workflows
* Calculates charges and generates billing records
* Stored in `billing.json`

### 6. DataStorage Module

* Acts as the persistence layer of the system
* Handles reading from and writing to JSON files
* Ensures data consistency across program executions

### 7. HospitalSystem Controller

* Central coordinator of the application
* Manages menus, role-based access, and user flow
* Connects all modules together

---

## Role-Based Access Control

The system supports multiple roles:

* **Admin**: Full access to all system functionalities
* **Receptionist**: Patient registration, appointment handling, billing
* **Doctor**: View appointments and patient details

Each role is authenticated using a PIN-based login system.

---

## Data Persistence

All data is stored in JSON format using the **nlohmann/json** library. This allows:

* Easy serialization and deserialization of objects
* Human-readable data storage
* Persistent records across application restarts

---

## Build & Run Instructions

### Prerequisites

* C++ compiler (g++ / MinGW / MSVC)
* C++17 or later

### Compile (Example using g++)

```
g++ src/*.cpp -Iinclude -o Hospify
```

### Run

```
./Hospify
```

---

## Future Enhancements

* Password hashing for authentication
* File locking and concurrency handling
* GUI or web-based frontend
* Database integration (MySQL / PostgreSQL)
* Advanced reporting and analytics

---


---

## Author

Developed by **Rutuj Thakare**
