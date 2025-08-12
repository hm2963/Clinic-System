# Clinic Appointment System (C++)

[![Language: C++](https://img.shields.io/badge/C%2B%2B-11-blue.svg)](https://isocpp.org/)
[![Build: g++](https://img.shields.io/badge/build-g%2B%2B-brightgreen.svg)](#build--run)
[![License: MIT](https://img.shields.io/badge/license-MIT-lightgrey.svg)](#license)

A simple, file-backed clinic appointment system written in C++. Patients can **schedule**, **view**, and **cancel** appointments with three types of eye-care practitioners: **Ophthalmologists**, **Optometrists**, and **Opticians**. Data persists in plain `.txt` files to keep the project portable and easy to run.

---

## Table of Contents
- [Features](#features)
- [How It Works](#how-it-works)
- [Project Structure](#project-structure)
- [Build & Run](#build--run)
- [Data Files & Formats](#data-files--formats)
- [Sample Data (included)](#sample-data-included)
- [Demo](#demo)
- [Design Highlights](#design-highlights)
- [Known Limitations](#known-limitations)
- [Future Improvements](#future-improvements)
- [License](#license)

---

## Features
- ✅ Text-based menu with three core actions:
  - Schedule an appointment
  - View an appointment (by Patient ID and department)
  - Cancel an appointment (frees the time slot)
- ✅ Three departments with separate doctor and appointment files
- ✅ Persistent storage using human-readable `.txt` files
- ✅ Basic input validation and prevention of double-booking (marks slots with `BOOKED`)

---

## How It Works
- **Domain model**
  - `Person` → base class for `Patient` and `Doctor`
  - `Appointment` holds a `Patient`, `Doctor`, and a `timeslot`
  - `ClinicSystem` loads doctors from text files on startup and handles all menu actions
- **Persistence**
  - Doctors are defined in `ophthalmologists.txt`, `optometrists.txt`, and `opticians.txt`
  - Appointments are logged in `*appointments.txt` per department
  - Booking a slot appends `" BOOKED"` to the timeslot in the relevant doctor file

---

## Project Structure
Clinic-System/
├─ FINAL_PROJECT.cpp
├─ ophthalmologists.txt
├─ optometrists.txt
├─ opticians.txt
├─ ophthalmologistappointments.txt
├─ optometristappointments.txt
├─ opticianappointments.txt
└─ README.md

yaml
Copy
Edit

---

## Build & Run

### Using g++ (Linux/macOS/WSL/MinGW)
```bash
g++ -std=c++11 FINAL_PROJECT.cpp -o clinic
./clinic
Using MSVC (Developer Command Prompt)
bat
Copy
Edit
cl /EHsc /std:c++14 FINAL_PROJECT.cpp
FINAL_PROJECT.exe
Note: The code targets C++11 features; newer standards also work.

Data Files & Formats
Doctor files (ophthalmologists.txt, optometrists.txt, opticians.txt)
Per doctor block:

Name (line 1)

Surname (line 2)

Room number (line 3, integer)

One timeslot per line (e.g., 9:00 AM); a slot becomes 9:00 AM BOOKED when taken

Blank line separates doctors

Example block:

makefile
Copy
Edit
John
Smith
101
9:00 AM BOOKED
10:00 AM
2:00 PM
Appointment files (*appointments.txt)
Key–value lines per appointment:

Patient ID: <int>

Patient Name: <string>

Patient Surname: <string>

Doctor Name: <string>

Doctor Surname: <string>

Room Number: <int>

Time Slot: <string>

A line of dashes ----------------------- separates appointments.

Sample Data (included)
ophthalmologists.txt
txt
Copy
Edit
John
Smith
101
9:00 AM BOOKED
10:00 AM
2:00 PM

Amy
Rose
181
8:00 AM
9:30 AM
3:50 PM
optometrists.txt
txt
Copy
Edit
Emma
Johnson
102
10:00 AM BOOKED
11:00 AM
3:00 PM
opticians.txt
txt
Copy
Edit
Zam
Davis
103
11:00 AM BOOKED
1:00 PM
4:00 PM

Yugmee
Gidiya
109
9:00 AM
10:00 AM
12:00 PM
ophthalmologistappointments.txt
txt
Copy
Edit
Patient ID: 123
Patient Name: helin
Patient Surname: mazi
Doctor Name: John
Doctor Surname: Smith
Room Number: 101
Time Slot: 9:00 AM
-----------------------
optometristappointments.txt
txt
Copy
Edit
Patient ID: 234
Patient Name: seyran
Patient Surname: mazi
Doctor Name: Emma
Doctor Surname: Johnson
Room Number: 102
Time Slot: 10:00 AM
-----------------------
opticianappointments.txt
txt
Copy
Edit
Patient ID: 345
Patient Name: ilker
Patient Surname: mazi
Doctor Name: Zam
Doctor Surname: Davis
Room Number: 103
Time Slot: 11:00 AM
-----------------------
Demo
On launch you’ll see:

markdown
Copy
Edit
Clinic Appointment System
1. Schedule an Appointments
2. View Appointment
3. Cancel Appointment
4. Exit
Enter your choice:
Scheduling flow (example):

Choose department (1–3)

Pick a listed doctor and an available slot (numbers shown)

Enter your name, surname, and patient ID

Success message + files updated

Viewing/Canceling

Enter your Patient ID and select the department; the app searches the corresponding appointment file and prints (or removes) your appointment.

Design Highlights
OOP organization

Person abstracts shared identity fields

Patient adds ID

Doctor adds roomno and timeslots

Appointment composes Patient + Doctor + timeslot

Single source of truth

Doctor availability lives in the doctor files; booking toggles " BOOKED" in place

Separation by department

Makes it easy to scale or swap data per department

Known Limitations
Input robustness: Console input is minimal; unexpected input (e.g., non-integers) may require re-run.

Menu typo: The menu prints Schedule an Appointments (extra “s”).

Session lifecycle: A new ClinicSystem is constructed each loop iteration (files keep state; in-memory data is reloaded each time).

No concurrency control: Simultaneous runs could race on files.

No validation on names/IDs: IDs are not checked for uniqueness across departments.

Future Improvements
Replace plain text with a lightweight format (CSV/JSON) and add schema validation

Centralize appointment storage; derive availability on the fly

Stronger input validation and re-prompting on bad input

Unit tests and CI workflow (GitHub Actions) for parsing and booking logic

Export/print daily schedules per department

Add a small GUI or TUI (e.g., ncurses) for a nicer UX

