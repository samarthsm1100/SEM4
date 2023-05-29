#include <iostream>
using namespace std;

// <------------------------------------ NODE ----------------------------------------->

class Node{
    int data;
    Node *left,*right;
    int lflag,rflag;

    public:

    Node(){
        data = -999;
        left = right = NULL;
        lflag = rflag = 0;
    }

    Node(int d){
        data = d;
        left = right = NULL;
        lflag = rflag = 0;
    }

    friend class Thread;
};

class Thread{
    Node *root,*dummy;
    bool flag;

    public:
    
    Thread(){
        root = NULL;
        flag = true;
    }

// <------------------------------------- INSERTION --------------------------------------->

    void create(int d){
        Node *temp = new Node(d);
        flag = true;
        if(root == NULL){
            dummy = new Node;
            root = temp;
            dummy->left = root;
            root->left = dummy;
            root->right = dummy;
        }
        else{
            insert(root, temp);
        }
    }

    void insert(Node *root, Node *temp){
        while(flag){
            if(temp->data < root->data){
                if(root->lflag == 0){
                    temp->left = root->left;
                    temp->right = root;
                    root->left = temp;
                    root->lflag = 1;
                    flag = false;
                }
                else{
                    root = root->left;
                }
            }
            if(temp->data > root->data){
                if(root->rflag == 0){
                    temp->right = root->right;
                    temp->left = root;
                    root->rflag = 1;
                    root->right = temp;
                    flag = false;
                }
                else{
                    root = root->right;
                }
            }
        }
    }

// <---------------------------------------- DISPLAY ----------------------------------------->

    void display(){
        if(root == NULL){
            cout<<"Tree is not created !"<<endl;
        }
        else{
            cout<<"\nInorder  : ";
            inorder(root, dummy);
            cout<<"\nPreorder : ";
            preorder(root, dummy);
            cout<<endl;
        }
    }

    void inorder(Node *temp, Node *dummy){
        while(temp != dummy){
            while(temp->lflag == 1){
                temp = temp->left;
            }
            cout<<" "<<temp->data;
            while(temp->rflag == 0){
                temp = temp->right;
                if(temp == dummy)
                    return;
                cout<<" "<<temp->data;
            }
            temp = temp->right;
        }
    }

    void preorder(Node *temp, Node *dummy){
        while(temp != dummy){
            while(temp->lflag == 1){
                cout<<" "<<temp->data;
                temp = temp->left;
            }
            cout<<" "<<temp->data;
            while(temp->rflag == 0){
                temp = temp->right;
                if(temp == dummy)
                    return;
            }
            temp = temp->right;
        }
    }

// <--------------------------------- INORDER SUCCESSOR ----------------------------------->

    Node *insuc(Node *temp){
        if(temp->rflag == 0){
            return temp->right;
        }
        temp = temp->right;
        while(temp->lflag == 1){
            temp = temp->left;
        }
        return temp;
    }

// <------------------------------------ INORDER PREDECESSOR ------------------------------->

    Node *inpre(Node *temp){
        if(temp->lflag == 0){
            return temp->left;
        }
        temp = temp->left;
        while(temp->rflag == 1){
            temp = temp->right;
        }
        return temp;
    }

//<--------------------------------------- DELETION ---------------------------------------->

    void del(){
        int key;
        cout<<"\nEnter key you want to delete : ";
        cin>>key;
        del_logic(root, dummy, key);
    }

    void del_logic(Node *root, Node *dummy, int key){
        Node *par = dummy;
        Node *ptr = root;

        bool found = false;

        while(ptr != NULL){
            if(key == ptr->data){
                found = true;
                break;
            }
            par = ptr;
            if(key < ptr->data){
                if(ptr->lflag == 1){
                    ptr = ptr->left;
                }
                else{
                    break;
                }
            }
            else{
                if(ptr->rflag == 1){
                    ptr = ptr->right;
                }
                else{
                    break;
                }
            }
        }

        if(!found){
            cout<<"\nKey is not present "<<endl;
        }
        else if(ptr->lflag == 0 && ptr->rflag == 0){
            no_child(root, par, ptr);
        }
        else if(ptr->lflag == 0 || ptr->rflag == 0){
            one_child(root, par, ptr);
        }
        else{
            two_child(root, par, ptr);
        }

    }

    void no_child(Node *root, Node *par, Node *ptr){
        if(par == NULL){
            root = NULL;
        }
        else if(ptr == par->left){
            par->lflag = 0;
            par->left = ptr->left;
        }
        else{
            par->rflag = 0;
            par->right = ptr->right;
        }
        delete ptr;
    }

    void one_child(Node *root, Node *par, Node *ptr){
        Node *child, *s, *p;
        if(ptr->lflag == 1){
            child = ptr->left;
        }
        else{
            child = ptr->right;
        }
        if(par == NULL){
            root = child;
        }
        else if(ptr == par->left){
            par->left = child;
        }
        else{
            par->right = child;
        }
        s = insuc(ptr);
        p = inpre(ptr);
        if(ptr->lflag == 1){
            p->right = s;
        }
        else if(ptr->rflag == 1){
            s->left = p;
        }
        delete ptr;
    }

    void two_child(Node *root, Node *par, Node *ptr){
        Node *s, *pars;
        pars = ptr;
        s = ptr->right;
        ptr->data = s->data;

        if(s->lflag == 0 && s->rflag == 0){
            no_child(root, pars, s);
        }
        else if(s->lflag == 0 || s->rflag == 0){
            one_child(root, pars, s);
        }
        else{
            two_child(root, pars, s);
        }
    }
};

void func(){
    cout<<"\n_____________________________________\n";
    cout<<"\n\t1.Create Tree\n\t2.Insert Node\n\t3.Display \n\t4.Delete Node\n\t5.EXIT \n";
    cout<<"_____________________________________\n";
}

int main(){
    Thread tree;
    int n = 0;
    int temp = 0;
    int choice = 0;
    cout<<"\n============ THREADED TREE =============\n"<<endl;
    cout<<"\t_______ MENU ______\n";
    
    func();
    while(true){    
        cout<<"\nEnter choice in MENU : ";
        cin>>choice;

        if(choice == 0){
            func();
        }
        else if(choice == 1){
            cout<<"\nEnter element : ";
            cin>>temp;
            tree.create(temp);
        }
        else if(choice == 2){
            cout<<"\nEnter element : ";
            cin>>temp;
            tree.create(temp);
        }
        else if(choice == 3){
            tree.display();
        }
        else if(choice == 4){         
            tree.del();
        }
        else{
            cout<<"\n========== THANK YOU ===========\n";
            break;
        }
    }
    return 0;
}