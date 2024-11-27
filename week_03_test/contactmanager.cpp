#include <iostream>
#include <map>
#include <string>
#include <limits>
#include <thread>

using namespace std;

struct Contact
{

    string name;
    string phoneNumber;
    string email;

public:
    // parameter constructor
    Contact(string name, string phoneNumber, string email) : name(name), phoneNumber(phoneNumber), email(email) {}

    // default constructor(if needed)
    Contact()
    {
    }

    // setters
    void setPhoneNumber(string newPhone)
    {
        phoneNumber = newPhone;
    }
    void setEmail(string newEmail)
    {
        email = newEmail;
    }

    void setName(string newName)
    {
        name = newName;
    }

    //  getters
    string getName()
    {
        return name;
    }
    string getPhoneNumber()
    {
        return phoneNumber;
    }
    string getEmail()
    {
        return email;
    }
};

class ContactManager
{
private:
    map<string, Contact> contacts;  
            // Keyed by phone number(store contact by phonenumber)

public:
    void addContact(const Contact &contact)
    {
        contacts.insert({contact.phoneNumber, contact}); // key-phoneNumber, value-contact
        // or not good practice
        // contacts[contact.phoneNumber] = contact;
        cout << "Added contact:" << contact.name << "- " << contact.phoneNumber << endl;
    }

    // update contact
    void updateContact(const string &phoneNumber, const Contact &updatedContact)
    {
        auto it = contacts.find(phoneNumber); // it will itartor if found
        if (it != contacts.end())             // means we have found the contact
        {
            it->second = updatedContact; // update contact
        }
        else
        {
            cout << "Contact not found" << endl;
        }
    }

    // delete by phoneNumber
    void deleteContact(const string &phoneNumber)
    {
        auto it = contacts.find(phoneNumber);
        if (it != contacts.end())
        {
            Contact contact = it->second; // backup contact
            contacts.erase(it);           // delteting contact by phonenUmber
            cout << "Contact deleted:" << contact.name << "- " << contact.phoneNumber << endl;
        }
        else
        {
            cout << "Contact not found" << endl;
        }
    }

    // search by phoneNumber and return Contact
    Contact searchContact(const string &phoneNumber) const
    {
        auto it = contacts.find(phoneNumber); // find contact
        if (it != contacts.end())             // cheks if number present or not
        {
            return it->second; // will return contact
        }
        else
        {
            cout << "Contact not found" << endl;
            return Contact{}; // empty contact
        }
    }

    // display contacts
    void displayContacts() const
    {
        if (contacts.empty())
        {
            cout << "Contacts list is empty" << endl;
            return;
        }

        // Contacts Management: "Added contact: John Doe - 555-1234", "Contact deleted: Jane Smith - 555-5678"
        for (auto it : contacts) // we will get pair(key,value- phoneNumber, contact)
        {
            Contact contact = it.second;
            cout << "Contact:[" << contact.name << ", " << contact.phoneNumber << ", ";
            if (!contact.email.empty()) // bcz emial is optinal
            {
                cout << contact.email << "]" << endl;
            }
        }
    }
};

int main()
{
    // Contactmanager
    ContactManager manager;

    string name;
    string phoneNumber;
    string email;

    int contactNumber;
    cout << "How many contacts you want to store, please enter a integer value" << endl;
    cin >> contactNumber;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    for (int i = 0; i < contactNumber; i++)
    {
        cout << "Enter " << i + 1 << " contact information:" << endl;
        cout << "\n";

        cout << "Enter Name:" << endl;
        getline(cin, name); // use getLine() so that spcae can be read also
        cout << "Enter PhoneNumber:" << endl;
        getline(cin, phoneNumber);
        cout << "Enter Email:" << endl;
        getline(cin, email);

        Contact contact(name, phoneNumber, email);
        manager.addContact(contact);
        cout << "\n";
    }

    cout << "Recent contacts are:" << endl;
    manager.displayContacts();
    cout << "\n";

    cout << "Searching contact '22222222' " << endl;
    this_thread::sleep_for(chrono::seconds(4)); // sleeping for 4 second
    Contact contact = manager.searchContact("22222222");

    cout << "Updating contact '22222222' to '33333333'" << endl;
    contact.setPhoneNumber("33333333");         // set new contact
                                                // update phone number
                                                // now call updateContact with new contact
    this_thread::sleep_for(chrono::seconds(4)); // sleeping for 4 second
    manager.updateContact("22222222", contact);

    cout << "After updation:" << endl;
    manager.displayContacts();

    return 0;
}