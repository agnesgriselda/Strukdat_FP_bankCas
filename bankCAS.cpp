#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Transaction class
class Transaction {
private:
    string transactionId;
    string date;
    double amount;
    string type;
    string fromAccountId;
    string toAccountId;

public:
    Transaction(string tid, string d, double a, string t, string from, string to)
        : transactionId(tid), date(d), amount(a), type(t), fromAccountId(from), toAccountId(to) {}

    void viewDetails() {
        cout << "Transaction ID: " << transactionId << ", Date: " << date
             << ", Amount: " << amount << ", Type: " << type
             << ", From Account ID: " << fromAccountId
             << ", To Account ID: " << toAccountId << endl;
    }
};

// Account class
class Account {
protected:
    string accountId;
    string userId;
    double balance;
    string accountType;
    vector<Transaction> transactions;

public:
    Account(string aid, string uid, double bal, string type)
        : accountId(aid), userId(uid), balance(bal), accountType(type) {}

    string getAccountId() { return accountId; }
    double getBalance() { return balance; }

    virtual void viewBalance() { cout << "Balance: " << balance << endl; }

    virtual void viewTransactions() {
        for (auto& txn : transactions) {
            txn.viewDetails();
        }
    }

    void transferFunds(string toAccountId, double amount) {
        if (balance >= amount) {
            balance -= amount;
            transactions.emplace_back("T" + to_string(transactions.size() + 1), "2024-06-04", amount, "Transfer", accountId, toAccountId);
            cout << "Transfer successful. New balance: " << balance << endl;
        } else {
            cout << "Insufficient funds for transfer." << endl;
        }
    }

    virtual void displayAccountType() {
        cout << "Account Type: " << accountType << endl;
    }
};

// SavingsAccount class
class SavingsAccount : public Account {
private:
    double interestRate;
    string startDate;
    string maturityDate;

public:
    SavingsAccount(string aid, string uid, double bal, double rate, string start, string maturity)
        : Account(aid, uid, bal, "Savings"), interestRate(rate), startDate(start), maturityDate(maturity) {}

    void displayAccountType() override {
        cout << "Savings Account with interest rate: " << interestRate << "%" << endl;
    }
};

// InvestmentAccount class
class InvestmentAccount : public Account {
private:
    string investmentType;
    double amount;
    string startDate;
    string endDate;

public:
    InvestmentAccount(string aid, string uid, double bal, string type, double amt, string start, string end)
        : Account(aid, uid, bal, "Investment"), investmentType(type), amount(amt), startDate(start), endDate(end) {}

    void displayAccountType() override {
        cout << "Investment Account with type: " << investmentType << ", amount: " << amount << endl;
    }
};

// Base User class
class User {
protected:
    string userId;
    string name;
    string email;
    string password;
    string phone;
    string address;
    vector<Account*> accounts;

public:
    User(string uid, string n, string e, string p, string ph, string addr)
        : userId(uid), name(n), email(e), password(p), phone(ph), address(addr) {}

    string getUserID() { return userId; }
    string getName() { return name; }
    string getEmail() { return email; }
    void setPassword(string p) { password = p; }
    string getPhone() { return phone; }
    string getAddress() { return address; }

    void addAccount(Account* account) {
        accounts.push_back(account);
    }

    void viewAccounts() {
        for (auto& acc : accounts) {
            cout << "Account ID: " << acc->getAccountId() << ", Balance: " << acc->getBalance() << endl;
            acc->displayAccountType();
        }
    }

    void registerUser() {
        cout << "Enter user ID: ";
        cin >> userId;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter email: ";
        cin >> email;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter phone: ";
        cin >> phone;
        cout << "Enter address: ";
        cin.ignore();
        getline(cin, address);
        cout << "User registered successfully!" << endl;
    }

    bool login(string uid, string pass) {
        return (userId == uid && password == pass);
    }

    void logout() {
        cout << "User logged out successfully." << endl;
    }

    void updateProfile() {
        cout << "Enter new name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter new email: ";
        cin >> email;
        cout << "Enter new password: ";
        cin >> password;
        cout << "Enter new phone: ";
        cin >> phone;
        cout << "Enter new address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Profile updated successfully!" << endl;
    }

    virtual void displayInfo() {
        cout << "User ID: " << userId << ", Name: " << name << ", Email: " << email << endl;
    }

    virtual void addAccountMenu() {
        string accountId, type, startDate, maturityDate;
        double balance, rate;
        
        cout << "Enter Account ID: ";
        cin >> accountId;
        cout << "Enter initial balance: ";
        cin >> balance;
        cout << "Enter account type (Savings/Investment): ";
        cin >> type;
        
        if (type == "Savings") {
            cout << "Enter interest rate: ";
            cin >> rate;
            cout << "Enter start date (YYYY-MM-DD): ";
            cin >> startDate;
            cout << "Enter maturity date (YYYY-MM-DD): ";
            cin >> maturityDate;
            addAccount(new SavingsAccount(accountId, userId, balance, rate, startDate, maturityDate));
        } else if (type == "Investment") {
            double amount;
            string investmentType, endDate;
            cout << "Enter investment type: ";
            cin >> investmentType;
            cout << "Enter amount: ";
            cin >> amount;
            cout << "Enter start date (YYYY-MM-DD): ";
            cin >> startDate;
            cout << "Enter end date (YYYY-MM-DD): ";
            cin >> endDate;
            addAccount(new InvestmentAccount(accountId, userId, balance, investmentType, amount, startDate, endDate));
        } else {
            cout << "Invalid account type!" << endl;
        }
    }

