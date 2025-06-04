#include "Orlov_LR2_Phone.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

const string DATA_FILE = "phones_data.txt";
vector<Phone> phoneDatabase;

Phone::Phone() : lastName(""), firstName(""), middleName(""), address(""), 
                phoneNumber(""), vgorodCallTime(0), mgorodCallTime(0) {}

Phone::~Phone() {}

void Phone::display() const {
    cout << "ФИО: " << lastName << " " << firstName << " " << middleName << "\n"
         << "Адрес: " << address << "\n"
         << "Номер телефона: " << phoneNumber << "\n"
         << "Время внутригородских разговоров: " << vgorodCallTime << " минут\n"
         << "Время междугородних разговоров: " << mgorodCallTime << " минут\n"
         << "------------------------------------\n";
}

Phone* Phone::inputFromKeyboard() {
    Phone* newPhone = new Phone();
    string input;
    int time;
    
    cout << "Введите фамилию: ";
    getline(cin, input);
    newPhone->setLastName(input);
    
    cout << "Введите имя: ";
    getline(cin, input);
    newPhone->setFirstName(input);
    
    cout << "Введите отчество: ";
    getline(cin, input);
    newPhone->setMiddleName(input);
    
    cout << "Введите адрес: ";
    getline(cin, input);
    newPhone->setAddress(input);
    
    cout << "Введите номер телефона: ";
    getline(cin, input);
    newPhone->setPhoneNumber(input);
    
    cout << "Введите время внутригородских разговоров (в минутах): ";
    cin >> time;
    newPhone->setLocalCallTime(time);
    
    cout << "Введите время междугородних разговоров (в минутах): ";
    cin >> time;
    newPhone->setInternationalCallTime(time);
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    return newPhone;
}

bool Phone::exceedsLocalCallTime(int porog) const {
    return vgorodCallTime > porog;
}

bool Phone::usedInternationalCalls() const {
    return mgorodCallTime > 0;
}

bool Phone::operator<(const Phone &other) const {
    if (lastName != other.lastName) return lastName < other.lastName;
    if (firstName != other.firstName) return firstName < other.firstName;
    return middleName < other.middleName;
}

bool isValidName(const string &name) {
    return !name.empty() && name.find_first_not_of("абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ- ") == string::npos;
}

bool isValidPhoneNumber(const string &number) {
    return !number.empty() && number.find_first_not_of("0123456789-+() ") == string::npos;
}

bool isValidTime(int time) {
    return time >= 0;
}

string inputString(const string &prompt, bool (*validator)(const string&)) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
        if (!validator(input)) {
            cout << "Ошибочный ввод. Попробуйте снова.\n";
        }
    } while (!validator(input));
    return input;
}

int inputInt(const string &prompt, bool (*validator)(int)) {
    int value;
    do {
        cout << prompt;
        cin >> value;
        if (!validator(value)) {
            cout << "Ошибочный ввод. Попробуйте снова.\n";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (!validator(value));
    return value;
}

void loadDataFromFile(const string &filename, vector<Phone> &phones) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка запуска файла: " << filename << endl;
        return;
    }
    
    Phone phone;
    string line;
    
    while (getline(file, line)) {
        phone.setLastName(line);
        getline(file, line);
        phone.setFirstName(line);
        getline(file, line);
        phone.setMiddleName(line);
        getline(file, line);
        phone.setAddress(line);
        getline(file, line);
        phone.setPhoneNumber(line);
        
        int time;
        file >> time;
        phone.setLocalCallTime(time);
        file >> time;
        phone.setInternationalCallTime(time);
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        
        phones.push_back(phone);
    }
    
    file.close();
}

void addPhoneToVector(vector<Phone> &phones) {
    Phone* newPhone = Phone::inputFromKeyboard();
    phones.push_back(*newPhone);
    delete newPhone;
}

void displayAllPhones(const vector<Phone> &phones) {
    if (phones.empty()) {
        cout << "Нет телефона в базе данных.\n";
        return;
    }
    
    for (const auto &phone : phones) {
        phone.display();
    }
}

void displayPhonesExceedingLocalTime(const vector<Phone> &phones, int porog) {
    bool found = false;
    for (const auto &phone : phones) {
        if (phone.exceedsLocalCallTime(porog)) {
            phone.display();
            found = true;
        }
    }
    
    if (!found) {
        cout << "Нет номеров телефонов, время внутригородских разговоров которых превышает лимит в " << porog << " минут(ы).\n";
    }
}

void displayPhonesWithInternationalCalls(const vector<Phone> &phones) {
    bool found = false;
    for (const auto &phone : phones) {
        if (phone.usedInternationalCalls()) {
            phone.display();
            found = true;
        }
    }
    
    if (!found) {
        cout << "Нет номеров, использовавших время междугородных разговоров.\n";
    }
}

void displayPhonesInAlphabeticalOrder(vector<Phone> &phones) {
    if (phones.empty()) {
        cout << "Нет телефона в базе данных.\n";
        return;
    }
    
    sort(phones.begin(), phones.end());
    displayAllPhones(phones);
}