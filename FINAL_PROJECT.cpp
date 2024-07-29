#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//Person class is a base class for storing name and surname (since name and surname are both common variables for Patient and Doctor class).
class Person {
protected:
    string name;
    string surname;
public:
    //Constructor with its initializer list for Person class.
    Person(const string& Name, const string& Surname) : name(Name), surname(Surname) {}
    inline string getName() const { //Getter for name.
        return name;
    }
    inline string getSurname() const { //Getter for surname.
        return surname;
    }
};

//Patient is a derived class which is inherited as public from the Person class.
class Patient : public Person {
private:
    int ID;
public:
    //Constructor with its initializer list for Patient class.
    Patient(const string& Name, const string& Surname, int id) : Person(Name, Surname), ID(id) {}
    inline int getID() const { //Getter for Patient ID.
        return ID;
    }
};

//Doctor is a derived class which is inherited as public from the Person class.
class Doctor : public Person {
private:
    int roomno;
    vector<string> timeslots;
public:
    //Constructor with its initializer list for Doctor class.
    Doctor(const string& Name, const string& Surname, int Roomno) : Person(Name, Surname), roomno(Roomno) {}
    inline int getRoomno() const { //Getter for the room number of the doctor.
        return roomno;
    }
    inline void setAvailableTimeSlots(vector<string>& slots) { //Setter for the vector of timeslots for the doctor.
        timeslots = slots;
    }
    inline vector<string>& getAvailableTimeSlots() { //Getter for the vector of timeslots for the doctor.
        return timeslots;
    }
};

//Appointment class is a class to store appointment related information such as the doctor, patient and the time of appointment.
class Appointment {
private:
    Patient patient;
    Doctor doctor;
    string timeslot;
public:
    //Constructor with its initializer list for Appointment class. It receives a Patient and a Doctor object (passed by referencec), and the time of the appointment which will be chosen by the patient.
    Appointment(const Patient& patient, const Doctor& doctor, const string& timeslot) : patient(patient), doctor(doctor), timeslot(timeslot) {}
    const Patient& getPatient() const { //Getter for the Patient relevant to the appointment.
        return patient;
    }
    inline const Doctor& getDoctor() const { //Getter for the Doctor relevant to the appointment.
        return doctor;
    }
    inline string getTimeslot() const { //Getter for the appointment timeslot.
        return timeslot;
    }
    inline int getPatientID() const { //Getter for the ID of the Patient relevant to the appointment.
        return patient.getID();
    }
    inline string getPatientName() const { //Getter for the name of the Patient relevant to the appointment.
        return patient.getName();
    }
    inline string getPatientSurname() const { //Getter for the surname of the Patient relevant to the appointment.
        return patient.getSurname();
    }
    inline string getDrName() const { //Getter for the name of the Doctor relevant to the appointment.
        return doctor.getName();
    }
    inline string getDrSurname() const { //Getter for the surname of the Doctor relevant to the appointment.
        return doctor.getSurname();
    }
    inline int getDrRoomNo() const { //Getter for the room number of the Doctor relevant to the appointment.
        return doctor.getRoomno();
    }
};

class ClinicSystem {
private:
    vector<Doctor> ophthalmologists;
    vector<Doctor> optometrists;
    vector<Doctor> opticians;
public:
    ClinicSystem() {
        //ClinicSystem constructor calls the function that reads the files containing doctor information, so that, the vectors of Doctor objects are ready when the user sees the menu.
        loadDoctorsFromFile("ophthalmologists.txt", ophthalmologists);
        loadDoctorsFromFile("optometrists.txt", optometrists);
        loadDoctorsFromFile("opticians.txt", opticians);
    }
    //loadDoctorFromFile is a function that reads the files containing doctor information and stores the Doctor objects in vectors. It receives the file name and the reference to the vector of Doctor objects as parameters.
    //The function is structured this way, so that, it can be used to read the files for all types of doctors in the clinic.
    void loadDoctorsFromFile(const string& filename, vector<Doctor>& doctors) {
        ifstream inFile(filename);
        if (inFile.is_open()) { //To check if the file is opened correctly
            string name, surname;
            int roomno;
            vector<string> timeslots;
            string line;

            //The while loop is used to read the doctor information and repeates as long as there is information for doctor name, surname and room number.
            //Since name and surname are strings, getline() is used, however, since roomno is an integer it is read as inFile>>roomno
            while (getline(inFile, name) && getline(inFile, surname) && inFile >> roomno) {
                getline(inFile, line); //Since roomno is read from the file as inFile>>roomno, getline(inFile, line) is used to get rid of the end of line character.
                //Each time this loop runs, the information of one doctor will be added to the vector of doctors.
                //Hence, if the timeslot is not cleared, each followiing doctor will also have the timeslots of the previous doctors.
                timeslots.clear();
                while (getline(inFile, line) && !line.empty()) { //To make sure the time slots are read until an empty line is encountered because I used an empty line to separate doctor information in the files.
                    timeslots.push_back(line); //Add each line containing a timeslot to the the vector of timeslots
                }
                Doctor doctor(name, surname, roomno); //Create a Doctor object using the name,surname, and roomno read from the file.
                doctor.setAvailableTimeSlots(timeslots); //Set the timeslots of the doctor.
                doctors.push_back(doctor); //Add the Doctor object to the vector of doctors.
            }
            inFile.close(); //Close the file.
        }
    }

