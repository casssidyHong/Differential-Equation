#include<iostream>

using namespace std;

struct a
{
    int n;
    a* next;
};

class bag
{
public:
    a* f, * l;
    
    bag()
    {
        f=new a;
        f->next=NULL;
        l=f;
    }
    
    void add(int n)
    {
        a* temp=new a;
        temp->n=n;
        temp->next=NULL;
        l->next=temp;
        l=temp;
        a* current=f;
        cout << "Number:";
        while(current->next != NULL)
        {
            cout << current->next->n << " ";
            current=current->next;
        }
        cout << endl;
    }
    
    void initialize()
    {
        f=new a;
        f->next=NULL;
        l=f;
    }
    
    void del(int n)
    {
        int something=1;
        int time=0;
        a* current=f;
        if(current == NULL)
        {
            cout << n << " isn't in the bag." << endl;
        }
        else
        {
            while(current->next != NULL)
            {
                if(current->next->n == n)
                {
                    something=0;
                    a* temp = current->next;
                    current->next = temp->next;
                    delete(temp);
                    time++;
                    cout << "The bag had delete " << time << " time of the number " << n << ":";
                    a* temp_2=f;
                    while(temp_2->next != NULL)
                    {
                        cout << temp_2->next->n << " ";
                        temp_2 = temp_2->next;
                    }
                    cout << endl;
                }
                else
                {
                    current = current->next;
                }
            }
            if(something==1)
            {
                cout << "No number " << n << " int the bag." << endl;
            }
        }
        cout << endl;
    }
};

class queue :public bag
{
public:
    queue()
    {
        this->f=new a;
        this->f->next=NULL;
        this->l=this->f;
    }
    void del_queue()
    {
        a* temp=f;
        if(temp->next == NULL)
        {
            cout << "The queue has been empty!" << endl << endl;
        }
        else
        {
            cout << "Delete  num " << temp->next->n << " from the first place of this queue." << endl;
            f=temp->next;
            delete(temp);
            a* current=f;
            cout << "The queue now has the number:";
            while(current->next != NULL)
            {
                cout << current->next->n << " ";
                current = current->next;
            }
            cout << endl;
        }
    }
};

int main()
{
    int n;
    cout << "Make a bag, input 1. Make a queue, input 2." << endl;
    cin >> n;
    if (n == 1)
    {
        bag bag;
        int something=1;
        while(something == 1)
        {
            int m;
            cout << "Add number, input 1.Delete number, input 2.Stop this bag, input 3." << endl;
            cin >> m;
            if(m == 1)
            {
                int o;
                cout << "Add a new number = ";
                cin >> o;
                bag.add(o);
            }
            else if(m == 2)
            {
                int p;
                cout << "Delete a number = ";
                cin >> p;
                bag.del(p);
            }
            else if(m == 3)
                something=0;
            else
                cout << "Error!";
        }
    }
    else if(n == 2)
    {
        queue queue;
        int something_2=1;
        while(something_2 == 1)
        {
            int q;
            cout << "Input 1 to add a new number. Input 2 to delete number. Input 3 to stop." << endl;
            cin >> q;
            if (q == 1)
            {
                int r;
                cout << "Add a new number = ";
                cin >> r;
                queue.add(r);
            }
            else if(q == 2)
                queue.del_queue();
            else if(q == 3)
                something_2=0;
            else
                cout << "Error!";
        }
    }
    else
    {
        cout << "Error!";
    }
    return 0;
}
