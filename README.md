# Aplikasi Mobile Banking BankCAS

## Definisi

BankCAS adalah aplikasi mobile banking yang memungkinkan pengguna untuk mengelola rekening bank, melakukan transaksi, dan melihat detail rekening. Aplikasi ini dibangun menggunakan prinsip pemrograman berorientasi objek (OOP) dalam C++. README ini memberikan penjelasan rinci tentang kelas dan fungsi inti dalam file `bankCAS.cpp`, menggambarkan konsep OOP (Pemrograman Berorientasi Objek).

## Definisi Kelas

### Kelas Transaction

```cpp
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
```
Kelas ini mendefinisikan struktur transaksi dengan atribut seperti `transactionId`, `date`, `amount`, `type`, `fromAccountId`, dan `toAccountId`. Metode `viewDetails` digunakan untuk menampilkan detail transaksi.

### Kelas Account

```cpp
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
```
Kelas ini mendefinisikan sebuah akun bank dengan atribut seperti `accountId`, `userId`, `balance`, `accountType`, dan `transactions`. Metode `transferFunds` digunakan untuk mentransfer dana antara akun dan mencatat transaksi.

### Kelas SavingsAccount dan InvestmentAccount

```cpp
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
```
Kelas `SavingsAccount` dan `InvestmentAccount` mewarisi dari kelas `Account`, masing-masing dengan atribut tambahan yang spesifik untuk jenis akun, seperti `interestRate` untuk `SavingsAccount` dan `investmentType` untuk `InvestmentAccount`.

### Kelas User

```cpp
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
```
Kelas `User` mendefinisikan seorang pengguna aplikasi, dengan atribut seperti `userId`, `name`, `email`, `password`, `phone`, dan `address`. Kelas ini mencakup metode untuk mengelola akun dan profil pengguna, termasuk `registerUser`, `login`, `logout`, `updateProfile`, dan `viewAccounts`.

### Kelas PremiumUser

```cpp
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
```
Kelas `PremiumUser` memperluas kelas `User` dengan menambahkan atribut dan metode khusus untuk pengguna

 premium, seperti `membershipLevel` dan `discountRate`.

## Prototipe Fungsi

```cpp
void registerUser(vector<User*>& users);
User* loginUser(vector<User*>& users);
void mainMenu(User* user);
void transferFunds(User* user);
```
Prototipe fungsi ini menguraikan fungsi utama yang digunakan dalam aplikasi untuk registrasi pengguna, login, navigasi menu utama, dan transfer dana.

## Fungsi Utama

```cpp
int main() {
    vector<User*> users;
    User* loggedInUser = nullptr;

    int choice;
    do {
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerUser(users);
            break;
        case 2:
            loggedInUser = loginUser(users);
            if (loggedInUser != nullptr) {
                mainMenu(loggedInUser);
            }
            break;
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 3);

    for (User* user : users) {
        delete user;
    }

    return 0;
}
```
Fungsi `main` adalah titik masuk aplikasi, menyediakan menu untuk registrasi pengguna, login, dan keluar. Fungsi ini menggunakan `vector` untuk menyimpan objek `User` dan mengelola sesi pengguna.

## Fungsi Inti

### Fungsi Registrasi Pengguna

```cpp
void registerUser(vector<User*>& users) {
    string userId, name, email, password, phone, address;
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
    users.push_back(new User(userId, name, email, password, phone, address));
    cout << "User registered successfully!" << endl;
}
```
Fungsi `registerUser` mengumpulkan informasi pengguna dari input dan membuat objek `User` baru, menambahkannya ke `vector` pengguna.

### Fungsi Login Pengguna

```cpp
User* loginUser(vector<User*>& users) {
    string userId, password;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter password: ";
    cin >> password;
    for (User* user : users) {
        if (user->login(userId, password)) {
            cout << "Login successful! Welcome, " << user->getName() << endl;
            return user;
        }
    }
    cout << "Invalid user ID or password!" << endl;
    return nullptr;
}
```
Fungsi `loginUser` memvalidasi kredensial pengguna dan mengembalikan pointer ke objek `User` jika login berhasil.

### Fungsi Menu Utama

```cpp
void mainMenu(User* user) {
    int choice;
    do {
        cout << "1. View Accounts" << endl;
        cout << "2. Transfer Funds" << endl;
        cout << "3. Update Profile" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            user->viewAccounts();
            break;
        case 2:
            transferFunds(user);
            break;
        case 3:
            user->updateProfile();
            break;
        case 4:
            user->logout();
            break;
        default:
            cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 4);
}
```
Fungsi `mainMenu` menyediakan menu utama untuk pengguna yang sudah login, memungkinkan mereka untuk melihat akun, mentransfer dana, memperbarui profil, dan keluar.

### Fungsi Transfer Dana

