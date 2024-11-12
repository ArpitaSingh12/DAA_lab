#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std; // Add this line to use the standard namespace

struct Item {
    int id;
    double value;
    double weight;
    double shelfLife;
    double ratio;
};

// Comparator function to sort items by their value-to-weight ratio,
// and by shelf life if the ratios are the same
bool compare(Item a, Item b) {
    if (a.ratio == b.ratio) {
        return a.shelfLife < b.shelfLife; // Prioritize lesser shelf life
    }
    return a.ratio > b.ratio; // Sort in descending order
}

double fractionalKnapsack(vector<Item>& items, double capacity) {
    double totalValue = 0.0;

    // Sort items by their value-to-weight ratio
    sort(items.begin(), items.end(), compare);

    // Print the value, weight, ratio, and shelf life for the first 10 items
    cout << "Sorted Items (ID, Value, Weight, Shelf Life, Ratio):\n";
    cout << "-------------------------------------------------------\n";
    cout << "ID\tValue\tWeight\tShelf Life\tRatio\n";
    for (size_t i = 0; i < min(items.size(), size_t(10)); ++i) {
        cout << items[i].id << "\t"
             << items[i].value << "\t"
             << items[i].weight << "\t"
             << items[i].shelfLife << "\t\t"
             << items[i].ratio << "\n";
    }
    cout << "-------------------------------------------------------\n";

    for (const auto& item : items) {
        if (capacity <= 0) {
            break; // If the capacity is full, stop
        }

        if (item.weight <= capacity) {
            // If the item can fit entirely
            totalValue += item.value;
            capacity -= item.weight;
        } else {
            // If only a fraction can fit
            totalValue += item.value * (capacity / item.weight);
            capacity = 0; // Knapsack is now full
        }
    }

    return totalValue;
}

int main() {
    vector<Item> items;
    ifstream csvFile("items.csv");

    if (!csvFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    // Skip the header line
    getline(csvFile, line);

    // Read items from the CSV file
    while (getline(csvFile, line)) {
        stringstream ss(line);
        Item item;
        string temp;

        getline(ss, temp, ','); // Read ID
        item.id = stoi(temp);
        getline(ss, temp, ','); // Read Value
        item.value = stod(temp);
        getline(ss, temp, ','); // Read Weight
        item.weight = stod(temp);
        getline(ss, temp, ','); // Read Shelf Life
        item.shelfLife = stod(temp);
        item.ratio = item.value / item.weight; // Calculate value-to-weight ratio

        items.push_back(item);
    }

    csvFile.close(); // Close the file

    double capacity = 200; // Capacity of the knapsack
    double maxValue = fractionalKnapsack(items, capacity);

    cout << "Maximum value in the knapsack: " << maxValue << endl;

    return 0;
}
