#include <iostream>

using namespace std;

struct Node
{
    char data;
    struct Node *left, *right;
};

Node* newNode(char data)
{
    Node *temp = new Node;
    temp->data= data;
    temp->left = temp->right = NULL;
    return temp;
}

// **是什麼意思
void swap(Node **a, Node **b)
{
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

void swap_level(Node *root, int level)
{
    //if it is a leaf, then don't have to change
    if(root == NULL || (root->left == NULL && root->right == NULL))
        return;
    //if ( (level + 1) % k == 0)
    swap(&root->left, &root->right);
    
    //遞迴下去
    swap_level(root->left, level+1);
    swap_level(root->right, level+1);
}

void print(Node *root)
{
    if (root == NULL)
        return;
    print(root->left);
    cout << root->data << " ";
    print(root->right);
}

int main()
{
    
    /*     A
        /    \
       B      C
     /   \   /
    D     E  F
     \        \
      G        H */
    struct Node *root = newNode('A');
    root->left = newNode('B');
    root->right = newNode('C');
    root->left->left = newNode('D');
    root->left->right = newNode('E');
    root->right->left = newNode('F');
    root->left->left->right = newNode('G');
    root->right->left->right = newNode('H');
    
    //所以這個 k=2 是哪來的
    int k = 2;
    cout << "Before swapping the nodes:\n";
    print(root);
    cout << endl;
    
    swap_level(root, k);
    /*    A
        /    \
       C      B
         \   / \
          F E   D
         /      /
        H      G */
    
    cout << "\nAfter swapping the nodes:\n";
    print(root);
    return 0;
}
