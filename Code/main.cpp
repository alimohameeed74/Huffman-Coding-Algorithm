#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

// هيكل العقدة
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

// مقارنة لتحديد أولوية العقد
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};
/*struct Compare {
    bool operator()(Node* a, Node* b) {
        if (a->freq == b->freq)
            return a->ch > b->ch; // عشان الترتيب يكون ثابت للحروف المتساوية
        return a->freq > b->freq;
    }
};*/


// هيكل بيانات بسيط يحاكي unordered_map لتخزين الحروف وتردداتها أو رموزها
struct CharMap {
    char ch;
    string code;
};

class CustomMap {
    CharMap data[256]; // نفترض أن الحروف لا تتعدى 256
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
        data[size++] = {ch, code};
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
                int freq = stoi(data[i].code);
                data[i].code = to_string(freq + 1);
                return;
            }
        }
        data[size++] = {ch, "1"};
    }

    int getFreq(char ch) {
        for (int i = 0; i < size; ++i)
            if (data[i].ch == ch)
                return stoi(data[i].code);
        return 0;
    }

    int getSize() {
        return size;
    }

    CharMap* getData() {
        return data;
    }
};

// دالة توليد الرموز
void generateCodes(Node* root, string code, CustomMap& huffmanCode) {
    if (!root)
        return;
    if (!root->left && !root->right) {
        huffmanCode.insert(root->ch, code);
    }
    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// دالة فك التشفير
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

// الدالة الرئيسية
int main() {
    string text = "ALIMOHAMED";

    // حساب الترددات
    CustomMap freqMap;
    for (char ch : text) {
        if (ch == ' ') continue;
        freqMap.incrementFreq(ch);
    }

    // بناء الشجرة
    priority_queue<Node*, vector<Node*>, Compare> pq;
    CharMap* freqs = freqMap.getData();
    for (int i = 0; i < freqMap.getSize(); ++i) {
        pq.push(new Node(freqs[i].ch, stoi(freqs[i].code)));   // بخزن العنصر والتكرار بتاعه في الكيو
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

    // توليد الرموز
    CustomMap huffmanCode;
    generateCodes(root, "", huffmanCode);

    // طباعة الرموز
    cout << "Huffman Codes:\n";
    for (int i = 0; i < huffmanCode.getSize(); ++i) {
        cout << huffmanCode.getData()[i].ch << ": " << huffmanCode.getData()[i].code << endl;
    }

    // التشفير
    string encoded = "";
    for (char ch : text) {
        if (ch == ' ') continue;
        encoded += huffmanCode.get_code_of_char(ch);
    }
    cout << "\nEncoded string:\n" << encoded << endl;

    // فك التشفير
    string decoded = decode(root, encoded);
    cout << "\nDecoded string:\n" << decoded << endl;

    return 0;
}
