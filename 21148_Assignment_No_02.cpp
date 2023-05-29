#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
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

    // <----------------------------- COPY CONSTRUCTOR ---------------------------->
    Node(const Node& other){
        if (other.left != nullptr )
        {
            left = new Node(*other.left);
        }
        if (other.right != nullptr)
        {
            right = new Node(*other.right);
        }
    }

    // <----------------------- OVERLOADING ASSIGNMENT OPERATOR ---------------------->
    Node operator=(const Node& other)
    {
        data = other.data;

        Node * left_orig = left;
        left = new Node(*other.left);
        delete left_orig;

        Node * right_orig = right;
        right = new Node(*other.right);
        delete right_orig;

        return *this;
    }

    friend class BT;
};

class BT{
    Node *root;
    int longest,k;
    static int leaf;
    static int internal;

    public:
    // <------------------------------------ CONSTRUCTOR ------------------------------------>
    BT(){
        root = NULL;
        longest = k =  0;
    }

    // <------------------------------- Create and Insert Tree ------------------------------>
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
        Node *temp;
        queue<Node*>q;
        q.push(root);
        while(!q.empty()) 
        {
            temp = q.front();
            q.pop();

            if(temp->left == NULL) {
                temp->left = var;
                break;
            }

            else
                q.push(temp->left);
        
            if(temp->right == NULL) {
                temp->right = var;
                break;
            }

            else
                q.push(temp->right);
        }
    }

    // <------------------------------------------- DISPLAY --------------------------------------->
    void display(){
        int choice = 0;
        cout<<"\n__________________________________________\n";
        cout<<"\nSelect Traversal"<<endl;
        cout<<"1. PreOrder\n2. InOrder\n3. PostOrder\n4. Exit\n";
        cout<<"__________________________________________\n";
        while(true){
            cout<<"\nEnter choice : ";
            cin>>choice;
            if(choice == 1){
                cout<<"Preoder : ";
                preorder(root);
            }
            else if(choice == 2){
                cout<<"Inorder : ";
                inorder(root);
            }
            else if(choice == 3){
                cout<<"Postorder : ";
                postorder(root);
            }
            else
            break;
        }
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

    // <--------------------------------------- SWAPPING ---------------------------------->
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

    //<------------------------------------- HEIGHT ----------------------------------->
    int rheight(){
        return height(root);
    }

    int height(Node *root){
        if(root == NULL){
            return -1;
        }
        int left = height(root->left);
        int right = height(root->right);
        return max(left,right)+1;
    }

    // <------------------------------------ COUNT ---------------------------------->
    void count_node(Node *root){
        if(root){
            count_node(root->left);
            if(root->left == NULL && root->right == NULL)
                leaf++;
            if(root->left != NULL || root->right != NULL)
                internal++;
            count_node(root->right);
        }
    }

    static int return_leaf(){
        return leaf;
    }

    static int return_internal(){
        return internal;
    }

    void call_count(){
        count_node(root);
    }

    // <----------------------------------- DELETE TREE ----------------------------------->
    void delete_tree(){
        delete_logic(root);
    }

    void delete_logic(Node *root){
        if(root){
            delete_logic(root->left);
            delete_logic(root->right);
            cout<<"Deleting node : "<<root->data<<endl;
            delete root;
        }
    }

    // <-------------------------------- Iterative Traversal --------------------------------->
    void itr_call(){
        cout<<"\nInorder : ";
        itr_inorder(root);
        cout<<"\nPreorder : ";
        itr_preorder(root);
        cout<<"\nPostorder : ";
        itr_postorder(root);
    }
    
    void itr_inorder(Node *root){
        stack <Node *> st;
        Node *temp = root;
        while(st.empty() == false || temp != NULL){
            while(temp != NULL){
                st.push(temp);
                temp = temp->left;
            }
            temp = st.top();
            st.pop();
            cout<<temp->data<<" ";
            temp = temp->right;
        }   
    }

    void itr_preorder(Node *root){
        stack <Node *> st;
        Node *temp = root;
        st.push(root);
        while(!st.empty()){
            temp = st.top();
            st.pop();
            cout<<temp->data<<" ";
            if(temp->right != NULL){
                st.push(temp->right);
            }
            if(temp->left != NULL){
                st.push(temp->left);
            }
        }  
    }

    void itr_postorder(Node *root){
        stack <Node *>s1,s2;
        Node *temp;
        s1.push(root);
        if(root == NULL)
            return;
        while(!s1.empty()){
            temp = s1.top();
            s1.pop();
            s2.push(temp);

            if(temp->left)
                s1.push(temp->left);
            if(temp->right)
                s1.push(temp->right);
        }

        while(!s2.empty()){
            temp = s2.top();
            s2.pop();
            cout<<temp->data<<" ";
        }
    }
    

    // <--------------------------- Iterative Height ------------------------------>
    void itr_height(){
        iheight(root);
    }
    void iheight(Node *root){
        queue <Node *> q;
        q.push(root);
        int height = 0;
        int count = 0;
        if(root == NULL)
            return;
        while(!q.empty()){
            height++;
            count = q.size();
            while(count--){
                root = q.front();
                if(root->left != NULL)
                    q.push(root->left);
                if(root->right != NULL)
                    q.push(root->right);
                q.pop();
            }
        }
        cout<<"\nHeight of binary tree is : "<<height-1<<endl;
    }

    // <-------------------------- Iterative Node Count ----------------------------->
    void itr_count(){
        icount(root);
    }
    
    void icount(Node *root){
        queue <Node *> q;
        Node *temp = root;
        int internal = 0;
        int leaves = 0;
        q.push(root);
        while(!q.empty()){
            temp = q.front();
            q.pop();

            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);
            if(temp->left == NULL && temp->right == NULL)
                leaves++;
            if(temp->left != NULL || temp->right != NULL)
                internal++;
        }
        
        cout<<"\nLeaf nodes are : "<<leaves<<endl;
        cout<<"\nInternal nodes are : "<<internal<<endl;
    }

    // <--------------------------- Iterative Delete ------------------------->
    void itr_delete(){
        idelete(root);
    }

    void idelete(Node *root){
        if(root == NULL)
            return;
        
        queue <Node *> q;
        q.push(root);
        Node *temp;

        while(!q.empty()){
            temp = q.front();
            q.pop();

            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);
            cout<<"Deleting node : "<<temp->data<<endl;
            delete temp;
        }
    }

    // <------------------------ COPY TREE FUNCTION ----------------------->
    void tree_copy(){
        treeCopy(root);
    }
    
    Node* treeCopy(Node *temp){
        if(temp == NULL){
            return NULL;
        }
        Node *p = new Node(temp->data);
        p->left = treeCopy(temp->left);
        p->right = treeCopy(temp->right);
        return p;
    }
};

