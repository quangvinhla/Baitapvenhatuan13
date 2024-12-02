#include <iostream>
#include <string>

using namespace std;

struct Product {
    string name;
    int quantity;
    double price;
};

struct Node {
    Product* products;
    int productCount;
    Node* next;
};

struct Queue {
    Node* front;
    Node* rear;

    Queue() {
        front = rear = nullptr;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(Product* products, int productCount) {
        Node* newNode = new Node{products, productCount, nullptr};
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    Node* dequeue() {
        if (isEmpty()) return nullptr;
        Node* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        return temp;
    }
};

double calculateTotal(Queue& queue) {
    double total = 0;
    while (!queue.isEmpty()) {
        Node* node = queue.dequeue();
        for (int i = 0; i < node->productCount; ++i) {
            total += node->products[i].price * node->products[i].quantity;
        }
        delete[] node->products;
        delete node;
    }
    return total;
}

int countProductA(Queue& queue, const string& productName) {
    int count = 0;
    while (!queue.isEmpty()) {
        Node* node = queue.dequeue();
        for (int i = 0; i < node->productCount; ++i) {
            if (node->products[i].name == productName) {
                count += node->products[i].quantity;
            }
        }
        delete[] node->products;
        delete node;
    }
    return count;
}

int main() {
    Queue queue;

    Product products1[] = {{"Apple", 2, 10.0}, {"Banana", 3, 5.0}};
    Product products2[] = {{"Apple", 1, 10.0}, {"Orange", 2, 8.0}};

    queue.enqueue(products1, 2);
    queue.enqueue(products2, 2);

    double total = calculateTotal(queue);
    cout << "Total money collected: " << total << endl;

    queue.enqueue(products1, 2);
    queue.enqueue(products2, 2);

    int productACount = countProductA(queue, "Apple");
    cout << "Number of 'Apple' sold: " << productACount << endl;

    return 0;
}