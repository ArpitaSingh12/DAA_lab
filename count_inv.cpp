#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <map>

using namespace std;

// Function prototypes
int mergeSortAndCount(vector<int>& arr, int left, int right);
int countInversionsInDigits(int number);
int mergeAndCount(vector<int>& arr, int left, int mid, int right);

// Function to count inversions in the digits of a single number
int countInversionsInDigits(int number) {
    string numStr = to_string(number);
    int n = numStr.size();
    vector<int> digits(n);

    for (int i = 0; i < n; ++i) {
        digits[i] = numStr[i] - '0';  // Convert char to int
    }

    // Count inversions using a modified merge sort
    return mergeSortAndCount(digits, 0, n - 1);
}

// Function to merge two halves and count inversions
int mergeAndCount(vector<int>& arr, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = 0;
    vector<int> temp(right - left + 1);
    int inv_count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);  // Count inversions
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (int p = left; p <= right; p++) {
        arr[p] = temp[p - left];
    }

    return inv_count;
}

// Function to count inversions using merge sort
int mergeSortAndCount(vector<int>& arr, int left, int right) {
    int inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        inv_count += mergeSortAndCount(arr, left, mid);
        inv_count += mergeSortAndCount(arr, mid + 1, right);
        inv_count += mergeAndCount(arr, left, mid, right);
    }
    return inv_count;
}

bool isValidCourseCode(int courseCode) {
    return courseCode >= 100000 && courseCode <= 999999; // Check if it's a 6-digit number
}

int main() {
    vector<int> courseCodes;
    ifstream inFile("course_codes.csv");

    // Check if the file is open
    if (!inFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    getline(inFile, line); // Skip header
    while (getline(inFile, line)) {
        stringstream ss(line);
        string studentId;
        int courseCode;
        getline(ss, studentId, ','); // Read student ID
        ss >> courseCode; // Read course code as integer

        if (isValidCourseCode(courseCode)) {
            courseCodes.push_back(courseCode);
        }
    }
    inFile.close();
    // Map to count number of students by inversion counts
    map<int, int> inversionCountMap;
    vector<pair<int, int>> results; // To store course codes and their inversion counts
    // Process all course codes and count inversions
    for (int code : courseCodes) {
        int inversionCount = countInversionsInDigits(code);
        inversionCountMap[inversionCount]++;
        results.push_back({code, inversionCount});
    }
    // Write results to CSV
    ofstream outFile("inversion_counts.csv");
    outFile << "Course Code,Inversion Count\n"; // Write CSV header
    for (const auto& result : results) {
        outFile << result.first << "," << result.second << "\n";
    }
    outFile.close();

    // Randomly select 10 course codes and print their inversion counts
    random_device rd;
    mt19937 eng(rd());
    shuffle(courseCodes.begin(), courseCodes.end(), eng);

    cout << "Inversion counts for 10 randomly selected course codes:\n";
    for (int i = 0; i < 10 && i < courseCodes.size(); ++i) {
        int selectedCode = courseCodes[i];
        int inversionCount = countInversionsInDigits(selectedCode);
        cout << "Course Code: " << selectedCode
             << " | Inversion Count: " << inversionCount << endl;
    }

    // Output the count of students with 0, 1, 2, and 3 inversions
    cout << "\nNumber of students with:\n";
    for (int i = 0; i <= 3; ++i) {
        cout << i << " inversion(s): " << inversionCountMap[i] << endl;
    }
   // Write summary to CSV
    ofstream summaryFile("inversion_summary.csv");
    summaryFile << "Inversion Count,Number of Students\n"; // Write summary header
    for (int i = 0; i <= 3; ++i) {
        summaryFile << i << "," << inversionCountMap[i] << "\n";
    }
    summaryFile.close();
    return 0;
}
