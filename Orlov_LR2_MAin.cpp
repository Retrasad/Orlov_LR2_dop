#include "Orlov_LR2_Phone.h"
#include "Orlov_LR2_Phone.cpp"
#include <iostream>
#include <map>
#include <functional>
#include <limits>

using namespace std;

void showMenu() {
    cout << "\nМеню базы данных Phone:\n";
    cout << "1. Загрузить данные из файла\n";
    cout << "2. Добавить новую запись\n";
    cout << "3. Показать все записи\n";
    cout << "4. Показать записи, где был превышен порог времени внутригородских разговоров\n";
    cout << "5. Показать записи, где использовалось время междугородних разговоров\n";
    cout << "6. Показать записи в алфавитном порядке\n";
    cout << "7. Выход\n";
    cout << "Введите свой выбор: ";
}

int main() {
    vector<Phone> phones;
    map<int, function<void()>> menuActions;
    
    menuActions[1] = [&]() {
        loadDataFromFile(DATA_FILE, phones);
        cout << "Данные загружены из файла.\n";
    };
    
    menuActions[2] = [&]() {
        addPhoneToVector(phones);
        cout << "Новая запись добавлена.\n";
    };
    
    menuActions[3] = [&]() {
        cout << "\nВсе записи:\n";
        displayAllPhones(phones);
    };
    
    menuActions[4] = [&]() {
        int porog;
        cout << "Введите порог времени внутригородских разговоров (в минутах): ";
        cin >> porog;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nЗаписи, где время внутригородиских разговоров превысело " << porog << " минут(ы):\n";
        displayPhonesExceedingLocalTime(phones, porog);
    };
    
    menuActions[5] = [&]() {
        cout << "\nЗаписи, где использовалось время междугородних разговоров:\n";
        displayPhonesWithInternationalCalls(phones);
    };
    
    menuActions[6] = [&]() {
        cout << "\nЗаписи в алфавитном порядке:\n";
        displayPhonesInAlphabeticalOrder(phones);
    };
    
    menuActions[7] = []() {
        cout << "Выход из программы.\n";
        exit(0);
    };
    
    while (true) {
        showMenu();
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        try {
            auto action = menuActions.at(choice);
            action();
        } catch (const out_of_range&) {
            cout << "Ошибочный выбор. Попробуйте вновь.\n";
        }
    }
    
    return 0;
}