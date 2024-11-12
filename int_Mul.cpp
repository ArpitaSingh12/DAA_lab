#include <iostream>
#include <cmath>
#include <string>
#include <limits>
using namespace std;

long long karatsubaMultiply(long long x, long long y) {
    // Base case for recursion
    if (x < 10 || y < 10) {
        return x * y;
    }

    // Calculate the size of the numbers
    int n = max(to_string(x).length(), to_string(y).length());
    int half = n / 2;

    // Calculate powers of 10
    long long power = 1;
    for (int i = 0; i < half; ++i) {
        power *= 10; // Calculate 10^half
    }

    // Split the digits
    long long a = x / power;      // Left half of x
    long long b = x % power;      // Right half of x
    long long c = y / power;      // Left half of y
    long long d = y % power;      // Right half of y

    // 3 recursive calls
    long long ac = karatsubaMultiply(a, c);          // a * c
    long long bd = karatsubaMultiply(b, d);          // b * d
    long long ad_plus_bc = karatsubaMultiply(a + b, c + d) - ac - bd; // (a + b)(c + d) - ac - bd

    // Combine the results using integers
    return ac * power * power + ad_plus_bc * power + bd;
}

int main() {
    long long x, y;

    for (int i = 0; i < 10; ++i) {
        while (true) {
            cout << "Enter pair " << (i + 1) << " for Karatsuba multiplication (two integers): ";
            cin >> x >> y;

            // Check for valid input
            if (cin.fail()) {
                cin.clear(); // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input. Please enter two integers." << endl;
            } else {
                break; // Valid input, exit the loop
            }
        }

        long long result = karatsubaMultiply(x, y);
        cout << "Karatsuba Multiplication of " << x << " and " << y << ": " << result << endl;
    }

    return 0;
}