    void scheduleAppointment() {
        int choice;
        cout << endl;
        //Display doctor options.
        cout << "1. Ophthalmologist" << endl;
        cout << "2. Optometrist" << endl;
        cout << "3. Optician" << endl;
        cout << "4. Main Menu" << endl;
        cout << "Please enter your choice for the relevant eye care practitioner: ";
        cin >> choice;
        //A pointer to a vector of Doctor objects is used, so that, the function can be used to schedule appointment for all types of doctors.
        vector<Doctor>* doctors = nullptr;
        string departmentFileName, departmentAppointmentsFileName;
        //The switch statement is useful in this case because it will assign the specific vector of Doctor objects to the pointer based on the user input.
        //It will also assign the name of the file for the specific doctor type and the appointment file of the specific department.
        switch (choice) {
        case 1:
            doctors = &ophthalmologists;
            departmentFileName = "ophthalmologists.txt";
            departmentAppointmentsFileName = "ophthalmologistappointments.txt";
            cout << "Available Ophthalmologists: " << endl;
            break;
        case 2:
            doctors = &optometrists;
            departmentFileName = "optometrists.txt";
            departmentAppointmentsFileName = "optometristappointments.txt";
            cout << "Available Optometrists: " << endl;
            break;
        case 3:
            doctors = &opticians;
            departmentFileName = "opticians.txt";
            departmentAppointmentsFileName = "opticianappointments.txt";
            cout << "Available Opticians: " << endl;
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            return;
        }

        //A for loop is used to print the doctor information to the user.
        for (size_t i = 0; i < doctors->size(); ++i) { //The loop iterates through the vector of Doctor obejcts and size_t is used instead of int to make sure the indices never become negative.
            if ((*doctors)[i].getAvailableTimeSlots().size() > 0) { //To check if the doctor has any timeslots.
                cout << i+1 << ") Doctor: " << (*doctors)[i].getName() << " " << (*doctors)[i].getSurname() << endl; //To print name and surname of the doctor.
                cout << "Room Number: " << (*doctors)[i].getRoomno() << endl; //To print room number of the doctor.
                cout << "Available Time Slots:" << endl; //To print time slots of the doctor.
                for (int j = 0; j < (*doctors)[i].getAvailableTimeSlots().size(); ++j) { //This for loop prints all the timeslots of the doctor either booked or available.
                    cout << j + 1 << ". " << (*doctors)[i].getAvailableTimeSlots()[j] << endl;
                }
                cout << endl;
            }
        }

        int drno = -1;
        int drslot = -1;
        cout << "Please enter the number of the doctor you would like to schedule an appointment for: "; //To get user's choice of doctor.
        cin >> drno;
        cout << "Please enter the available slot you would like to schedule an appointment for: "; //To get user's choice of timeslot.
        cin >> drslot;

        if (drno >= 1 && drno <= doctors->size()) { //To check if the number of the chosen doctor is between 1 and the size of the vector of Doctor objects.
            Doctor& selectedDoctor = (*doctors)[drno - 1]; //To get the Doctor object that the user wanted to schedule an appointment with.

            if (drslot >= 1 && drslot <= selectedDoctor.getAvailableTimeSlots().size()) {//To check if the number of the chosen timeslot is between 1 and the size of the vector of timeslots.
                int chosenSlot = drslot - 1; //Since indices start from 0, I assigned drslot-1 to the chosenSlot to get the index of the timeslot.
                string& chosenTimeSlot = selectedDoctor.getAvailableTimeSlots()[chosenSlot];

                //To check if the chosen timeslot was already booked, find() is used. find() returns string::npos if the substring does not exist in the string.
                if (chosenTimeSlot.find("BOOKED") != string::npos) { 
                    cout << "The selected timeslot has already been booked. Please choose another time." << endl;
                    return;
                }

                //If the chosen doctor and timeslot are valid, the scheduling proceeds.
                string patientName, patientSurname;
                int patientID;
                cout << "Enter your name: ";
                cin >> patientName;
                cout << "Enter your surname: ";
                cin >> patientSurname;
                cout << "Enter your ID: ";
                cin >> patientID;

                //To create a patient object with the entered information.
                Patient patient(patientName, patientSurname, patientID);
                //To create an appointment object with relevant patient, doctor, and timeslot information.
                Appointment appointment(patient, selectedDoctor, chosenTimeSlot);
                //To mark the selected timeslot as "BOOKED" for the doctor.
                chosenTimeSlot += " BOOKED";
                //To save the updated information of the doctor to the relevant text file.
                saveDoctorToFile(departmentFileName, *doctors);

                //To save the appointment information to the relevant text file.
                ofstream outFile(departmentAppointmentsFileName, ios::app); //ios::app is used, so that, the scheduled appointment just appends to the appointment file.
                if (outFile.is_open()) { //To check if the file is opened correctly.
                    outFile << "Patient ID: " << appointment.getPatientID() << endl; //Output patient ID.
                    outFile << "Patient Name: " << appointment.getPatientName() << endl; //Output patient name.
                    outFile << "Patient Surname: " << appointment.getPatientSurname() << endl; //Output patient surname.
                    outFile << "Doctor Name: " << appointment.getDrName() << endl; //Output doctor name.
                    outFile << "Doctor Surname: " << appointment.getDrSurname() << endl; //Output doctor surname.
                    outFile << "Room Number: " << appointment.getDrRoomNo() << endl; //Output room number.
                    outFile << "Time Slot: " << appointment.getTimeslot() << endl; //Output time of the appointment.
                    outFile << "-----------------------" << endl;
                    outFile.close(); //Close the file.
                    cout << "Appointment booked successfully!" << endl;
                }
                else {
                    cout << "Unable to save appointment to file!" << endl;
                }
            }
            else {
                cout << "Invalid time slot selection!" << endl;
            }
        }
        else {
            cout << "Invalid doctor selection!" << endl;
        }
    }

