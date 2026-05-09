#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <stdexcept>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// -------------------- Goods Structure --------------------
struct Goods {
    string name;
    string type;
    double weight;

    Goods(string n, string t, double w) {
        if (w <= 0) throw invalid_argument("Weight must be positive");
        name = n; type = t; weight = w;
    }

    void display() const {
        cout << left << setw(15) << name
             << setw(15) << type
             << setw(8) << weight << "kg" << endl;
    }
};

// -------------------- FIFO Queue Example --------------------
void truckQueueExample(vector<Goods>& goodsList) {
    cout << "\n--- FIFO Truck Queue Example ---\n";
    queue<Goods> loadingBay;

    for(const auto& g : goodsList)
        loadingBay.push(g);

    cout << setw(15) << "Truck Load Order" << endl;
    while(!loadingBay.empty()) {
        Goods g = loadingBay.front();
        g.display();
        loadingBay.pop();
    }
}

// -------------------- Sorting Algorithms with Timing --------------------
void bubbleSort(vector<double> &arr) {
    for(size_t i = 0; i < arr.size(); i++)
        for(size_t j = 0; j < arr.size()-i-1; j++)
            if(arr[j] < arr[j+1]) swap(arr[j], arr[j+1]);
}

int partition(vector<double> &arr, int low, int high) {
    double pivot = arr[high];
    int i = low-1;
    for(int j=low; j<high; j++)
        if(arr[j] > pivot) swap(arr[++i], arr[j]);
    swap(arr[i+1], arr[high]);
    return i+1;
}

void quickSort(vector<double> &arr, int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

void sortingExample(vector<double> weights) {
    cout << "\n--- Sorting Comparison ---\n";

    vector<double> bubbleArr = weights;
    auto start = high_resolution_clock::now();
    bubbleSort(bubbleArr);
    auto end = high_resolution_clock::now();
    auto bubbleTime = duration_cast<microseconds>(end - start).count();

    vector<double> quickArr = weights;
    start = high_resolution_clock::now();
    quickSort(quickArr, 0, quickArr.size()-1);
    end = high_resolution_clock::now();
    auto quickTime = duration_cast<microseconds>(end - start).count();

    vector<double> stlArr = weights;
    start = high_resolution_clock::now();
    sort(stlArr.begin(), stlArr.end(), greater<double>());
    end = high_resolution_clock::now();
    auto stlTime = duration_cast<microseconds>(end - start).count();

    cout << "Bubble Sort Desc: ";
    for(auto w : bubbleArr) cout << w << " ";
    cout << "\nTime: " << bubbleTime << " μs | Big O: O(n^2)\n";

    cout << "QuickSort Desc: ";
    for(auto w : quickArr) cout << w << " ";
    cout << "\nTime: " << quickTime << " μs | Big O: O(n log n) avg\n";

    cout << "STL sort Desc: ";
    for(auto w : stlArr) cout << w << " ";
    cout << "\nTime: " << stlTime << " μs | Big O: O(n log n)\n";
}

// -------------------- Stack Example --------------------
void stackExample(vector<string> functionCalls) {
    cout << "\n--- Stack Function Call Example ---\n";
    stack<string> callStack;
    for(auto f : functionCalls) callStack.push(f);

    while(!callStack.empty()) {
        cout << "Executing: " << callStack.top() << endl;
        callStack.pop();
    }
}

// -------------------- AVL Tree with Insert/Search/Delete --------------------
struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(AVLNode* node) { return node ? node->height : 0; }
int getBalance(AVLNode* node) { return node ? getHeight(node->left) - getHeight(node->right) : 0; }

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y; y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right))+1;
    x->height = max(getHeight(x->left), getHeight(x->right))+1;
    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x; x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right))+1;
    y->height = max(getHeight(y->left), getHeight(y->right))+1;
    return y;
}

AVLNode* insertAVL(AVLNode* node, int key) {
    if(!node) return new AVLNode(key);
    if(key < node->key) node->left = insertAVL(node->left, key);
    else if(key > node->key) node->right = insertAVL(node->right, key);
    else return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if(balance > 1 && key < node->left->key) return rightRotate(node);
    if(balance < -1 && key > node->right->key) return leftRotate(node);
    if(balance > 1 && key > node->left->key) { node->left = leftRotate(node->left); return rightRotate(node);}
    if(balance < -1 && key < node->right->key) { node->right = rightRotate(node->right); return leftRotate(node);}
    return node;
}

AVLNode* minValueNode(AVLNode* node) { while(node->left) node = node->left; return node; }

AVLNode* deleteAVL(AVLNode* root, int key) {
    if(!root) return root;
    if(key < root->key) root->left = deleteAVL(root->left, key);
    else if(key > root->key) root->right = deleteAVL(root->right, key);
    else {
        if(!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            if(!temp) { temp=root; root=nullptr; }
            else *root = *temp;
            delete temp;
        } else {
            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key);
        }
    }
    if(!root) return root;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);
    if(balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if(balance > 1 && getBalance(root->left) < 0) { root->left=leftRotate(root->left); return rightRotate(root);}
    if(balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if(balance < -1 && getBalance(root->right) > 0) { root->right=rightRotate(root->right); return leftRotate(root);}
    return root;
}

void preOrder(AVLNode* root) {
    if(root) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void avlExample(vector<int> inventory) {
    cout << "\n--- AVL Tree Example ---\n";
    AVLNode* root=nullptr;
    for(auto i : inventory) root = insertAVL(root, i);

    cout << "Preorder traversal: ";
    preOrder(root); cout << endl;

    if(!inventory.empty()) {
        cout << "Deleting node " << inventory[1] << "...\n";
        root = deleteAVL(root, inventory[1]);
        cout << "Preorder after deletion: ";
        preOrder(root); cout << endl;
    }
}

// -------------------- Routing Stub for Distinction --------------------
class RouteNetwork {
public:
    void dijkstraDemo() {
        cout << "\n--- Dijkstra Routing Stub ---\n";
        cout << "Illustration placeholder for shortest path analysis.\n";
    }
};

// -------------------- Main --------------------
int main() {
    try {
        vector<Goods> goodsList = {
            Goods("Laptop","Electronics",10.5),
            Goods("Shirt","Clothes",5),
            Goods("Apples","Food",20)
        };

        truckQueueExample(goodsList);

        vector<double> weights;
        for(auto g : goodsList) weights.push_back(g.weight);
        sortingExample(weights);

        stackExample({"Load Truck1","Load Truck2","Load Truck3"});

        avlExample({10,20,30,40,50,25});

        RouteNetwork rn;
        rn.dijkstraDemo();

    } catch(exception& e) { cerr << "Error: " << e.what() << endl; }
    return 0;
}