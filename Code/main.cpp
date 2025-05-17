/*
========================================================================================================================================
   => Project Name: Huffman Coding Algorithm Implementation.
   => Project Description:
   This is a C++ implementation of the Huffman Coding Algorithm, a well-known algorithm used for lossless data compression, this project
   demonstrates how to compress and decompress text efficiently using a binary tree structure, the goal of this project is to understand
   how Huffman Coding works and to implement it in C++.
   => Made By:
   1) Ali Mohamed Eissa Aboelmagd.
   2) Addulrahman Ahmed Mohamed Rashad.
   3) Abdulaziz Ahmed Abdulaziz.
   => Students at Benha Faculty of Engineering, Communications & Computer Engineering Department.
========================================================================================================================================
*/


#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>  // For Just Display, Not More.

using namespace std;


// ==================================================
// The Structure of The Node.
struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};
// ==================================================



// ==================================================
// Compare to Determine The Priority of Nodes.
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};
// ==================================================


// ==================================================
// Map: A simple Structure Used to Store Letters and Their Frequencies or Codes.
struct CharMap {
    char ch;
    string code;
    int ch_freq = 0;
};
// ==================================================



// ==================================================
// Class for Map.
class CustomMap {
    CharMap data[256]; // Max Number of Letters.
    int size;
public:
    CustomMap() {
        size = 0;
    }

    void insert(char ch, string code) {
        for (int i = 0; i < size; ++i) {
            if (data[i].ch == ch) {
                data[i].code = code;
                return;
            }
        }
        data[size++] = {ch, code , 0};
    }

    string get_code_of_char(char ch) {
        for (int i = 0; i < size; ++i) {
            if (data[i].ch == ch)
                return data[i].code;
        }
        return "";
    }

    bool exists(char ch) {
        for (int i = 0; i < size; ++i)
            if (data[i].ch == ch) return true;
        return false;
    }

    void incrementFreq(char ch) {
    for (int i = 0; i < size; ++i) {
        if (data[i].ch == ch) {
            data[i].ch_freq += 1;
            return;
        }
    }
    data[size++] = {ch, "", 1};
    }

    int getFreq(char ch) {
    for (int i = 0; i < size; ++i)
        if (data[i].ch == ch)
            return data[i].ch_freq;
    return 0;
    }


    int getSize() {
        return size;
    }

    CharMap* getData() {
        return data;
    }
};
// ==================================================



// ==================================================
// Generate Codes for Each Letter.
void generateCodes(Node* root, string code, CustomMap& huffmanCode) {
    if (!root)
        return;
    if (!root->left && !root->right) {
        huffmanCode.insert(root->ch, code);
    }
    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}
// ==================================================




// ==================================================
// Function for Decoding.
string decode(Node* root, string encodedStr) {
    string result = "";
    Node* curr = root;
    for (char bit : encodedStr) {
        if (bit == '0') curr = curr->left;
        else curr = curr->right;

        if (!curr->left && !curr->right) {
            result += curr->ch;
            curr = root;
        }
    }
    return result;
}
// ==================================================


// ==================================================
// Function for Display Each Character, Its Code and Its Frequency.
void printCharCodeFreqFromTree(Node* root, CustomMap& codeMap) {
    if (!root) return;

    if (!root->left && !root->right) {
        string code = codeMap.get_code_of_char(root->ch);

        // Print formatted output
        cout << left << setw(10) << root->ch
             << setw(20) << code
             << setw(10) << root->freq << endl;
        return;
    }

    printCharCodeFreqFromTree(root->left, codeMap);
    printCharCodeFreqFromTree(root->right, codeMap);
}
// ==================================================



// ==================================================
// Main Function.
int main() {
    string text="" ;

// ==================================================
// The File Contains The Text to Be Encoded.

    string In_filePath = "Original_Text.txt";

// ==================================================


// ==================================================
// Open the file Using ifstream.

    ifstream In_file(In_filePath);

// ==================================================


// ==================================================
// confirm file opening
    if (!In_file.is_open()) {

        cout << "Failed to open file: " << In_filePath << endl;
        return 1;
    }
// ==================================================



// ==================================================
// Read The File Line By Line Into a String and Store in Text Variable.
    string line;
    while (getline(In_file, line)) {
            text+=line;
    }
// ==================================================


// ==================================================
// Close the Input file.
    In_file.close();
// ==================================================



// ==================================================
// Calculate Frequences.
    CustomMap freqMap;
    for (char ch : text) {
        freqMap.incrementFreq(ch);
    }
// ==================================================


// ==================================================
// Bulding The Tree.
    priority_queue<Node*, vector<Node*>, Compare> pq;
    CharMap* freqs = freqMap.getData();
    for (int i = 0; i < freqMap.getSize(); ++i) {
    pq.push(new Node(freqs[i].ch, freqs[i].ch_freq));
    }
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    Node* root = pq.top();
// ==================================================



// ==================================================
// Generate Codes.
    CustomMap huffmanCode;
    generateCodes(root, "", huffmanCode);
// ==================================================


// ==================================================
// Printing The Codes for Each letter.
    cout << "Huffman Codes";
    cout << "\n===================================================\n";
    cout << left << setw(10) << "Char"
         << setw(20) << "Code"
         << setw(10) << "Freq" << endl;
    cout << "---------------------------------------------------\n";

    printCharCodeFreqFromTree(root, huffmanCode);
// ==================================================


// ==================================================
    cout<<"===================================================\n";

    cout<<"The Size of Text Before Compression: "<<text.length()*8<<" Bits"<<endl;

    cout<<"===================================================\n";
// ==================================================
// Stored The Encoded String to Print it.
    string encoded = "";
    for (char ch : text) {
        encoded += huffmanCode.get_code_of_char(ch);
    }
// ==================================================



// ==================================================
// Preparing a File to Store The Encoded Data.
// ==================================================
// Specify the File Path.
    string Out_filePath = "Binary_Encoeded_File.txt";
// ==================================================


// ==================================================
// Create an ofstream object (opens file for writing).
    ofstream Out_file(Out_filePath);
// ==================================================


// ==================================================
// Check if the file opened successfully.
    if (!Out_file.is_open()) {
        cout << "Failed to open file for writing: " << Out_filePath << endl;
        return 1;
    }
// ==================================================


// ==================================================
// Stores the Data into Output File.
    for (char ch : encoded) {
        Out_file << ch;
    }
// ==================================================



// ==================================================
    // Close the Out file.
    Out_file.close();
// ==================================================



// ==================================================
// Printing Stage.
// ==================================================
// Printing The Encoded Pattern and Display Its Size After Compression.
    cout << "\nEncoded string:\n" << encoded << endl << endl;

    cout<<"===================================================\n";

    cout<<"The Size of Text After Compression: "<<encoded.length()<<" Bits"<<endl;

    cout<<"===================================================\n";
// ==================================================



// ==================================================
// Diplay The Decoded Text.
    string decoded = decode(root, encoded);
    cout << "\nDecoded string:\n" << decoded << endl;
// ==================================================

// ==================================================
// End The Program.
    return 0;
// ==================================================
}