    void viewAppointments() {
        cout << "Enter your patient ID to view the appointment: ";
        int patientID;
        cin >> patientID;
        //To ask the user to choose the department in which they have the appointment for.
        cout << "Choose the department for which you want to cancel the appointment:" << endl;
        cout << "1. Ophthalmologist" << endl;
        cout << "2. Optometrist" << endl;
        cout << "3. Optician" << endl;
        int departmentChoice;
        cin >> departmentChoice;
        string aptFileName;
        //A pointer to a vector of Doctor objects is used, so that, the function can be used to schedule appointment for all types of doctors.
        vector<Doctor>* doctors = nullptr;
        //To determine the file names and doctors vector based on the department choice using a switch statement. This way, the viewappointment() can be used for all departments.
        switch (departmentChoice) {
        case 1: //Ophthalmologist
            aptFileName = "ophthalmologistappointments.txt";
            doctors = &ophthalmologists;
            break;
        case 2: //Optometrist
            aptFileName = "optometristappointments.txt";
            doctors = &optometrists;
            break;
        case 3: //Optician
            aptFileName = "opticianappointments.txt";
            doctors = &opticians;
            break;
        default:
            cout << "Invalid department choice." << endl;
            return;
        }
        //I defined a vector of Appointment objects to store the appointments that are in the file.
        vector<Appointment> readAppointments = readAppointmentsFromFile(aptFileName);
        bool found = false; //This variable is declared to see if the appointment that the user wants to view exists.
        
        for (size_t i = 0; i < readAppointments.size(); ++i) { //The for loop iterates through the vector of Appointment objects.
            if (readAppointments[i].getPatientID() == patientID) { //To check if the ID the user entered matches the Patient ID of any existing appointments.
                found = true; //To indicate the appointment of the user is found.
                cout << "Patient ID: " << readAppointments[i].getPatientID()<<endl; //Print Patient ID.
                cout << "Patient Name: " << readAppointments[i].getPatientName()<<endl; //Print Patient name. 
                cout << "Patient Surname: " << readAppointments[i].getPatientSurname() << endl; //Print Patient surname.
                cout << "Doctor Name: " << readAppointments[i].getDrName() << endl; //Print Doctor name.
                cout << "Doctor Surname: " << readAppointments[i].getDrSurname() << endl; //Print Doctor surname.
                cout << "Room Number: " << readAppointments[i].getDrRoomNo() << endl; //Print Doctor room number.
                cout << "Time Slot: " << readAppointments[i].getTimeslot() << endl; //Print time of appointment.
            }
        }
        
        if (found == false) { //If this variable is still false, it means that the user does not have scheduled appointment with that department.
            cout << "You do not have a scheduled appointment!" << endl;
        }
    }

