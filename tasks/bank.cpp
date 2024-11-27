#include <iostream>
using namespace std;

// bank class
class BankAccount
{
private:
    string name;
    int accountNumber;
    float balance = 0.0;

    // constructor
public:
    BankAccount(string name, int accountNumber)
    {
        this->name = name;
        this->accountNumber = accountNumber;
    }
    // setter and getters
public:
    void setName(string n)
    {
        name = n;
    }
    string getName()
    {
        return name;
    }

    void setAccountNumber(int number)
    {
        accountNumber = number;
    }
    int getAccountNumber()
    {
        return accountNumber;
    }

    void setbalance(float b)
    {
        balance = b;
    }
    float getbalance()
    {
        return balance;
    }

    // depoiste money
    void deposit(int amount)
    {
        balance = balance + amount;
        cout << "Amount deposited successfully" << endl;
    }

    // Withdraw money
    void withdraw(int amount)
    {
        if (amount < balance)
        {
            balance = balance - amount;
            cout << "Amount withdrawl successfully:" << endl;
        }
        else
        {
            cout << "Sorry, No sufficent amount" << endl;
        }
    }

    void display()
    {
        cout << "Account holder:" << name << endl;
        cout << "Cureent balance is:" << balance << endl;
    }
};

// main
int main()
{

    // account creation
    BankAccount ac1("Rahman", 1001);

    // deopsite;
    int amount1;
    int amount2;
    // display account number and name
    ac1.display();
    while(true){
    cout << "option\n 1.Deposite   2.Withdraw" << endl;
    int option;
    cin >> option;
    switch (option)
    {
    case 1: // deposite
        cout << "Enter amount to be deposited" << endl;
        cin >> amount1;
        ac1.deposit(amount1);
        break;

    case 2: // withdrwal
        cout << "Enter amount to be withrdwal" << endl;
        cin >> amount2;
        ac1.withdraw(amount2);
        break;
    default:
        cout << "please enter right option:" << endl;
        break;
    }

    // display balance
    ac1.display();
    }
    return 0;
}