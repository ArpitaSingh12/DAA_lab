#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

double find_cpi(int n, double spi[]) {
    if (n == 0) {
        return 0;
    }

    double sum_spi = 0.0;

    for (int i = 0; i < n; ++i) {
        sum_spi += spi[i];
    }

    double cpi = sum_spi / n;

    return cpi;
}

int main() {
     string command;
        cout << "Enter 'start' to input SPI values or 'exit' to quit: ";
        cin >> command;
    while (true) {

        if (command == "exit") {
            break;
        } else if (command != "start") {
            cout << "Invalid command. Please enter 'start' or 'exit'." << endl;
            continue;
        }

        int n;
        cout << "Enter the number of semesters: ";
        cin >> n;

        if (n <= 0) {
            cout << "Number of semesters must be a positive integer." << endl;
            continue;
        }

        double spi[n];
        cout << "Enter the SPI values: ";
        for (int i = 0; i < n; ++i) {
            cin >> spi[i];
        }

        double cpi = find_cpi(n, spi);
        cout << fixed << setprecision(2) << "CPI = " << cpi << endl;
    }

    cout << "Exiting the program." << endl;
    return 0;
}