    void cancelAppointment() {
        cout << "Enter your patient ID to cancel the appointment: ";
        int patientID;
        cin >> patientID; //To get Patient ID
        cout << "Choose the department for which you want to cancel the appointment:" << endl; //To get the department at which the user has an appointment.
        cout << "1. Ophthalmologist" << endl;
        cout << "2. Optometrist" << endl;
        cout << "3. Optician" << endl;
        int departmentChoice;
        cin >> departmentChoice;
        // Determine the file names and doctors vector based on the department choice
        string aptFileName;
        string drFileName;
        vector<Doctor>* doctors = nullptr;

        //To determine the file names and doctors vector based on the department choice using a switch statement. This way, the cancelappointment() can be used for all departments.
        switch (departmentChoice) {
        case 1: //Ophthalmologist
            aptFileName = "ophthalmologistappointments.txt";
            drFileName = "ophthalmologists.txt";
            doctors = &ophthalmologists;
            break;
        case 2: //Optometrist
            aptFileName = "optometristappointments.txt";
            drFileName = "optometrists.txt";
            doctors = &optometrists;
            break;
        case 3: //Optician
            aptFileName = "opticianappointments.txt";
            drFileName = "opticians.txt";
            doctors = &opticians;
            break;
        default:
            cout << "Invalid department choice." << endl;
            return;
        }

        //I defined a vector of Appointment objects to store the appointments that are in the file.
        vector<Appointment> readAppointments = readAppointmentsFromFile(aptFileName);
        //This variable is declared to see if the appointment that the user wants to cancel exists.
        bool found = false;

        for (size_t i = 0; i < readAppointments.size(); ++i) { //The for loop iterates through the vector of Appointment objects.
            if (readAppointments[i].getPatientID() == patientID) { //To check if the ID the user entered matches the Patient ID of any existing appointments.
                found = true; //To indicate the appointment of the user is found.
                const Doctor& canceledDoctor = readAppointments[i].getDoctor(); //To get the Doctor object relevant to the appointment to be canceled.
                const string& canceledTimeSlot = readAppointments[i].getTimeslot(); //To get the timeslot relevant to the appointment to be canceled.
                for (Doctor& doctor : *doctors) { //The for loop iterates through the specific vector of doctors.
                    if (doctor.getName() == canceledDoctor.getName() && doctor.getSurname() == canceledDoctor.getSurname()) { //To find the relevant Doctor object among the vector of doctors by checking if the name and surname matches.
                        vector<string>& timeSlots = doctor.getAvailableTimeSlots(); //To get the timeslots of the doctor relevant to the appointment to be canceled.
                        for (string& slot : timeSlots) { //The for loop iterates through the vector of timeslots.
                            if (slot == canceledTimeSlot + " BOOKED") { //To find the timeslot of the doctor that was "BOOKED" after scheduling this appointment.
                                slot = canceledTimeSlot; //To remove the word "BOOKED" from the timeslot of the doctor, so that, it appears available to next users.
                                break; //The loop can stop after finding the specific timeslot.
                            }
                        }
                        break; //The loop can stop after finding the specific doctor.
                    }
                }               
                readAppointments.erase(readAppointments.begin() + i);//To erase the canceled appointment from the vector of appointments.
                break; //The loop can stop after finding the specific appointment.
            }
        }

        if (found==false) { //If this variable is still false, it means that the user does not have scheduled appointment with that department.
            cout << "You do not have a scheduled appointment!" << endl;
        }

        //To save the updated appointment information to the text file.
        ofstream outFile2(aptFileName);
        if (outFile2.is_open()) { //To check if the file is opened correctly.
            for (const Appointment& appointment : readAppointments) { //The for loop iterates through the vector of appointment objects.
                outFile2 << "Patient ID: " << appointment.getPatientID() << endl; //Output patient ID.
                outFile2 << "Patient Name: " << appointment.getPatientName() << endl; //Output patient name.
                outFile2 << "Patient Surname: " << appointment.getPatientSurname() << endl; //Output patient surname.
                outFile2 << "Doctor Name: " << appointment.getDrName() << endl; //Output doctor name.
                outFile2 << "Doctor Surname: " << appointment.getDrSurname() << endl; //Output doctor surname.
                outFile2 << "Room Number: " << appointment.getDrRoomNo() << endl; //Output doctor room number.
                outFile2 << "Time Slot: " << appointment.getTimeslot() << endl; //Output time of appointment.
                outFile2 << "-----------------------" << endl;
            }
            outFile2.close(); //Close the file.
            cout << "Appointment canceled successfully!" << endl;
        }
        else {
            cout << "Unable to update appointment file!" << endl;
        }

        //To update relevant file of doctors.
        saveDoctorToFile(drFileName, *doctors);
    }

