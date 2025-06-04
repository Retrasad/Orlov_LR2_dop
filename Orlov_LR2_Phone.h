#ifndef PHONE_H
#define PHONE_H

#include <string>
#include <vector>

using namespace std;

extern const string DATA_FILE;

class Phone {
private:
    string lastName;
    string firstName;
    string middleName;
    string address;
    string phoneNumber;
    int vgorodCallTime;
    int mgorodCallTime;

public:
    Phone();
    ~Phone();
    
    string getLastName() const { return lastName; }
    string getFirstName() const { return firstName; }
    string getMiddleName() const { return middleName; }
    string getAddress() const { return address; }
    string getPhoneNumber() const { return phoneNumber; }
    int getLocalCallTime() const { return vgorodCallTime; }
    int getInternationalCallTime() const { return mgorodCallTime; }
    
    void setLastName(const string &ln) { lastName = ln; }
    void setFirstName(const string &fn) { firstName = fn; }
    void setMiddleName(const string &mn) { middleName = mn; }
    void setAddress(const string &addr) { address = addr; }
    void setPhoneNumber(const string &num) { phoneNumber = num; }
    void setLocalCallTime(int time) { vgorodCallTime = time; }
    void setInternationalCallTime(int time) { mgorodCallTime = time; }
    
    void display() const;
    
    static Phone* inputFromKeyboard();
    
    bool exceedsLocalCallTime(int porog) const;
    bool usedInternationalCalls() const;
    
    bool operator<(const Phone &other) const;
};

void loadDataFromFile(const string &filename, vector<Phone> &phones);
void addPhoneToVector(vector<Phone> &phones);
void displayAllPhones(const vector<Phone> &phones);
void displayPhonesExceedingLocalTime(const vector<Phone> &phones, int porog);
void displayPhonesWithInternationalCalls(const vector<Phone> &phones);
void displayPhonesInAlphabeticalOrder(vector<Phone> &phones);

#endif