```cpp
void transferFunds(User* user) {
    string fromAccountId, toAccountId;
    double amount;
    cout << "Enter from account ID: ";
    cin >> fromAccountId;
    cout << "Enter to account ID: ";
    cin >> toAccountId;
    cout << "Enter amount to transfer: ";
    cin >> amount;

    for (Account* account : user->getAccounts()) {
        if (account->getAccountId() == fromAccountId) {
            account->transferFunds(toAccountId, amount);
            return;
        }
    }
    cout << "From account not found!" << endl;
}
```
Fungsi `transferFunds` menangani transfer dana antara akun, memvalidasi akun asal dan melakukan transaksi.

## Pembagian Konsep OOP pada Kode

1. **Class & Object:**
   - Kelas adalah blueprint untuk menciptakan objek. Dalam kode ini, kita memiliki beberapa kelas seperti `Transaction`, `Account`, `SavingsAccount`, `InvestmentAccount`, `User`, dan `PremiumUser`.
   - Objek adalah instance dari sebuah kelas. Contohnya adalah ketika kita membuat objek seperti `Transaction`, `Account`, `SavingsAccount`, dan lain-lain di dalam fungsi `main()`.

2. **Attribute / Property & Method / Behavior:**
   - Atribut adalah data yang dimiliki oleh suatu objek. Contohnya adalah `transactionId`, `date`, `amount` di kelas `Transaction`.
   - Metode adalah perilaku yang dimiliki oleh suatu objek. Contohnya adalah `viewDetails()` di kelas `Transaction`.

3. **Constructor:**
   - Constructor adalah metode khusus yang dieksekusi saat objek dibuat. Dalam kode ini, kita memiliki constructor untuk setiap kelas seperti `Transaction`, `Account`, `SavingsAccount`, dan `InvestmentAccount`. Mereka digunakan untuk menginisialisasi nilai awal atribut.

4. **Setter & Getter:**
   - Setter adalah metode yang digunakan untuk mengatur nilai atribut dalam sebuah objek. Dalam kode ini, kita tidak memiliki metode setter eksplisit, tetapi kita mengatur nilai atribut melalui konstruktor.
   - Getter adalah metode yang digunakan untuk mengambil nilai atribut dari sebuah objek. Contohnya adalah `getAccountId()` dan `getBalance()` di kelas `Account`.

5. **Encapsulation:**
   - Encapsulation adalah konsep menyembunyikan detail implementasi dari luar dunia. Dalam kode ini, kita menggunakan encapsulation dengan menjadikan atribut private atau protected, sehingga hanya metode dalam kelas yang dapat mengakses dan mengubah nilainya.

6. **Inheritance:**
   - Inheritance adalah konsep di mana sebuah kelas dapat mewarisi atribut dan metode dari kelas lain. Dalam kode ini, `SavingsAccount` dan `InvestmentAccount` mewarisi atribut dan metode dari kelas `Account`.

7. **Overriding, Overloading:**
   - Overriding terjadi saat sebuah metode dalam subclass memiliki implementasi yang berbeda dengan metode dalam superclass. Contohnya adalah `displayAccountType()` di kelas `SavingsAccount` dan `InvestmentAccount` yang mengoverride metode dengan nama yang sama di kelas `Account`.
   - Overloading terjadi saat sebuah kelas memiliki beberapa metode dengan nama yang sama tetapi berbeda dalam jumlah atau tipe parameter. Contohnya tidak terdapat dalam kode ini.

8. **Access Modifiers (Private, Protected, dan Public):**
   - Private membatasi akses langsung ke anggota kelas hanya ke dalam kelas itu sendiri. Contohnya adalah atribut `transactionId` dalam kelas `Transaction`.
   - Protected membatasi akses ke anggota kelas kepada kelas itu sendiri dan subclass. Contohnya adalah atribut `accountId` dalam kelas `Account`.
   - Public memungkinkan akses ke anggota kelas dari mana saja. Contohnya adalah metode `registerUser()` dalam kelas `User`.

9. **Abstraction:**
   - Abstraction adalah konsep menyembunyikan detail implementasi dan hanya menampilkan fungsionalitas yang diperlukan. Dalam kode ini, kita menggunakan abstraksi dengan menyediakan antarmuka umum seperti `viewAccounts()`, `addAccountMenu()`, dan lain-lain, tanpa harus mengetahui detail implementasinya.

10. **Polymorphism:**
   - Polymorphism adalah konsep di mana suatu objek dapat memiliki banyak bentuk. Dalam kode ini, polimorfisme terjadi saat kita memanggil metode `viewAccounts()` atau `addAccountMenu()` dari objek `User`, yang dapat merujuk baik pada objek `User` biasa maupun `PremiumUser`, bergantung pada konteks pemanggilannya. Ini terjadi karena pewarisan dan overriding yang dilakukan di kelas turunan.

