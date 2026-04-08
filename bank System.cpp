#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct PersonalInfo {
    string name;
    string fatherName;
    string cnic;
    int age;
    string accountType;
    double income;
    string sourceOfIncome;
};

//Base Class
class Account {
protected:
    long long accountNumber;
    int pin;
    double balance;

public:
    Account() {
        balance = 0.0;
        accountNumber = 0;
        pin = 0;
    }

    void generateAccountDetails() {
        srand(time(0));
        accountNumber = 1000000000LL + rand() % 900000000;
        pin = 1000 + rand() % 9000;
    }

    long long getAccountNumber() { return accountNumber; }
    int getPin() { return pin; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "\nAmount deposited successfully!" << endl;
            cout << "New Balance: Rs. " << balance << endl;
        } else {
            cout << "\nInvalid amount!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "\nInvalid amount!" << endl;
        } else if (amount > balance) {
            cout << "\nInsufficient balance!" << endl;
        } else {
            balance -= amount;
            cout << "\nAmount withdrawn successfully!" << endl;
            cout << "Remaining Balance: Rs. " << balance << endl;
        }
    }

    // Base version: shows balance without any personal context
    virtual void showBalance() {
        cout << "\nCurrent Balance: Rs. " << balance << endl;
    }
};

//Derived Class
class BankAccount : public Account {
public:

    //Taking Structure as Object of class
    PersonalInfo info;

    void registerAccount() {
        cout << "\nEnter Your Name: ";
        cin.ignore();
        getline(cin, info.name);

        cout << "Enter Father's Name: ";
        getline(cin, info.fatherName);

        cout << "Enter CNIC Number: ";
        getline(cin, info.cnic);

        cout << "Enter Age: ";
        cin >> info.age;

        cout << "Account Type (saving / salary / business): ";
        cin >> info.accountType;

        cout << "Enter Monthly Income (Rs.): ";
        cin >> info.income;

        cout << "Source of Income: ";
        cin.ignore();
        getline(cin, info.sourceOfIncome);

        cout << "\nVerifying..." << endl;
        cout << "Congratulations! You are registered at NED Bank." << endl;

        generateAccountDetails();

        cout << "\nYour Account Number: " << accountNumber << endl;
        cout << "Your PIN: " << pin << endl;
    }

    bool login(long long accNum, int enteredPin) {
        return (accNum == accountNumber && enteredPin == pin);
    }

    // Overridden version: shows balance WITH the account holder's name
    void showBalance() override {
        cout << "\nAccount Holder : " << info.name << endl;
        cout << "Current Balance: Rs. " << balance << endl;
    }
};

// Handles menu options after a successful login
void handleBankingMenu(BankAccount &acc) {
    int option;
    while (true) {
        cout << "\n1. Deposit\n2. Withdraw\n3. Show Balance\n4. Exit\nChoose: ";
        cin >> option;

        if (option == 1) {
            double amount;
            cout << "Enter amount: ";
            cin >> amount;
            acc.deposit(amount);
        } else if (option == 2) {
            double amount;
            cout << "Enter amount: ";
            cin >> amount;
            acc.withdraw(amount);
        } else if (option == 3) {
            acc.showBalance();   // calls BankAccount's overridden version
        } else if (option == 4) {
            cout << "\nLogged out." << endl;
            break;
        } else {
            cout << "\nInvalid option." << endl;
        }
    }
}

// Handles account registration (choice 2)
void handleNewAccount(BankAccount &acc, bool &accountCreated) {
    if (accountCreated) {
        cout << "\nAccount already exists. Please login." << endl;
    } else {
        acc.registerAccount();
        accountCreated = true;
    }
}

// Handles login and banking session (choice 1)
void handleLogin(BankAccount &acc, bool accountCreated) {
    if (!accountCreated) {
        cout << "\nNo account found. Please create one first." << endl;
        return;
    }

    long long accNum;
    int enteredPin;

    cout << "\nEnter Account Number: ";
    cin >> accNum;
    cout << "Enter PIN: ";
    cin >> enteredPin;

    if (!acc.login(accNum, enteredPin)) {
        cout << "\nIncorrect account number or PIN." << endl;
        return;
    }

    cout << "\nLogin successful! Welcome, " << acc.info.name << endl;
    handleBankingMenu(acc);
}

int main() {
    //Object creation
    BankAccount myAccount;
    bool accountCreated = false;
    int choice;

    while (true) {
        cout << "\nWelcome to NED Bank\nDo you have a account?\n" << endl;
        cout << "1) Yes\n2) No\n3) Exit\nEnter your choice: ";
        cin >> choice;

        if      (choice == 1) handleLogin(myAccount, accountCreated);
        else if (choice == 2) handleNewAccount(myAccount, accountCreated);
        else if (choice == 3) { cout << "\nExiting program..." << endl; return 0; }
        else                  cout << "\nInvalid input!" << endl;
    }
}
