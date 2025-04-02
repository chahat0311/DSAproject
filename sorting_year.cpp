#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

struct Acquisition {
    std::string company;
    int year;
};

// Function to parse the CSV file
std::vector<Acquisition> parseCSV(const std::string& filename) {
    std::vector<Acquisition> acquisitions;
    std::ifstream file(filename);
    std::string line;

    // Skip the header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string company, yearStr;
        std::getline(ss, company, ',');
        std::getline(ss, yearStr, ',');

        Acquisition acquisition = {company, std::stoi(yearStr)};
        acquisitions.push_back(acquisition);
    }

    return acquisitions;
}

// Merge function for merge sort
void merge(std::vector<Acquisition>& data, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Acquisition> leftArr(n1);
    std::vector<Acquisition> rightArr(n2);

    for (int i = 0; i < n1; ++i)
        leftArr[i] = data[left + i];
    for (int i = 0; i < n2; ++i)
        rightArr[i] = data[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].year <= rightArr[j].year) {
            data[k] = leftArr[i];
            ++i;
        } else {
            data[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        data[k] = leftArr[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        data[k] = rightArr[j];
        ++j;
        ++k;
    }
}

// Merge sort function
void mergeSort(std::vector<Acquisition>& data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(data, left, mid);
        mergeSort(data, mid + 1, right);
        merge(data, left, mid, right);
    }
}

// Function to print the sorted data
void printAcquisitions(const std::vector<Acquisition>& acquisitions) {
    for (const auto& acquisition : acquisitions) {
        std::cout << acquisition.company << ", " << acquisition.year << std::endl;
    }
}

int main() {
    std::string filename = "acquisitions.csv";
    std::vector<Acquisition> acquisitions = parseCSV(filename);

    mergeSort(acquisitions, 0, acquisitions.size() - 1);

    std::cout << "Sorted Acquisitions by Year:" << std::endl;
    printAcquisitions(acquisitions);

    return 0;
}