#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to perform Matrix Chain Multiplication
int matrixChainOrder(const vector<int>& p, int n, vector<vector<int>>& m, vector<vector<int>>& s) {
    // m[i][j] will store the minimum number of scalar multiplications required to multiply matrices from i to j
    // s[i][j] will store the index k at which the optimal split occurs
    for (int len = 2; len <= n; ++len) { // len is the chain length
        for (int i = 0; i <= n - len; ++i) { // i is the starting point of the chain
            int j = i + len - 1; // j is the endpoint of the chain
            m[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                // Calculate the cost for splitting at k
                int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    return m[0][n - 1];
}

// Function to print the optimal parenthesization of the matrix chain multiplication
void printOptimalParenthesis(const vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "M" << i + 1; // print matrix index (1-based)
    } else {
        cout << "(";
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j] + 1, j);
        cout << ")";
    }
}

int main() {
    // Matrix dimensions (based on the 6 matrices described above)
    vector<int> p = {10, 5, 30, 15, 20, 25, 5}; // Dimension array for the matrices

    int n = p.size() - 1; // Number of matrices is p.size() - 1

    // Create tables for storing minimum cost and split index
    vector<vector<int>> m(n, vector<int>(n, 0)); // m[i][j] is the minimum number of multiplications
    vector<vector<int>> s(n, vector<int>(n, 0)); // s[i][j] is the index where the optimal split occurs

    // Call the matrix chain order function
    int minCost = matrixChainOrder(p, n, m, s);

    cout << "Minimum number of multiplications: " << minCost << endl;

    // Print the optimal parenthesization
    cout << "Optimal Parenthesization: ";
    printOptimalParenthesis(s, 0, n - 1);
    cout << endl;

    return 0;
}
