#include <iostream>
using namespace std;

enum class CustomerType {
    HURTS,
    DOESNTHURTS
};

struct Customer {
    string name;
    CustomerType type;

    Customer(const string& name, CustomerType type) : name(name), type(type) {}
};

class DentistQueue {
private:
    Customer* queue;
    int capacity;
    int size;

public:
    DentistQueue(int capacity) : capacity(capacity), size(0) {
        queue = new Customer[capacity];
    }

    ~DentistQueue() {
        delete[] queue;
    }

    // ��������� �볺��� � �����
    void enqueue(const string& name, CustomerType type) {
        if (size == capacity) {
            cerr << "Queue is full\n";
            return;
        }

        Customer customer(name, type);
        queue[size++] = customer;
        // ��������� ����� ���� ���� ������ ��� ��� ������� ���������
    }

    // ��������� �� ���������� ������� �볺��� � �����
    Customer dequeue() {
        if (size == 0) {
            cerr << "Queue is empty\n";
            return { "", CustomerType::DOESNTHURTS };
        }

        Customer front = queue[0];
        for (int i = 1; i < size; ++i) {
            queue[i - 1] = queue[i];
        }
        size--;
        return front;
    }

    // ��������, �� ����� �������
    bool isEmpty() const {
        return size == 0;
    }
};

int main() {
    DentistQueue dentistQueue(10); // ��������� ����� ��� �������� � ������������ ������� 10

    // ��������� �볺��� �� �����
    dentistQueue.enqueue("Nazar", CustomerType::DOESNTHURTS);
    dentistQueue.enqueue("Kate", CustomerType::HURTS);
    dentistQueue.enqueue("Oleh", CustomerType::DOESNTHURTS);

    // ������� ����� �� �������������� �볺���
    while (!dentistQueue.isEmpty()) {
        Customer customer = dentistQueue.dequeue();
        cout << "Serving customer: " << customer.name << endl;
    }

    return 0;
}
