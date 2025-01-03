#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <windows.h>
using namespace std;

class Login {
private:
    string LoginID,Password;
public:
    Login(){
        LoginID="";
        Password="";
    }
    void setID(string id)
    {
        LoginID = id;
    }
    void setPW(string pw)
    {
        Password = pw;
    }
    string getID()
    {
        return LoginID;
    }
    string getPW()
    {
        return Password;
    }
};

void registration(Login &log)
 {
    system("cls");
    string id,pw;
    cout<<"\tEnter Login ID: ";
    cin>>id;
    log.setID(id);

start:
    cout<<"\tEnter A Strong Password (min 8 chars): ";
    cin>>pw;
    if(pw.length()>=8)
    {
        log.setPW(pw);
    }
    else
    {
        cout<<"\tEnter Minimum 8 Characters!"<<endl;
        goto start;
    }
    ofstream outfile("Login.txt", ios::app);
    if (!outfile)
    {
        cout<<"\tError: File Can't Open!"<<endl;
    }
    else
    {
        outfile<<id<<":"<<pw<<endl;
        cout<<"\tUser Registered Successfully!"<<endl;
    }
    outfile.close();
    Sleep(2000);
}

bool login()
 {
    system("cls");
    string id, pw;
    cout<<"\tEnter Login ID: ";
    cin>>id;

    cout <<"\tEnter Password: ";
    cin>>pw;

    ifstream infile("Login.txt");
    if (!infile)
    {
        cout<<"\tError: File Can't Open!"<<endl;
        return false;
    }
    string line;
    while (getline(infile,line))
    {
        stringstream ss(line);
        string userID,userPW;
        getline(ss,userID,':');
        getline(ss,userPW);

        if (id==userID&&pw==userPW)
        {
            cout<<"\tLogin Successful! Welcome "<<id<<"!"<<endl;
            infile.close();
            Sleep(2000);
            return true;
        }
    }
    cout <<"\tError: Incorrect Login ID or Password!"<<endl;
    infile.close();
    Sleep(2000);
    return false;
 }class Employee {
protected:
    int id;
    string name;
    double hourlyRate;
    double hoursWorked;
    string type;
    string level;

public:
    Employee(int empId, string empName, double rate, double hours, string empType, string empLevel)
    {
        id=empId;
        name=empName;
        hourlyRate=rate;
        hoursWorked=hours;
        type=empType;
        level=empLevel;
    }

    Employee(){
     id=0;
     name="";
     hourlyRate=0.0;
     hoursWorked=0.0;
     type="";
     level="";
    }

    virtual ~Employee() {}

    int getId()const{
         return id;
    }
    string getName()const{
        return name;
    }
    void setHourlyRate(double rate){
        hourlyRate = rate;
    }
    double getHourlyRate()const{
        return hourlyRate;
    }

    void setHoursWorked(double hours){
        hoursWorked = hours;
    }
    double getHoursWorked()const{
        return hoursWorked;
    }

    void setType(const string& type){
        this->type=type;
    }
    string getType()const{
        return type;
    }

    void setLevel(const string& level) {
        this->level=level;
    }
    string getLevel() const {
        return level;
    }
    virtual double calculateSalary() const {
        return hourlyRate * hoursWorked;
    }

    virtual void displayDetails() const {
        cout << left << setw(10) << id << setw(20) << name
             << setw(15) << hourlyRate << setw(15) << hoursWorked
             << setw(15) << calculateSalary() << setw(15) << type << setw(15) << level << endl;
    }

    virtual string toFileString() const {
        stringstream ss;
        ss << id << "," << name << "," << hourlyRate << "," << hoursWorked << "," << type << "," << level;
        return ss.str();
    }

    static Employee* fromFileString(const string &line) {
        stringstream ss(line);
        string token;
        int id;
        string name, type, level;
        double rate, hours;
        getline(ss, token, ',');
        id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ',');
        rate = stod(token);
        getline(ss, token, ',');
        hours = stod(token);
        getline(ss, type, ',');
        getline(ss, level);

        return new Employee(id, name, rate, hours, type, level);
    }
};


class FullTimeEmployee : public Employee {
public:
    FullTimeEmployee(int empId, string empName, double rate, double hours, string empLevel)
        : Employee(empId, empName, rate, hours, "Full-Time", empLevel) {}

       virtual double calculateSalary() const override {

        return hourlyRate * hoursWorked * 1.1;
    }
};


class PartTimeEmployee : public Employee {
public:
    PartTimeEmployee(int empId, string empName, double rate, double hours, string empLevel)
        : Employee(empId, empName, rate, hours, "Part-Time", empLevel) {}

       virtual double calculateSalary() const override {

        return hourlyRate * hoursWorked;
    }
};


class InternEmployee : public Employee {
public:
    InternEmployee(int empId, string empName, double rate, double hours, string empLevel)
        : Employee(empId, empName, rate, hours, "Intern", empLevel) {}

       virtual double calculateSalary() const override {

        return hourlyRate * hoursWorked * 0.5;
    }
};


class EntryLevel : public Employee {
public:
    EntryLevel(int empId, string empName, double rate, double hours, string empType)
        : Employee(empId, empName, rate, hours, empType, "Entry-Level") {}

    virtual double calculateSalary() const override {
        return Employee::calculateSalary();
    }

    virtual void displayDetails() const override {
        cout << left << setw(10) << id << setw(20) << name
             << setw(15) << hourlyRate << setw(15) << hoursWorked
             << setw(15) << calculateSalary() << setw(15) << type << setw(15) << level << endl;
    }
};


class SeniorLevel : public Employee {
public:
    SeniorLevel(int empId, string empName, double rate, double hours, string empType)
        : Employee(empId, empName, rate, hours, empType, "Senior-Level") {}

    virtual double calculateSalary() const override {
        return hourlyRate * hoursWorked + 1000;
    }

    virtual void displayDetails() const override {
        cout << left << setw(10) << id << setw(20) << name
             << setw(15) << hourlyRate << setw(15) << hoursWorked
             << setw(15) << calculateSalary() << setw(15) << type << setw(15) << level << endl;
    }
};

int main() {
     Login log;
bool loggedIn = false;

    while (!loggedIn) {
        system("cls");
        int choice;
        cout << "Welcome to the System\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
             registration(log);
        } else if (choice == 2) {
            loggedIn = login();
        } else if (choice == 3) {
            cout << "Exiting...\n";
            return 0;
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    }
}

