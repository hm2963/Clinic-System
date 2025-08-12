# Clinic Appointment System (C++)

[![Language: C++11](https://img.shields.io/badge/C%2B%2B-11-blue.svg)](https://isocpp.org/)
[![Build: g++](https://img.shields.io/badge/build-g%2B%2B-brightgreen.svg)](#build--run)
[![CI](https://github.com/hm2963/Clinic-System/actions/workflows/ci.yml/badge.svg)](../../actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-lightgrey.svg)](#license)

A simple, file-backed clinic appointment system written in C++. Patients can **schedule**, **view**, and **cancel** appointments with three eye-care departments: **Ophthalmology**, **Optometry**, and **Opticianry**. Data persists in human-readable `.txt` files, keeping the project portable and easy to run.

---

## Table of Contents
- [Features](#features)
- [Demo](#demo)
- [Project Structure](#project-structure)
- [Build & Run](#build--run)
- [Data Files & Formats](#data-files--formats)
- [Sample Data (included)](#sample-data-included)
- [Design Notes](#design-notes)
- [Known Limitations](#known-limitations)
- [Roadmap](#roadmap)
- [Extras (CI & .gitignore)](#extras-ci--gitignore)
- [Small Code Polish (nice-to-have)](#small-code-polish-nice-to-have)
- [License](#license)

---

## Features
- ✅ Text menu with three actions:
  - **Schedule** an appointment
  - **View** an appointment (by Patient ID & department)
  - **Cancel** an appointment (frees the time slot)
- ✅ Separate files per department (doctors & appointments)
- ✅ Persistent storage using plain `.txt` files
- ✅ Prevents double-booking by marking slots as `BOOKED`

---

## Demo

On launch:
Clinic Appointment System

Schedule an Appointments

View Appointment

Cancel Appointment

Exit
Enter your choice:

**Scheduling flow (example):**
1. Choose department (1–3)
2. Pick a listed doctor and an available slot
3. Enter name, surname, and patient ID  
→ Success message; files updated (`*appointments.txt` & doctor timeslots with `BOOKED`).

**Viewing/Canceling:**  
Enter Patient ID and select department; the app looks up (or removes) the appointment in the matching `*appointments.txt`.

---

## Project Structure
Clinic-System/

Clinic-System/

├─ FINAL_PROJECT.cpp

├─ ophthalmologists.txt

├─ optometrists.txt

├─ opticians.txt

├─ ophthalmologistappointments.txt

├─ optometristappointments.txt

├─ opticianappointments.txt

└─ README.md

Build & Run
Linux / macOS / WSL (g++)

g++ -std=c++11 FINAL_PROJECT.cpp -o clinic
./clinic

Windows (MSVC Developer Command Prompt)

cl /EHsc /std:c++14 FINAL_PROJECT.cpp
FINAL_PROJECT.exe
The code targets C++11; newer standards also work.

Data Files & Formats
Doctor files (ophthalmologists.txt, optometrists.txt, opticians.txt)
Each doctor block:

Name (line 1)

Surname (line 2)

Room number (line 3, integer)

One timeslot per line (e.g., 9:00 AM).
Booked slots become 9:00 AM BOOKED.

Blank line separates doctors

Example:
John
Smith
101
9:00 AM BOOKED
10:00 AM
2:00 PM

Appointment files (*appointments.txt)
Key–value lines per appointment, separated by a dashed line:
Patient ID: 123
Patient Name: helin
Patient Surname: mazi
Doctor Name: John
Doctor Surname: Smith
Room Number: 101
Time Slot: 9:00 AM
-----------------------

Sample Data (included)
ophthalmologists.txt
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
Emma
Johnson
102
10:00 AM BOOKED
11:00 AM
3:00 PM

opticians.txt
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
Patient ID: 123
Patient Name: helin
Patient Surname: mazi
Doctor Name: John
Doctor Surname: Smith
Room Number: 101
Time Slot: 9:00 AM
-----------------------

optometristappointments.txt
Patient ID: 234
Patient Name: seyran
Patient Surname: mazi
Doctor Name: Emma
Doctor Surname: Johnson
Room Number: 102
Time Slot: 10:00 AM
-----------------------

opticianappointments.txt
Patient ID: 345
Patient Name: ilker
Patient Surname: mazi
Doctor Name: Zam
Doctor Surname: Davis
Room Number: 103
Time Slot: 11:00 AM
-----------------------

Design Notes
OOP model

Person → base for Patient and Doctor

Appointment composes a Patient, Doctor, and a timeslot

ClinicSystem loads doctors and implements actions

Single source of truth

Doctor availability lives in doctor files; booking toggles BOOKED inline

Separation by department

Keeps data isolated and simple to reason about

Known Limitations
Input robustness: Minimal validation; unexpected input may require re-run.

Menu typo: The menu prints “Schedule an Appointments” (extra “s”).

Session lifecycle: A new ClinicSystem is constructed each loop iteration (files keep state; in-memory data reloads each time).

No concurrency: Simultaneous runs could race on files.

IDs: No cross-department uniqueness checks.

Roadmap
Switch to CSV/JSON with light schema validation

Centralize appointments; derive availability dynamically

Stronger input validation & re-prompting on bad input

Unit tests + CI (GitHub Actions) for parsing & booking logic

Export daily schedules per department

Optional TUI/GUI (e.g., ncurses) for nicer UX

Extras (CI & .gitignore)
GitHub Actions: /.github/workflows/ci.yml

name: build
on:
  push:
  pull_request:
jobs:
  linux-gpp:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Build
        run: g++ -std=c++11 FINAL_PROJECT.cpp -o clinic
      - name: Smoke test (exit immediately)
        run: printf "4\n" | ./clinic
.gitignore
# C/C++ build artifacts
*.o
*.obj
*.exe
*.out
*.log
*.pdb
*.ilk

# OS noise
.DS_Store
Thumbs.db

# Editors
.vscode/

