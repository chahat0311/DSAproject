#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Define a Node for Linked List
struct Node {
    string data;
    Node* next;

    Node(string value) {
        data = value;
        next = nullptr;
    }
};

// Linked List Class
class LinkedList {
public:
    Node* head;

    LinkedList() {
        head = nullptr;
    }

    // Insert at end
    void insert(string value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    // Print list
    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
};

// Function to load CSV into linked list
void loadCSV(const string& filePath, LinkedList& list) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filePath << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        list.insert(line);
    }

    file.close();
}

int main() {
    LinkedList acquiringCompanies, acquiredCompanies, acquisitions, founders;

    // Load files into linked lists
    loadCSV("/Users/chahatgupta/Desktop/Code/DSA/final/Dataset/Acquiring Tech Companies.csv", acquiringCompanies);
    loadCSV("/Users/chahatgupta/Desktop/Code/DSA/final/Dataset/Acquired Tech Companies.csv", acquiredCompanies);
    loadCSV("/Users/chahatgupta/Desktop/Code/DSA/final/Dataset/Acquisitions.csv", acquisitions);
    loadCSV("/Users/chahatgupta/Desktop/Code/DSA/final/Dataset/Founders and Board Members.csv", founders);

    // Print sample data
    cout << "Acquiring Companies:" << endl;
    acquiringCompanies.print();

    return 0;
}
