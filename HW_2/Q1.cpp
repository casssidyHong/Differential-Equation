#include <iostream>
using namespace std;

struct queue
{
    int data;
    queue *next;
    //為什麼next都是指向０？
    queue():data(0),next(0){};
    queue(int x):data(x),next(0){};
};

class queuelist
{
private:
    //為什麼不用說front, back指向哪裡？
    queue *front;
    queue *back;
    int size;
public:
    queuelist():front(0),back(0),size(0){};
    void Push(int x);
    void Pop();
    bool IsEmpty();
    int getFront();
    int getBack();
    int getSize();
};

void queuelist::Push(int x)
{
    if(IsEmpty())
    {
        front = new queue(x);
        back = front;
        size++;
        return;
    }
    queue *newnode = new queue(x);
    back->next = newnode;
    back = newnode;
    size++;
    if(IsEmpty())
        cout << "The queue is empty.\n";
    else
        cout << "FRONT: " << getFront() << " BACK: " << getBack();
}

void queuelist::Pop()
{
    if(IsEmpty())
    {
        cout << "The queue is empty.\n";
        return;
    }
    queue *deletenode = front;
    front = front->next;
    delete deletenode;
    deletenode = 0;
    size--;
    if(IsEmpty())
        cout << "The queue is empty.\n";
    else
        cout << "FRONT: " << getFront() << " BACK: " << getBack();
}

int queuelist::getFront()
{
    if(IsEmpty())
    {
        cout << "The queue is empty.\n";
        return -1;
    }
    return front->data;
}

int queuelist::getBack()
{
    if(IsEmpty())
    {
        cout << "The queue is empty.\n";
        return -1;
    }
    return back->data;
}

bool queuelist::IsEmpty()
{
    return ((front && back) == 0);
}

int queuelist::getSize()
{
    return size;
}


int main()
{
    queuelist q;
    if(q.IsEmpty())
    {
        cout << "The queue is empty now.";
    }
    cout << "\n\nPush 1, 2 inorder to the queue.\n";
    //為什麼者邊不會輸出兩行FRONT跟BACK?
    q.Push(1);
    q.Push(2);
    cout << "\n\nThe size of the queue now is: " << q.getSize();
    cout << "\n\nPop the first element\n";
    q.Pop();
    cout << "\n\nPush 3 to the queue.\n";
    q.Push(3);
    cout << "\n\nPop the first element\n";
    q.Pop();
    cout << "\n\nPop the first element\n";
    q.Pop();
    return 0;
}
