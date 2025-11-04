//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

//The buildEncodingTree function starts with a minheap and pushes the index of weights that are > 0 into the
//heap. While the heap hasn't reached one node/the root node yet, a parent is created at index nextFree,
//and leftArr and rightArr which get the left and right child indexes. Using all three of these,
//the two smallest nodes' weights are popped and are combined and assigned to the parent's weight.
//Then, that parent index with that weight is pushed back into  the heap. The root node is then popped once
//it's the only thing left in order to return its index.

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    //^have to use an array
    MinHeap heap = MinHeap();

    //initialize starting index/size for array since weightArr[] is already given (I'm assuming there's no need to actually create one).
    //^used in the heap functions

    // 2. Push all leaf node indices into the heap.
    //loop until nextFree
    for (int i = 0; i < nextFree; i++) {
        if (weightArr[i] > 0) { //only pushes if the weight at the index i is > 0
            heap.push(i, weightArr);
        }
    }
    // 3. While the heap size is greater than 1:
    //  - Pop two smallest nodes
    //  - Create a new parent node with combined weight
    //  - Set left/right pointers
    //  - Push new parent index back into the heap
    while (heap.size > 1) {
        //two smallest nodes popped
        int pop1 = heap.pop(weightArr);
        int pop2 = heap.pop(weightArr);

        int parent = nextFree; //create spot for parent node
        leftArr[parent] = pop1; //leftArr stores left children
        rightArr[parent] = pop2; //rightArr stores right children

        weightArr[parent] = weightArr[pop1] + weightArr[pop2]; //combined weight of the two nodes

        heap.push(parent, weightArr); //pushed back into the heap
        nextFree++; //get next open index
    }
    // 4. Return the index of the last remaining node (root)
    return heap.pop(weightArr); //pop returns the last node which should be the root by now
}
//The generateCodes function creates a stack that pops each pair (nodeIdex, path) one by one off the stack
//and gets the left and right child of the current node, and then checks if they exist or not (if not, it's a leaf node),
//and finds the correct letter index/slot in codes[] using ASCII values (charArr[nodeIndex] - 'a'). If the right or left child
//exist, those left and right children's path strings are updated with "0" (for left) or "1" (for right) that hold the code, and that
//new pair is pushed into the stack.

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    if (root == -1) { //no root to start at
        return;
    }
    std::stack<pair<int, string>> codeStack;
    codeStack.push(make_pair(root, "")); //initialize stack

    // Left edge adds '0', right edge adds '1'.
    //if there's nothing in the left and right arrays, there's no children nodes --> leaf node
    while (codeStack.size() > 0) {
        pair<int, string> curr = codeStack.top();
        codeStack.pop();
        int nodeIndex = curr.first;
        string path = curr.second;

        int left = leftArr[nodeIndex];
        int right = rightArr[nodeIndex];

        // Record code when a leaf node is reached.
        if (left == -1 && right == -1) { //checks it's a leaf node (no children nodes)
            int letterIdx = charArr[nodeIndex] - 'a'; //get the character at the leaf node by subtracting ASCII codes to stay within the 0-25 range for the 26 letters
            if (path == "") { //leaf node is the only node
                codes[letterIdx] = "0"; //needs to use the letter index and not the node index to assign the code to that specific letter
            }
            else {
                codes[letterIdx] = path; //path to this leaf node is passed to codes[]
            }
        }

        //have to do path + "0" or "1" so that it adds to the existing code as it traverses
        if (right != -1) { //right child of the node exists
            codeStack.push(make_pair(right, path + "1")); //right edge
        }
        if (left != -1) { //left child of the node exists
            codeStack.push(make_pair(left, path + "0")); //left edge
        }
    }

}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}