    void saveDoctorToFile(const string& fileName, vector<Doctor>& doctors) {
        //To save the updated information of the doctor to the relevant text file.
        ofstream outFile(fileName);
        if (outFile.is_open()) { //To check if the file is opened correctly.
            for (size_t i = 0; i < doctors.size(); ++i) { //To iterate through the specific vector of doctors.
                outFile << doctors[i].getName() << endl; //Output doctor name.
                outFile << doctors[i].getSurname() << endl; //Output doctor surname.
                outFile << doctors[i].getRoomno() << endl; //Output doctor room number.
                for (size_t j = 0; j < doctors[i].getAvailableTimeSlots().size(); ++j) { //The for loop is to output the timeslots.
                    outFile << doctors[i].getAvailableTimeSlots()[j] << endl;
                }
                if (i < doctors.size() - 1) { //To add an empty line after each doctor except the last one.
                    outFile << endl;
                }
            }
            outFile.close();
            cout << "Data saved successfully!" << endl;
        }
        else {
            cout << "Unable to save data to file!" << endl;
        }
    }

    vector<Appointment> readAppointmentsFromFile(const string& aptFileName) {
        vector<Appointment> readAppointments;
        ifstream aptFile(aptFileName);
        if (aptFile.is_open()) { //To check if the file is opened correctly.
            string line;
            int aptPatientID = -1;
            
            while (getline(aptFile, line)) { //To keep reading the file until the end of file.
                
                if (line.find("Patient ID: ") != string::npos) { //To check if the line contains "Patient ID: ".
                    //To get patient ID from the line and convert it to an integer using stoi().
                    aptPatientID = stoi(line.substr(line.find(":") + 2)); //line.find(":") finds the index of ":". Adding 2 to the index of ":" to get the ID using line.substr().
                }
                
                //To keep reading other appointment details.
                getline(aptFile, line); //The line starts with "Patient Name: " in the file.
                string aptPatientName = line.substr(line.find(":") + 2);
                getline(aptFile, line); //The line starts with "Patient Surname: " in the file.
                string aptPatientSurname = line.substr(line.find(":") + 2);
                getline(aptFile, line); //The line starts with "Doctor Name: " in the file.
                string aptDoctorName = line.substr(line.find(":") + 2);
                getline(aptFile, line); //The line starts with "Doctor Surname: " in the file.
                string aptDoctorSurname = line.substr(line.find(":") + 2);
                getline(aptFile, line); //The line starts with "Room Number: " in the file.
                int aptRoomNumber = stoi(line.substr(line.find(":") + 2));
                getline(aptFile, line); //The line starts with "Time Slot: " in the file.
                string aptTimeSlot = line.substr(line.find(":") + 2);
                getline(aptFile, line); //To get rid of the line separating each appointment.              
                Patient aptPatient(aptPatientName, aptPatientSurname, aptPatientID); //To create a Patient object according to the information read from the file.               
                Doctor aptDoctor(aptDoctorName, aptDoctorSurname, aptRoomNumber); //To create a Doctor object according to the information read from the file.                          
                Appointment appointment(aptPatient, aptDoctor, aptTimeSlot); //To create an Appointment object according to the information read from the file.
                readAppointments.push_back(appointment); //Add the Appointment object to the vector of appointments.                
            }
            aptFile.close(); //Close the appointment file.
        }
        else {
            cout << "Unable to open appointment file!" << endl;
        }   
        return readAppointments;
    }


};

int main() {
    while (true) {
        ClinicSystem clinic;
        cout << "Clinic Appointment System" << endl;
        cout << "1. Schedule an Appointments" << endl;
        cout << "2. View Appointment" << endl;
        cout << "3. Cancel Appointment" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            clinic.scheduleAppointment();
            break;
        case 2:
            clinic.viewAppointments();
            break;
        case 3:
            clinic.cancelAppointment();
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
