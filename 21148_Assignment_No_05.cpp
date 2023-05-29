#include <iostream>
#define size 10
using namespace std;

class Node
{
    string key;
    int value;
    Node *next;

public:
    Node()
    {
        key = "";
        value = 0;
        next = NULL;
    }

    Node(string k, int v)
    {
        key = k;
        value = v;
        next = NULL;
    }

    friend class OpenHash;
};

class OpenHash
{
    Node *Array = new Node[size];

public:
    OpenHash() {}

    int HashFunction(string key)
    {
        int ret = 0;
        for (int i = 0; key[i] != '\0'; i++)
        {
            ret += int(key[i]);
        }
        return ret % size;
    }

    void Insert(string key, int value)
    {
        int HashIndex = HashFunction(key);
        Node *temp = new Node(key, value);

        if (Array[HashIndex].next == NULL)
        {
            Array[HashIndex].next = temp;
        }
        else
        {
            Node *p = &Array[HashIndex];
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = temp;
        }
    }

    void Display()
    {
        Node *p;
        cout << "\n________________________ HASH TABLE _______________________\n\n";
        for (int i = 0; i < size; i++)
        {
            cout << "\n| " << i << " | ";
            p = &Array[i];
            if (p->next != NULL)
            {
                p = p->next;
                while (p)
                {
                    cout << " >> " << p->key << " : " << p->value;
                    p = p->next;
                }
            }
            else
            {
                cout << " >> "
                     << "EMPTY"
                     << " : " << p->value;
            }
        }
        cout << "\n____________________________________________________________\n\n";
    }

    bool Search(string key)
    {
        int HashIndex = HashFunction(key);
        Node *p = &Array[HashIndex];
        p = p->next;

        while (p)
        {
            if (p->key == key)
            {
                return true;
            }
            p = p->next;
        }

        return false;
    }

    void Delete(string key)
    {
        if (!Search(key))
        {
            cout << "Key is Absent" << endl;
            return;
        }

        int HashIndex = HashFunction(key);
        Node *p = &Array[HashIndex];
        Node *q = p->next;

        while (q->key != key)
        {
            p = q;
            q = q->next;
        }

        p->next = q->next;
        string str = q->key;
        q->next = NULL;
        delete q;
        cout << "Successfully deleted the key : " << str << endl;
    }
};

void func()
{
    cout << "___________________________\n\n";
    cout << "\t1. Insert\n\t2. Display\n\t3. Search\n\t4. Delete\n";
    cout << "___________________________\n\n";
}

int main()
{
    OpenHash H;
    int choice, value;
    string key;

    cout << "\n---- SEPARATE CHAINING ----\n";
    cout << "___________________________\n\n";
    cout << "\t  MENU\n";
    func();

    while (true)
    {
        cout << "\nEnter choice : ";
        cin >> choice;

        if (choice == 0)
            func();
        else if (choice == 1)
        {
            cout << "\nEnter key : ";
            cin >> key;
            cout << "Enter value : ";
            cin >> value;
            H.Insert(key, value);
        }
        else if (choice == 2)
        {
            H.Display();
        }
        else if (choice == 3)
        {
            cout << "\nEnter key to search : ";
            cin >> key;
            if(H.Search(key)){
                cout<<key<<" is present."<<endl;
            }
            else{
                cout<<"Key is absent."<<endl;
            }
        }
        else if(choice == 4){
            cout<<"\nEnter key to delete : ";
            cin>>key;
            H.Delete(key);
        }
        else{
            cout<<"\n ======== THANK YOU =======\n";
            break;
        }
    }

    return 0;
}