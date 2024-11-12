#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <tuple>
#include <limits>
#include <iomanip>

using namespace std;

class SalaryCalculator {
private:
    double basicSalary;
    double bonus;
    static constexpr double conveyanceAllowance = 1500.0;
    static constexpr double hraPercentage = 50.0;
    static constexpr double daPercentage = 10.0;
    static constexpr double epfPercentage = 12.0;
    static constexpr double estPercentage = 0.75;

public:
    SalaryCalculator(double basic, double bon)
        : basicSalary(basic), bonus(bon) {}

    double calculateHRA() const {
        return (hraPercentage / 100) * basicSalary;
    }

    double calculateDA() const {
        return (daPercentage / 100) * basicSalary;
    }

    double calculateEPF() const {
        return (epfPercentage / 100) * basicSalary;
    }

    double calculateEST() const {
        return (estPercentage / 100) * basicSalary;
    }

    double calculateGrossSalary() const {
        return basicSalary + calculateHRA() + conveyanceAllowance + calculateDA() + bonus;
    }

    double calculateNetSalary(double taxPercentage) const {
        double grossSalary = calculateGrossSalary();
        double totalDeductions = calculateEPF() + calculateEST();
        double netSalaryBeforeTax = grossSalary - totalDeductions;
        double taxAmount = (netSalaryBeforeTax * taxPercentage) / 100;
        return netSalaryBeforeTax - taxAmount;
    }

    static void findMinMax(const vector<double>& arr, int left, int right, double &minSalary, double &maxSalary) {
        if (left > right) {
            throw invalid_argument("Invalid range for min/max computation.");
        }
        if (left == right) {
            minSalary = maxSalary = arr[left];
        } else if (right == left + 1) {
            minSalary = min(arr[left], arr[right]);
            maxSalary = max(arr[left], arr[right]);
        } else {
            int mid = (left + right) / 2;
            double minLeft, maxLeft, minRight, maxRight;
            findMinMax(arr, left, mid, minLeft, maxLeft);
            findMinMax(arr, mid + 1, right, minRight, maxRight);
            minSalary = min(minLeft, minRight);
            maxSalary = max(maxLeft, maxRight);
        }
    }
};

void readDataFromCSV(const string& filename, vector<tuple<double, double, double>>& data) {
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        getline(file, line); // Skip header row if present
        while (getline(file, line)) {
            stringstream ss(line);
            double basicSalary, bonus, taxPercentage;
            char comma;

            if (ss >> basicSalary >> comma >> bonus >> comma >> taxPercentage) {
                data.emplace_back(basicSalary, bonus, taxPercentage);
            } else {
                cerr << "Error parsing line: " << line << endl;
            }
        }
        file.close();
    } else {
        cerr << "Unable to open file for reading." << endl;
    }
}

void writeSalariesToCSV(const string& filename, const vector<double>& salaries) {
    ofstream file(filename);
    if (file.is_open()) {
        for (size_t i = 0; i < salaries.size(); ++i) {
            file << fixed << setprecision(2) << salaries[i];
            if (i < salaries.size() - 1) file << ",";
        }
        file.close();
    } else {
        cerr << "Unable to open file for writing." << endl;
    }
}

int main() {
    vector<tuple<double, double, double>> data;
    vector<double> netSalaries;
    vector<double> grossSalaries;

    // Read data from CSV
    readDataFromCSV("salaries_data.csv", data);

    // Calculate salaries
    for (const auto& record : data) {
        double basicSalary = get<0>(record);
        double bonus = get<1>(record);
        double taxPercentage = get<2>(record);

        SalaryCalculator salaryCalc(basicSalary, bonus);
        double grossSalary = salaryCalc.calculateGrossSalary();
        double netSalary = salaryCalc.calculateNetSalary(taxPercentage);
        netSalaries.push_back(netSalary);
        grossSalaries.push_back(grossSalary);
    }

    // Find min and max net salaries
    double minNetSalary = numeric_limits<double>::max();
    double maxNetSalary = numeric_limits<double>::lowest();

    if (!netSalaries.empty()) {
        try {
            SalaryCalculator::findMinMax(netSalaries, 0, netSalaries.size() - 1, minNetSalary, maxNetSalary);
        } catch (const exception& e) {
            cerr << "Exception: " << e.what() << endl;
            return 1;
        }

        // Display salaries for the first 10 employees
        cout << "Gross and Net Salaries for the first 10 employees:" << endl;
        for (size_t i = 0; i < min(static_cast<size_t>(10), netSalaries.size()); ++i) {
            cout << "Employee " << (i + 1) << " - Gross Salary: " << fixed << setprecision(2) << grossSalaries[i]
                 << ", Net Salary: " << fixed << setprecision(2) << netSalaries[i] << endl;
        }

        // Display minimum and maximum net salaries
        cout << "Minimum net salary: " << fixed << setprecision(2) << minNetSalary << endl;
        cout << "Maximum net salary: " << fixed << setprecision(2) << maxNetSalary << endl;
    } else {
        cout << "No salaries available to compute." << endl;
    }

    // Write net salaries to CSV
    writeSalariesToCSV("net_salaries.csv", netSalaries);

    return 0;
}




