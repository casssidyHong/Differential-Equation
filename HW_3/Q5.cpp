#include <iostream>

using namespace std;

struct node{
    pair<int, char> content;
    node *left;
    node *right;
};

node *newNode(int key, char element){
    node *temp = new node();
    temp->content.first = key;
    temp->content.second = element;
    temp->left = NULL;
    temp -> right = NULL;
  return temp;
}

// inorder
void print(node *root){
    if(root != NULL){
        print(root->left);
        cout << "(" << root -> content.first << ", " << root -> content.second << ") ";
        print(root->right);
    }
}

node *insert(node *node, pair<int, char> key){
    if(node == NULL)
        return newNode(key.first, key.second);
    if (key.first < node -> content.first)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    
    return node;
}

// Find the inorder successor
node *minValueNode(node *node){
    struct node *current = node;
    // Find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

node *deleteNode(node *root, pair<int, char> key){
    // the tree is empty
    if (root == NULL)
        return root;

    // Find the node to be deleted
    if (key.first < root-> content.first)
        root->left = deleteNode(root->left, key);
    else if (key.first > root->content.first)
        root->right = deleteNode(root->right, key);
    else{
        // one child or no child
        if(root->left == NULL){
            node *temp = root->right;
            free(root);
            return temp;
        }else if(root->right == NULL){
            node *temp = root->left;
            free(root);
            return temp;
        }

        // two children
        node *temp = minValueNode(root->right);

        // Place the inorder successor in position of the node to be deleted
        root->content = temp->content;
        
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->content);
    }
    return root;
}


int main(){
    node *root = NULL;
    root = insert(root, pair<int, char>(18, 'a'));
    root = insert(root, pair<int, char>(31, 'b'));
    root = insert(root, pair<int, char>(1, 'c'));
    root = insert(root, pair<int, char>(62, 'd'));
    root = insert(root, pair<int, char>(7, 'e'));
    root = insert(root, pair<int, char>(0, 'f'));
    root = insert(root, pair<int, char>(4, 'g'));
    root = insert(root, pair<int, char>(43, 'h'));

    cout << "Insert (18,a), (31,b), (1,c), (62,d), (7,e), (0,f), (4,g), (43,h) inorder to the binary search tree.\n\n";
    cout << "Before deleting 31, the inorder traversal is:\n";
    print(root);

    cout << "\n\nAfter deleting 31, the inorder traversal is:\n";
    root = deleteNode(root, pair<int, char>(31, 'b'));
    print(root);
    cout << endl;
    return 0;
}
