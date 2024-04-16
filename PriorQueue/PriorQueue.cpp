#include <iostream>
#include <string>

using namespace std;

struct Patient {
    string name;
    int age;
    Patient* next;

    Patient(string n, int a) : name(n), age(a), next(nullptr) {}
};

class PriorityHealthcareQueue {
public:
    Patient* head;

    PriorityHealthcareQueue() : head(nullptr) {}

    ~PriorityHealthcareQueue() {
        while (head != nullptr) {
            Patient* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertPatient(string name, int age) {
        Patient* newPatient = new Patient(name, age);
        if (head == nullptr || head->age < age) { // Higher age, higher priority
            newPatient->next = head;
            head = newPatient;
        }
        else {
            Patient* current = head;
            while (current->next != nullptr && current->next->age >= age) {
                current = current->next;
            }
            newPatient->next = current->next;
            current->next = newPatient;
        }
    }

    string servePatient() {
        if (head == nullptr) {
            cout << "Queue is empty" << endl;
            return "";
        }
        string name = head->name;
        Patient* temp = head;
        head = head->next;
        delete temp;
        return name;
    }

    void displayQueue() {
        Patient* current = head;
        while (current != nullptr) {
            cout << "Patient: " << current->name << ", Age: " << current->age << endl;
            current = current->next;
        }
    }

    // View the oldest patient without removing
    string peekNextPatient() {
        if (head == nullptr) {
            cout << "Queue is empty" << endl;
            return "";
        }
        return head->name;
    }
};

void displayOptions() {
    cout << "\nMenu:\n";
    cout << "1. Add Patient\n";
    cout << "2. Serve Patient\n";
    cout << "3. Display Queue\n";
    cout << "4. Peek Next Patient\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    PriorityHealthcareQueue queue;
    int choice;
    string name;
    int age;

    queue.insertPatient("John Doe", 60);
    queue.insertPatient("Jane Smith", 65);
    queue.insertPatient("Alice Johnson", 58);
    queue.insertPatient("Bob Brown", 70);

    while (true) {
        displayOptions();
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter patient's name: ";
            cin >> ws;  // Clear leading whitespace
            getline(cin, name);
            cout << "Enter patient's age: ";
            cin >> age;
            queue.insertPatient(name, age);
            break;
        case 2:
            name = queue.servePatient();
            if (!name.empty()) {
                cout << name << " has been served." << endl;
            }
            break;
        case 3:
            cout << "Current queue of patients:" << endl;
            queue.displayQueue();
            break;
        case 4:
            name = queue.peekNextPatient();
            if (!name.empty()) {
                cout << "Next patient to be served: " << name << endl;
            }
            break;
        case 5:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
