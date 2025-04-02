#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Define a Node for Linked List
struct Node {
    string companyName;
    double acquisitionPrice;
    int year;
    Node* next;

    Node(string name, double price, int yr) {
        companyName = name;
        acquisitionPrice = price;
        year = yr;
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
    void insert(string name, double price, int year) {
        Node* newNode = new Node(name, price, year);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    // Merge Sort Helper
    Node* merge(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;
        
        Node* result;
        if (left->acquisitionPrice > right->acquisitionPrice) { // Sorting in descending order
            result = left;
            result->next = merge(left->next, right);
        } else {
            result = right;
            result->next = merge(left, right->next);
        }
        return result;
    }

    // Split list into two halves
    void split(Node* source, Node** front, Node** back) {
        Node* fast = source->next;
        Node* slow = source;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        *front = source;
        *back = slow->next;
        slow->next = nullptr;
    }

    // Merge Sort Function
    void mergeSort(Node** headRef) {
        Node* head = *headRef;
        if (!head || !head->next) return;
        
        Node* left;
        Node* right;
        split(head, &left, &right);
        
        mergeSort(&left);
        mergeSort(&right);
        *headRef = merge(left, right);
    }

    void sort() {
        mergeSort(&head);
    }

    // Print list
    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->companyName << " - $" << temp->acquisitionPrice << " - " << temp->year << endl;
            temp = temp->next;
        }
    }
};

// Function to load CSV into linked list (skips header & handles errors)
void loadCSV(const string& filePath, LinkedList& list) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filePath << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header row
    while (getline(file, line)) {
        stringstream ss(line);
        string name, priceStr, yearStr;
        
        getline(ss, name, ',');
        getline(ss, priceStr, ',');
        getline(ss, yearStr, ',');

        // Remove any extra spaces
        name.erase(name.find_last_not_of(" \n\r\t") + 1);
        priceStr.erase(priceStr.find_last_not_of(" \n\r\t") + 1);
        yearStr.erase(yearStr.find_last_not_of(" \n\r\t") + 1);

        double price = 0;
        int year = 0;

        try {
            if (!priceStr.empty()) price = stod(priceStr);
            if (!yearStr.empty()) year = stoi(yearStr);
        } catch (const invalid_argument &e) {
            cerr << "Warning: Skipping invalid row: " << line << endl;
            continue; // Skip this row
        }

        list.insert(name, price, year);
    }

    file.close();
}

int main() {
    LinkedList acquisitions;

    // Load files into linked list
    loadCSV("/Users/chahatgupta/Desktop/Code/DSA/final/Dataset/Acquisitions.csv", acquisitions);

    // Sort acquisitions by price (descending)
    acquisitions.sort();

    // Print sorted acquisitions
    cout << "Sorted Acquisitions by Price:" << endl;
    acquisitions.print();

    return 0;
}