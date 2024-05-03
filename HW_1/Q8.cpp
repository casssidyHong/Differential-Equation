#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

class A
{
public:
    int row, col, val;
    A(int x = -1, int col = -1, int val = -1) : row(row), col(col), val(val) {}
};

class Matrix
{
public:
    Matrix(){}
    Matrix(int row_num, int col_num, int r) : row_num(row_num), col_num(col_num), r(r) {}
    Matrix(const Matrix& other);
    Matrix operator*(Matrix& other);
    void set_M();
    void set_vec();
    void display();

    int row_num;
    int col_num;
    int r;
    int M[100][100];
    vector<A> vec;
};

Matrix::Matrix(const Matrix& copy)
{
    row_num = copy.row_num;
    col_num = copy.col_num;
    r = copy.r;
    vec = copy.vec;
    for(int i=0; i<row_num; i++)
    {
        for(int j=0; j<col_num; j++)
        {
            M[i][j]=copy.M[i][j];
        }
    }
}

void set_input(Matrix& K)
{
    cin >> K.row_num >> K.col_num >> K.r;
    for(int i=0; i<K.r; i++)
    {
        int row, col, val;
        cin >> row >> col >> val;
        A a(row, col, val);
        K.vec.push_back(a);
    }
    K.set_M();
}

void Matrix::set_M()
{
    memset(M, 0, sizeof(M));
    for(int i=0; i<r; i++)
        M[vec[i].row][vec[i].col]=vec[i].val;
}

void Matrix::set_vec()
{
    int count=0;
    for(int i=0; i<row_num; i++)
    {
        for(int j=0; j<col_num; j++)
        {
            if (M[i][j] != 0)
            {
                A element(i, j, M[i][j]);
                vec.push_back(element);
                count++;
            }
        }
    }
    r = count;
}

void Matrix::display()
{
    for(int i=0; i<row_num; i++)
    {
        for(int j=0; j<col_num; j++)
            cout << M[i][j] << " ";
        cout << endl;
    }
}

Matrix Matrix::operator*(Matrix& other)
{
    Matrix mul_f(row_num, other.col_num, 0);

    if(other.col_num*r <= row_num*other.r)
    {
        for(int i=0; i<r; i++)
        {
            for(int j=0; j<other.col_num; j++)
                mul_f.M[vec[i].row][j] += vec[i].val*other.M[vec[i].col][j];
        }
    }
    else
    {
        for(int i=0; i<other.r; i++)
        {
            for(int j=0; j<row_num; j++)
                mul_f.M[j][other.vec[i].col] += other.vec[i].val*M[j][other.vec[i].row];
        }
    }
    mul_f.set_vec();
    return mul_f;
}

int main()
{
    Matrix Sample;
    Matrix Sample_2;
    set_input(Sample);
    set_input(Sample_2);

    Matrix copy_SM=Sample;
    cout << "copy result: " << endl;
    copy_SM.display();
    return 0;
}






/*#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

class Matrix
{
private:
    int** matrix;
    int row;
    int column;
    
public:
    
    // Constructor with parameters
    Matrix(int a, int b)
    {
        row = a;
        column = b;
        matrix = new int*[row];

        for (int i = 0; i < row; i++)
        {
            matrix[i] = new int[column];
        }
        
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                matrix[i][j] = rand() % 100;
            }
        }

    }
    // Copy constructor
    Matrix(const Matrix& N)
    {
        row = N.row;
        column = N.column;

        //開一個新的矩陣 大小跟原本的一樣大
        matrix = new int*[row];
        for (int i = 0; i < row; i++)
        {
            matrix[i] = new int[column];
        }

        //把原本矩陣裡面的數值複製過來新的裡面
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                matrix[i][j] = N.matrix[i][j];
            }
        }
    }
    
    void print()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Matrix x(3, 3);
    cout << "Here's a 3*3 matrix." << endl;
    x.print();
}*/



/*#include <iostream>

using namespace std;

class matrix
{
private:
    int x,y;
public:
    matrix(int x1, int y1)
    {
        x=x1;
        y=y1;
    }
    
    //copy constructor
    matrix(const matrix&);
};

int main(void)
{
    cout << "Please imput the size of a 'm*n' matrix:" << endl;
    int m, n, r;
    cout << "m = ";
    cin >> m;
    cout << "n = ";
    cin >> n;
    cout << "The amount of non-zero number 'r':" << endl;
    cin >> r;
    int arr[m][n];
    cout << "Please imput the coordinates and the number in the type of 'a, b, c;' :";
    int row, column;
    for(int i=0; i<r; i++)
    {
        cin >> row;
        getchar();
        cin >> column;
        getchar();
        cin >> arr[row][column];
        getchar();
    }
    cout << ;
    
    return 0;
}*/
