#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    char data; // One of the input characters
    unsigned freq; // Frequency of the character
    Node *left, *right;

    Node(char data, unsigned freq)
        : data(data), freq(freq), left(NULL), right(NULL) {}
};

struct compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

void printCodes(Node* root, string str) {
    if (!root) return;

    if (root->left == NULL && root->right == NULL)
        cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void HuffmanCodes(vector<char>& data, vector<int>& freq, int size) {
    Node *left, *right, *top;
    priority_queue<Node*, vector<Node*>, compare> minHeap;

    for (int i = 0; i < size; ++i) {
        minHeap.push(new Node(data[i], freq[i]));
    }

    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();

        top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    printCodes(minHeap.top(), "");
}

int main() {
    vector<char> arr;
    vector<int> freq;
    int size;
    char character;
    int frequency;

    cout << "Enter the number of characters: ";
    cin >> size;

    cout << "Enter characters and their frequencies:\n";
    for (int i = 0; i < size; ++i) {
        cin >> character >> frequency;
        arr.push_back(character);
        freq.push_back(frequency);
    }

    cout << "Huffman codes in the preorder traversal of tree: ";
    HuffmanCodes(arr, freq, size);

    return 0;
}