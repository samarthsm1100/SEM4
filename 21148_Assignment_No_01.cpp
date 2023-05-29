#include <iostream>
using namespace std;

class Node{
    int data;
    Node *left;
    Node *right;

    public:
    
    Node(){
        this->data = 0;
        this->left = NULL;
        this->right = NULL;
    }

    Node(int d){
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }

    friend class BST;
};

class BST{
    Node *root;
    int longest,k;

    public:

    BST(){
        root = NULL;
        longest = k =  0;
    }

    void create(int d){
        Node *temp = new Node(d);
        if(root == NULL){
            root = temp;
        }
        else{
            insert(root, temp);
        }
    }

    void insert(Node *root, Node *var){
        // Left-Subtree
        if(var->data < root->data){
            if(root->left == NULL){
                root->left = var;
                if(k>longest)
                longest = k;
                // k = 0;
            }
            else{
                insert(root->left, var);
                k++;
            }
        }

        // Right-Subtree
        if(var->data > root->data){
            if(root->right == NULL){
                root->right = var;
                if(k>longest)
                longest = k;
                // k = 0;
            }
            else{
                insert(root->right, var);
                k++;
            }
        }
    }

    void display(){
        int choice = 0;
        cout<<"\nSelect Traversal"<<endl;
        cout<<"1. PreOrder\n2. InOrder\n3. PostOrder\n4. Exit\n";
        while(true){
            cout<<"\nEnter choice : ";
            cin>>choice;
            if(choice == 1)
            preorder(root);
            else if(choice == 2)
            inorder(root);
            else if(choice == 3)
            postorder(root);
            else
            break;
        }
        cout<<endl<<endl;
    }

    void inorder(Node *temp){
        if(temp != NULL){
            inorder(temp->left);
            cout<<temp->data<<" ";
            inorder(temp->right);
        }
    }

    void preorder(Node *temp){
        if(temp != NULL){
            cout<<temp->data<<" ";
            preorder(temp->left);
            preorder(temp->right);
        }
    }

    void postorder(Node *temp){
        if(temp != NULL){
            postorder(temp->left);
            postorder(temp->right);
            cout<<temp->data<<" ";
        }
    }

    void max_value(){
        Node *temp = root;
        while(temp->right != NULL)
        temp = temp->right;
        cout<<"Maximum element is : "<<temp->data<<endl;
    }

    void min_value(){
        Node *temp = root;
        while(temp->left != NULL)
        temp = temp->left;
        cout<<"Minimum element is : "<<temp->data<<endl;
    }

    bool search(int key){
        return search_func(root, key);
    }

    bool search_func(Node *root, int key){
        if(root == NULL){
            return false;
        }
        else if(root->data == key){
            return true;
        }
        else if(root->data > key){
            return search_func(root->left, key);
        }
        else{
            return search_func(root->right, key);
        }
    }

    void long_path(){
        cout<<"Longest path is : "<<longest<<endl;
    }

    void swapped(){
        swap(root);
        display();
    }
    
    void swap(Node *root){
        Node *p = root->left;
        root->left = root->right;
        root->right = p;
        if(root->left != NULL)
        swap(root->left);
        if(root->right != NULL)
        swap(root->right);
    }

    void del(int key){
        del_logic(root, key);
    }

    Node *findMin(Node *root){
        Node *temp = root;
        while(temp && temp->left != NULL){
            temp = temp->left;
        }
        return temp;
    }

    Node *del_logic(Node *root, int data){
        if(root == NULL)
            return root;
        else if(data < root->data)
            root->left = del_logic(root->left, data);
        else if(data > root->data)
            root->right = del_logic(root->right, data);
        else{
            // Case 1 - No child
            if(root->left == NULL && root->right == NULL){
                delete root;
                root = NULL;
            }
            // Case 2 - One child
            else if(root->left == NULL){
                Node *temp = root;
                root = root->right;
                delete temp;
            }
            else if(root->right == NULL){
                Node *temp = root;
                root = root->left;
                delete temp;
            }
            // Case 3 - Two children
            else{
                Node *temp = findMin(root->right);
                root->data = temp->data;
                root->right = del_logic(root->right, temp->data);
            }
        }
        return root;
    }
};

void func(){
    cout<<"\n\t1.Create \n\t2.Insert \n\t3.Display \n\t4.Longest Path \n\t5.Search \n\t6.Swap \n\t7.Minimum element \n\t8.Maximum Element \n\t9.Delete\n\t10.EXIT\n\n";
}

int main(){
    BST tree;
    int n = 0;
    int temp = 0;
    int choice = 0;
    cout<<"\n========== BINARY SEARCH TREE ===========\n"<<endl;
    cout<<"\t_______ MENU ______\n";
    
    func();
    while(true){    
        cout<<"\nEnter choice in MENU : ";
        cin>>choice;

        if(choice == 0){
            func();
        }
        else if(choice == 1){
            cout<<"Enter element : ";
            cin>>temp;
            tree.create(temp);
        }
        else if(choice == 2){
            cout<<"Enter element : ";
            cin>>temp;
            tree.create(temp);
        }
        else if(choice == 3){
            tree.display();
        }
        else if(choice == 4){
            tree.long_path();
        }
        else if(choice == 5){
            cout<<"Enter key to search : ";
            cin>>temp;
            if(tree.search(temp))
            cout<<"Key is present"<<endl;
            else
            cout<<"Key is absent"<<endl;
        }
        else if(choice == 6){
            tree.swapped();
        }
        else if(choice == 7){
            tree.min_value();
        }
        else if(choice == 8){
            tree.max_value();
        }
        else if(choice == 9){
            cout<<"Enter element to delete : ";
            cin>>temp;
            tree.del(temp);
        }
        else{
            cout<<"\n========== THANK YOU ===========\n";
            break;
        }
    }

    return 0;
}