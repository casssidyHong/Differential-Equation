#include<iostream>

using namespace std;
   
class Node{
    public:
    int key;
    Node *left;
    Node *right;
    int height;
};

Node* newNode(int key){
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}
   
int max(int a, int b){
    if(a>b)
        return a;
    else
        return b;
}
   
int getHeight(Node *n){
    if (n == NULL)
        return 0;
    return n->height;
}

// right rotate the sub tree rooted with y
Node *rightRotate(Node *y){
    Node *x = y->left;
    Node *temp = x->right;
   
    // Perform rotation
    x->right = y;
    y->left = temp;
   
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
   
    return x; // new root
}
   
// left rotate the sub tree rooted with x
Node *leftRotate(Node *x){
    Node *y = x->right;
    Node *temp = y->left;
   
    // Perform rotation
    y->left = x;
    x->right = temp;
    
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
   
    return y; // new root
}
   
int BF(Node *N){
    if (N == NULL)
        return 0;
    return getHeight(N->left) - getHeight(N->right);
}

Node* insert(Node* node, int key){
    //normal BST rotation
    if (node == NULL)
        return(newNode(key));
   
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys not allowed
        return node;
   
    //update height of ancestor node
    node->height = 1 + max(getHeight(node->left),  getHeight(node->right));
   
    int bf = BF(node);
   
    if (bf > 1 && key < node->left->key)
        return rightRotate(node);
   
    if (bf < -1 && key > node->right->key)
        return leftRotate(node);
    
    if (bf > 1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
   
    if (bf < -1 && key < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void print(Node *root){
    if(root != NULL){
        print(root->left);
        cout << root->key << " ";
        print(root->right);
    }
}

int main(){
    Node *root = NULL;
   
    root = insert(root, 12);
    root = insert(root, 1);
    root = insert(root, 4);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 8);
    root = insert(root, 10);
    root = insert(root, 2);
    root = insert(root, 11);
    root = insert(root, 5);
    root = insert(root, 6);
     
    cout << "Ascending order of the AVL tree is: \n";
    print(root);
    cout << endl;
   
    return 0;
}
