#include <bits/stdc++.h>
using namespace std;

// Function to find the LCS of two sequences
vector<string> lcs_two_sequences(const vector<string>& seq1, const vector<string>& seq2) {
    int n = seq1.size();
    int m = seq2.size();

    // Create a 2D vector for dynamic programming
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Fill the dp array
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (seq1[i - 1] == seq2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Reconstruct the LCS from the dp array
    vector<string> lcs;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (seq1[i - 1] == seq2[j - 1]) {
            lcs.push_back(seq1[i - 1]);
            --i;
            --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    reverse(lcs.begin(), lcs.end());
    return lcs;
}

// Function to find the longest common sequence across multiple sequences
vector<string> longest_common_sequence(const vector<vector<string>>& sequences) {
    if (sequences.empty()) {
        return {};
    }

    // Start with the LCS of the first sequence
    vector<string> lcs_result = sequences[0];

    // Compute the LCS across all sequences
    for (size_t i = 1; i < sequences.size(); ++i) {
        lcs_result = lcs_two_sequences(lcs_result, sequences[i]);
        if (lcs_result.empty()) {
            break;  // Early stop if there is no common subsequence
        }
    }

    return lcs_result;
}

int main() {
    // Sample data: grades of 20 students, each with 5 grades
    vector<vector<string>> student_grades = {
        {"AA", "AB", "BB", "CC", "FF"},
        {"AB", "BB", "CC", "FF", "GG"},
        {"AA", "AB", "BB", "GG", "CC"},
        {"AB", "BB", "CC", "FF", "GG"},
        {"AB", "BB", "CC", "FF", "AA"},
        {"AB", "BB", "GG", "FF", "CC"},
        {"AA", "AB", "BB", "FF", "GG"},
        {"AB", "BB", "CC", "FF", "CC"},
        {"AB", "BB", "FF", "GG", "AA"},
        {"AA", "AB", "BB", "GG", "FF"},
        {"AB", "BB", "CC", "FF", "GG"},
        {"AA", "AB", "BB", "CC", "GG"},
        {"AB", "BB", "GG", "FF", "CC"},
        {"AA", "AB", "BB", "FF", "GG"},
        {"AB", "BB", "CC", "FF", "GG"},
        {"AA", "AB", "BB", "GG", "CC"},
        {"AB", "BB", "CC", "FF", "GG"},
        {"AA", "AB", "BB", "FF", "GG"},
        {"AB", "BB", "CC", "FF", "GG"}
    };

    // Compute the longest common sequence
    vector<string> lcs_grades = longest_common_sequence(student_grades);

    // Output the result
    cout << "Longest common sequence of grades among students: ";
    for (const string& grade : lcs_grades) {
        cout << grade << " ";
    }
    cout << endl;

    return 0;
}
