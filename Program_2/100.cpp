#include <iostream>
#include <map>
#include <deque>
#include <string.h>
#include <fstream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

map<char, int> alpha_weight;
map<char, int>::iterator iter;

//看character的frequence是多少 記錄在alpha_weight裡面
void count(string characters)
{
    char arr[characters.size()];
    strcpy(arr, characters.c_str());
    for(int i=0; i<characters.size(); i++)
    {
        iter = alpha_weight.find(arr[i]);
        if(iter != alpha_weight.end())
            iter -> second++;
        else
            alpha_weight.insert(pair<char, int>(arr[i], 1));
    }
}

//每個節點裡面要存的資料和指標
class node
{
public:
    int alph;
    int weight;
    node* left;
    node* right;
    node(){};
};

//暫存資料的結構
class something
{
public:
    char alph;
    int weight;
    unsigned long wepl;
    string s;
};

deque<node*> forest; //用來儲存各個節點之指標
deque<something> store; //要印出來之前的暫存容器

//頻率小
bool compare1(const node* a, const node* b)
{
    return a -> weight < b -> weight;
}

//字母小
bool compare2(something a, something b)
{
    return (int)a.alph < (int)b.alph;
}

//建立hufftree
void construct_huffTree(map<char, int> alpha_weight)
{
    for(const auto& information : alpha_weight)
    {
        node* temp = new node;
        temp->alph = information.first;
        temp->weight = information.second;
        temp->left = NULL;
        temp->right = NULL;
        forest.push_back(temp);
    }
    while (forest.size() != 1)
    {
        sort(forest.begin(), forest.end(), compare1);
        //從最小的兩個開始合併
        node* temp1 = forest.front();
        forest.pop_front();
        node* temp2 = forest.front();
        forest.pop_front();
        node* temp = new node;
        temp->alph = ' ';
        temp->weight = temp1->weight + temp2->weight;
        temp->left = temp1;
        temp->right = temp2;
        forest.push_back(temp);
    }
}

map<string, char> code_alpha;
map<string, char>::iterator itz;

//找到最下面的A B C所對應的編碼
void store_huffTree(const node* root, string s)
{
    if(root -> left == NULL || root -> right == NULL)
    {
        something temp;
        temp.alph = root -> alph;
        temp.weight = root -> weight;
        temp.s = s;
        temp.wepl = s.size();
        store.push_back(temp);
        code_alpha[temp.s] = temp.alph;
    }
    if(root -> left != NULL)
        store_huffTree(root -> left, string(s + '0'));
    if(root->right != NULL)
        store_huffTree(root -> right, string(s + '1'));
    return;
}

//印出編碼前的資料
void before(map<char, int> alpha_weight)
{
    int i=0;
    for(const auto& x : alpha_weight)
    {
        cout << x.first << " = " << x.second << " | ";
        i++;
        if(i%10 == 0)
            cout << endl;
    }
}

//印出decode後的資料
void decode(string huffman_code)
{
    string temp = "";
    for(int i=0; i<huffman_code.length(); i++)
    {
        temp += huffman_code[i];
        for (itz = code_alpha.begin(); itz != code_alpha.end(); itz++)
        {
            if(code_alpha.find(temp) != code_alpha.end())
            {
                cout << code_alpha[temp];
                temp = "";
            }
        }
    }
    if(temp.length())
        cout << " -wrong decode-";
}

int main(int argc, const char* argv[])
{
    vector<string> all_args;
    all_args.assign(argv, argv + argc); // convert command line argument to string

    cout << "DSOO-Program2-Demo: ";
    for(auto a : all_args)
    {
        cout << a << " ";
    }
    cout << "\n";
    
    if(argc != 2)
    {
        cout << "\n\npart1\n\n";
        alpha_weight.insert(pair<char, int>('A', 11));
        alpha_weight.insert(pair<char, int>('B', 5));
        alpha_weight.insert(pair<char, int>('C', 2));
        alpha_weight.insert(pair<char, int>('D', 3));
        alpha_weight.insert(pair<char, int>('E', 12));
        alpha_weight.insert(pair<char, int>('F', 3));
        alpha_weight.insert(pair<char, int>('G', 5));
        alpha_weight.insert(pair<char, int>('H', 6));
        alpha_weight.insert(pair<char, int>('I', 8));
        alpha_weight.insert(pair<char, int>('J', 1));
        alpha_weight.insert(pair<char, int>('K', 2));
        alpha_weight.insert(pair<char, int>('L', 4));
        alpha_weight.insert(pair<char, int>('M', 8));
        alpha_weight.insert(pair<char, int>('N', 7));
        alpha_weight.insert(pair<char, int>('O', 2));
        alpha_weight.insert(pair<char, int>('P', 2));
        alpha_weight.insert(pair<char, int>('Q', 1));
        alpha_weight.insert(pair<char, int>('R', 9));
        alpha_weight.insert(pair<char, int>('S', 6));
        alpha_weight.insert(pair<char, int>('T', 2));
        alpha_weight.insert(pair<char, int>('U', 4));
        alpha_weight.insert(pair<char, int>('V', 1));
        alpha_weight.insert(pair<char, int>('W', 10));
        alpha_weight.insert(pair<char, int>('X', 10));
        alpha_weight.insert(pair<char, int>('Y', 1));
        alpha_weight.insert(pair<char, int>('Z', 1));
        before(alpha_weight);
        cout << endl;
        construct_huffTree(alpha_weight);
        string s = "";
        store_huffTree(forest.front(), s);
        sort(store.begin(), store.end(), compare2);
        int wepl = 0;
        cout << endl;
        while (!store.empty())
        {
            something temp = store.front();
            store.pop_front();
            cout << temp.alph << " : " << temp.s << endl;
            wepl += temp.weight * temp.wepl;
        }
        cout << endl;
        cout << "WEPL : " << wepl;
        cout << endl;
    }
    else
    {
        string filename = argv[1];
        cout << "read file from : " << "test/" << filename << endl;
        
        fstream f;
        f.open(filename, ios::in);
        
        
        string characters, huffman_code;
        f >> characters;
        f >> huffman_code;
        
        /*cout << "cin character: ";
        cin >> characters;
        cout << "cin huffman_code: ";
        cin >> huffman_code;*/
        
        cout << "characters : " << characters;
        cout << endl;
        
        count(characters);
        before(alpha_weight);
        cout << endl;
        construct_huffTree(alpha_weight);
        string s = "";
        store_huffTree(forest.front(), s);
        sort(store.begin(), store.end(), compare2);
        int wepl = 0;
        cout << endl;
        while (!store.empty())
        {
            something temp = store.front();
            store.pop_front();
            cout << temp.alph << " : " << temp.s << endl;
            wepl += temp.weight * temp.wepl;
        }
        cout << endl;
        
        cout << "Huffman code : " << huffman_code;
        
        cout << "\ndecode : ";
        decode(huffman_code);
        cout << "\nWEPL : " << wepl;
        cout << endl;
    }
    return 0;
}
