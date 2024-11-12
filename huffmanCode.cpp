#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Node structure for the Huffman tree
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char character, int frequency) : ch(character), freq(frequency), left(nullptr), right(nullptr) {}
};

// Comparator for the priority queue
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Function to generate the Huffman codes
void generateCodes(Node* root, const string& str, unordered_map<char, string>& codes) {
    if (!root) return;
    if (root->left == nullptr && root->right == nullptr) {
        codes[root->ch] = str;
    }
    generateCodes(root->left, str + "0", codes);
    generateCodes(root->right, str + "1", codes);
}

// Function to build the Huffman tree
Node* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create a node for each character and push it to the priority queue
    for (const auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Merge nodes until there's only one node left
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* combined = new Node('\0', left->freq + right->freq);
        combined->left = left;
        combined->right = right;
        pq.push(combined);
    }

    return pq.top(); // Root of the Huffman tree
}

// Function to calculate the original and compressed sizes and the compression ratio
void calculateSizes(const unordered_map<char, int>& freqMap, const unordered_map<char, string>& codes,
                    int& originalSize, int& compressedSize) {
    originalSize = 0;
    compressedSize = 0;

    for (const auto& pair : freqMap) {
        originalSize += pair.second * 8; // Assuming each character is 8 bits
        compressedSize += pair.second * codes.at(pair.first).length();
    }
}

// Function to read frequency map from a specified file
unordered_map<char, int> readFrequencyMap(const string& filename) {
    unordered_map<char, int> freqMap;
    ifstream infile(filename);

    if (!infile.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return freqMap;
    }

    string line;
    while (getline(infile, line)) {
        if (!line.empty()) {
            char ch = line[0];
            size_t colon_pos = line.find(':');
            if (colon_pos != string::npos && colon_pos + 1 < line.size()) {
                string freq_str = line.substr(colon_pos + 1);
                try {
                    int freq = stoi(freq_str);
                    freqMap[ch] = freq;
                } catch (const std::invalid_argument&) {
                    cerr << "Invalid frequency for character '" << ch << "': " << freq_str << "\n";
                }
            }
        }
    }
    return freqMap;
}

// Function to clean up the Huffman tree
void deleteTree(Node* root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

int main() {
    // Specify the full path to your local frequency map file here
    string local_file_path = "C:\\Users\\dines\\Desktop\\freq.txt"; // Update this line with your actual path

    // Read frequency map from file
    unordered_map<char, int> freqMap = readFrequencyMap(local_file_path);

    if (freqMap.empty()) {
        cerr << "Error: Frequency map is empty. Check the file format." << endl;
        return 1;
    }

    // Build the Huffman tree
    Node* root = buildHuffmanTree(freqMap);

    // Generate Huffman codes
    unordered_map<char, string> codes;
    generateCodes(root, "", codes);

    // Output the codes
    cout << "Huffman Codes:\n";
    for (const auto& pair : codes) {
        cout << pair.first << ": " << pair.second << "\n";
    }

    // Calculate original and compressed sizes
    int originalSize, compressedSize;
    calculateSizes(freqMap, codes, originalSize, compressedSize);

    // Output the sizes and compression ratio
    cout << "Original Size: " << originalSize << " bits\n";
    cout << "Compressed Size: " << compressedSize << " bits\n";
    double compressionRatio = compressedSize/static_cast<double>(originalSize);
    cout << "Compression Ratio: " << compressionRatio << "\n";

    // Clean up the Huffman tree
    deleteTree(root);

    return 0;
}