    const vector<Account*>& getAccounts() const {
        return accounts;
    }
};

// PremiumUser class inheriting from User
class PremiumUser : public User {
private:
    string membershipLevel;
    double discountRate;

public:
    PremiumUser(string uid, string n, string e, string p, string ph, string addr, string level, double discount)
        : User(uid, n, e, p, ph, addr), membershipLevel(level), discountRate(discount) {}

    string getMembershipLevel() { return membershipLevel; }
    void setMembershipLevel(string level) { membershipLevel = level; }
    double getDiscountRate() { return discountRate; }
    void setDiscountRate(double discount) { discountRate = discount; }

    void displayMembershipInfo() {
        cout << "Membership Level: " << membershipLevel << ", Discount Rate: " << discountRate << "%" << endl;
    }

    void displayInfo() override {
        User::displayInfo();
        displayMembershipInfo();
    }

    void viewPremiumInfo() {
        displayMembershipInfo();
    }
};

// Function prototypes
void showMainMenu();
void showUserMenu();
void registerUser(vector<User*>& users);
void loginUser(vector<User*>& users);
void displayUsers(vector<User*>& users);

int main() {
    vector<User*> users;
    int choice;

    while (true) {
        showMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser(users);
                break;
            case 2:
                loginUser(users);
                break;
            case 3:
                displayUsers(users);
                break;
            case 4:
                cout << "Exiting the application. Goodbye!" << endl;
                // Free allocated memory
                for (User* user : users) {
                    delete user;
                }
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}

void showMainMenu() {
    cout << "\n=== BankEase Mobile Banking Application ===" << endl;
    cout << "1. Register New User" << endl;
    cout << "2. Login" << endl;
    cout << "3. Display All Users (Admin only)" << endl;
    cout << "4. Exit" << endl;
}

void showUserMenu() {
    cout << "\n=== User Menu ===" << endl;
    cout << "1. Update Profile" << endl;
    cout << "2. View Accounts" << endl;
    cout << "3. Add Account" << endl;
    cout << "4. Transfer Funds" << endl;
    cout << "5. View Transactions" << endl;
    cout << "6. View Premium Info" << endl;
    cout << "7. Logout" << endl;
}

void registerUser(vector<User*>& users) {
    string userId, name, email, password, phone, address, userType;

    cout << "Enter user type (Regular/Premium): ";
    cin >> userType;

    if (userType == "Regular") {
        User* newUser = new User("", "", "", "", "", "");
        newUser->registerUser();
        users.push_back(newUser);
    } else if (userType == "Premium") {
        string membershipLevel;
        double discountRate;
        cout << "Enter membership level: ";
        cin >> membershipLevel;
        cout << "Enter discount rate: ";
        cin >> discountRate;

        PremiumUser* newPremiumUser = new PremiumUser("", "", "", "", "", "", membershipLevel, discountRate);
        newPremiumUser->registerUser();
        users.push_back(newPremiumUser);
    } else {
        cout << "Invalid user type!" << endl;
    }
}

void loginUser(vector<User*>& users) {
    string userId, password;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter password: ";
    cin >> password;

    for (User* user : users) {
        if (user->login(userId, password)) {
            cout << "Login successful!" << endl;
            int userChoice;
            while (true) {
                showUserMenu();
                cout << "Enter your choice: ";
                cin >> userChoice;
                switch (userChoice) {
                    case 1:
                        user->updateProfile();
                        break;
                    case 2:
                        user->viewAccounts();
                        break;
                    case 3:
                        user->addAccountMenu();
                        break;
                    case 4:
                        {
                            string fromAccountId, toAccountId;
                            double amount;
                            cout << "Enter from account ID: ";
                            cin >> fromAccountId;
                            cout << "Enter to account ID: ";
                            cin >> toAccountId;
                            cout << "Enter amount to transfer: ";
                            cin >> amount;

                            for (Account* acc : user->getAccounts()) {
                                if (acc->getAccountId() == fromAccountId) {
                                    acc->transferFunds(toAccountId, amount);
                                    break;
                                }
                            }
                        }
                        break;
                    case 5:
                        {
                            for (Account* acc : user->getAccounts()) {
                                acc->viewTransactions();
                            }
                        }
                        break;
                    case 6:
                        {
                            PremiumUser* premiumUser = dynamic_cast<PremiumUser*>(user);
                            if (premiumUser) {
                                premiumUser->viewPremiumInfo();
                            } else {
                                cout << "This feature is available for Premium Users only." << endl;
                            }
                        }
                        break;
                    case 7:
                        user->logout();
                        return;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
            }
        }
    }
    cout << "Login failed! Invalid user ID or password." << endl;
}

void displayUsers(vector<User*>& users) {
    if (users.empty()) {
        cout << "No users registered." << endl;
        return;
    }

    for (User* user : users) {
        user->displayInfo();
        cout << "---------------------------" << endl;
    }
}
