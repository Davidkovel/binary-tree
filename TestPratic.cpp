#include <iostream>
#include <Windows.h>
using namespace std;

class Node {
public:
    string word;
    string translation;
    size_t count;
    Node* left;
    Node* right;

    Node(string w, string t) : word(w), translation(t), count(0), left(nullptr), right(nullptr) {}

};

class Binary_Tree {
public:
    Node* root;

    Binary_Tree() { root = nullptr; }

    void addNode(string word, string translation) {
        Node* newNode = new Node(word, translation);

        if (root == nullptr) {
            root = newNode;
        }
        else {
            Node* focusNode = root;
            Node* parent = nullptr;

            while (true) {
                parent = focusNode;

                if (newNode->word < focusNode->word) {
                    focusNode = focusNode->left;

                    if (focusNode == nullptr) {
                        parent->left = newNode;
                        return;
                    }
                }
                else {
                    focusNode = focusNode->right;

                    if (focusNode == nullptr) {
                        parent->right = newNode;
                        return;
                    }
                }
            }
        }
    }

    string findTranslation(string word) {
        Node* focusNode = root;

        while (focusNode != nullptr) {
            if (word == focusNode->word) {
                focusNode->count++;
                return focusNode->translation;
            }
            else if (word < focusNode->word) {
                focusNode = focusNode->left;
            }
            else {
                focusNode = focusNode->right;
            }
        }

        return "The word is not found";
    }

    void replaceTranslation(string word, string newTranslation) {
        Node* focusNode = root;

        while (focusNode != nullptr) {
            if (word == focusNode->word) {
                focusNode->translation = newTranslation;
                return;
            }
            else if (word < focusNode->word) {
                focusNode = focusNode->left;
            }
            else {
                focusNode = focusNode->right;
            }
        }

        cout << "The word is not found" << endl;
    }

    void deleteNode(string word) {
        root = deleteNodeRecursive(root, word);
    }

    Node* deleteNodeRecursive(Node* focusNode, const string& word) {
        if (focusNode == nullptr) {
            return nullptr;
        }

        if (word < focusNode->word) {
            focusNode->left = deleteNodeRecursive(focusNode->left, word);  // лiвий
        }
        else if (word > focusNode->word) {
            focusNode->right = deleteNodeRecursive(focusNode->right, word); // правий
        }
        else {
            if (focusNode->left == nullptr) {
                Node* temp = focusNode->right;
                delete focusNode;
                return temp;
            }
            else if (focusNode->right == nullptr) {
                Node* temp = focusNode->left;
                delete focusNode;
                return temp;
            }

            Node* parent = focusNode;
            Node* temp = focusNode->right;

            while (temp->left != nullptr) {
                parent = temp;
                temp = temp->left;
            }

            focusNode->word = temp->word;
            focusNode->translation = temp->translation;
            focusNode->count = temp->count;

            if (parent != focusNode) {
                parent->left = deleteNodeRecursive(parent->left, temp->word);
            }
            else {
                focusNode->right = deleteNodeRecursive(focusNode->right, temp->word);
            }
        }
        return focusNode;
    }


    void collectNodes(Node* node, Node* nodes[], int& index) {
        if (node != nullptr) {
            nodes[index++] = node;
            collectNodes(node->left, nodes, index);
            collectNodes(node->right, nodes, index);
        }
    }

    void bubbleSortByCount(Node* nodes[], int size, bool descending = true) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if ((descending && nodes[j]->count < nodes[j + 1]->count) ||
                    (!descending && nodes[j]->count > nodes[j + 1]->count)) {
                    Node* temp = nodes[j];
                    nodes[j] = nodes[j + 1];
                    nodes[j + 1] = temp;
                }
            }
        }
    }

    void getTopWords() {
        const int maxNodes = 100;
        Node* nodes[maxNodes];
        int nodeCount = 0;

        collectNodes(root, nodes, nodeCount);

        bubbleSortByCount(nodes, nodeCount, true);

        cout << "Top-3 most popular words:" << endl;
        for (int i = 0; i < (nodeCount < 3 ? nodeCount : 3); i++) {
            cout << nodes[i]->word << " (" << nodes[i]->count << " times called)" << endl;
        }

        bubbleSortByCount(nodes, nodeCount, false);

        cout << "Top-3 most unpopular words:" << endl;
        for (int i = 0; i < (nodeCount < 3 ? nodeCount : 3); i++) {
            cout << nodes[i]->word << " (" << nodes[i]->count << " times called)" << endl;
        }
    }

    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    ~Binary_Tree() {
        deleteTree(root);
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Binary_Tree binary_tree;

    binary_tree.addNode("apple", "яблоко");
    binary_tree.addNode("banana", "банан");
    binary_tree.addNode("pear", "груша");
    binary_tree.addNode("peach", "персик");
    binary_tree.addNode("grape", "виноград");
    binary_tree.addNode("orange", "апельсин");
    
    cout << "Translation for 'apple': " << binary_tree.findTranslation("apple") << endl;
    cout << "Translation for 'banana': " << binary_tree.findTranslation("banana") << endl;
    cout << "Translation for 'banana': " << binary_tree.findTranslation("banana") << endl;
    cout << "Translation for 'orange': " << binary_tree.findTranslation("orange") << endl;
    cout << "Translation for 'grape': " << binary_tree.findTranslation("grape") << endl;

    cout << endl;
    binary_tree.replaceTranslation("apple", "нове яблоко");
    cout << "New translation for 'apple': " << binary_tree.findTranslation("apple") << endl;

    cout << endl;
    binary_tree.deleteNode("orange");
    cout << "Trying to find 'orange': " << binary_tree.findTranslation("orange") << endl;

    cout << endl;
    binary_tree.getTopWords();

    return 0;
}

/*
Translation for 'apple': яблоко
Translation for 'banana': банан
Translation for 'banana': банан
Translation for 'orange': апельсин
Translation for 'grape': виноград

New translation for 'apple': нове яблоко

Trying to find 'orange': The word is not found

Top-3 most popular words:
apple (2 times called)
banana (2 times called)
grape (1 times called)
Top-3 most unpopular words:
pear (0 times called)
peach (0 times called)
grape (1 times called)

C:\Users\David\source\repos\TestPratic\x64\Debug\TestPratic.exe (процесс 8620) завершил работу с кодом 0 (0x0).
Нажмите любую клавишу, чтобы закрыть это окно…

*/