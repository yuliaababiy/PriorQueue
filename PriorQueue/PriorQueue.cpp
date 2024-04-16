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

    // Додавання клієнта в чергу
    void enqueue(const string& name, CustomerType type) {
        if (size == capacity) {
            cerr << "Queue is full\n";
            return;
        }

        Customer customer(name, type);
        queue[size++] = customer;
        // Додаткова логіка може бути додана тут для обробки пріоритетів
    }

    // Видалення та повернення першого клієнта з черги
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

    // Перевірка, чи черга порожня
    bool isEmpty() const {
        return size == 0;
    }
};

int main() {
    DentistQueue dentistQueue(10); // Створення черги для магазину з максимальним розміром 10

    // Додавання клієнтів до черги
    dentistQueue.enqueue("Nazar", CustomerType::DOESNTHURTS);
    dentistQueue.enqueue("Kate", CustomerType::HURTS);
    dentistQueue.enqueue("Oleh", CustomerType::DOESNTHURTS);

    // Обробка черги та обслуговування клієнтів
    while (!dentistQueue.isEmpty()) {
        Customer customer = dentistQueue.dequeue();
        cout << "Serving customer: " << customer.name << endl;
    }

    return 0;
}