int BT::leaf = 0;
int BT::internal = 0;

void func(){
    cout<<"\n_____________________________________\n";
    cout<<"\n\t1.Create \n\t2.Insert \n\t3.Display \n\t4.Height \n\t5.Swap \n\t6.Copy \n\t7.Leaves \n\t8.Internal nodes \n\t9.Erase nodes\n\t10.EXIT\n";
    cout<<"_____________________________________\n";
}

int main(){
    BT tree;
    int n = 0;
    int temp = 0;
    int choice = 0;
    cout<<"\n============ BINARY TREE =============\n"<<endl;
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
            tree.call_count();
            tree.display();
        }
        else if(choice == 4){
            cout<<"\n----------------------------------------";
            cout<<"\nHeight of tree is : "<<tree.rheight();
            cout<<"\n----------------------------------------\n";
        }
        else if(choice == 5){
            tree.swapped();
        }
        else if(choice == 6){
            BT copy_tree;
            copy_tree = tree;
            cout<<"\nDisplaying elements of copy tree : ";
            copy_tree.display();
        }
        else if(choice == 7){
            cout<<"---------------------------------------";
            cout<<"\nNumber of leaves are : "<<BT::return_leaf()<<endl;
            cout<<"---------------------------------------\n";
        }
        else if(choice == 8){
            cout<<"---------------------------------------";
            cout<<"\nNumber of internal nodes : "<<BT::return_internal()<<endl;
            cout<<"---------------------------------------------\n";
            }
        else if(choice == 9){
            tree.delete_tree();
        }
        else{
            cout<<"\n========== THANK YOU ===========\n";
            break;
        }
    }

    return 0;
}