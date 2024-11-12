#include <iostream>
#include <limits>
#include <string>

using namespace std;

double calculateSPI(int n, int credits[], double grades[]) {
    double totalWeightedGradePoints = 0.0;
    int totalCredits = 0;

    for (int i = 0; i < n; ++i) {
        if (credits[i] <= 0 || grades[i] < 0) {
            cout << "Invalid input: credits must be positive and grades must be non-negative." << endl;
            return -1;
        }
        totalWeightedGradePoints += credits[i] * grades[i];
        totalCredits += credits[i];
    }

    if (totalCredits == 0) {
        cout << "Invalid calculation: total credits cannot be zero." << endl;
        return -1;
    }

    return totalWeightedGradePoints / totalCredits;
}

int main() {
    string command;
        cout << "Enter 'exit' to quit or press Enter to continue: ";
        getline(cin, command);

    while (true) {
        if (command == "exit") {
            break;
        }

        int n;
        cout << "Enter the number of subjects: ";
        cin >> n;

        if (n <= 0) {
            cout << "Invalid input: number of subjects must be positive." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            continue;
        }

        int credits[n];
        double grades[n];

        cout << "Enter the credits for each subject: ";
        for (int i = 0; i < n; ++i) {
            cin >> credits[i];
        }

        cout << "Enter the grades for each subject: ";
        for (int i = 0; i < n; ++i) {
            cin >> grades[i];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        double spi = calculateSPI(n, credits, grades);

        if (spi != -1) {
            cout << "The SPI is: " << spi << endl;
        } else {
            cout << "Error in calculating SPI due to invalid input." << endl;
        }
    }

    return 0;
}
