#include <iostream>
#include <queue>
using namespace std;

class Node {
    int key;
    string value;
    int height;
    Node* left;
    Node* right;

    public:

    Node(){
        key = 0;
        height = 1;
        value = "";
        left = right = NULL;
    }

    Node(int k, string v){
        key = k;
        height = 1;
        value = v;
        left = right = NULL;
    }

    friend class AVL;
};

class AVL {

    public:

    Node *root;

    AVL(){
        root = NULL;
    }

    int height(Node *node){
        if(node == NULL) return 0;
        else return node->height;
    }

    int balanceFactor(Node *node){
        if(node == NULL) return 0;
        else return (height(node->left) - height(node->right));
    }

    void updateHeight(Node* node){
        node->height = 1 + max(height(node->left), height(node->right));
    }

    Node *rotateLeft(Node *node){
        Node *temp = node->right;
        node->right = temp->left;
        temp->left = node;
        updateHeight(node);
        updateHeight(temp);
        return temp;
    }

    Node *rotateRight(Node *node){
        Node *temp = node->left;
        node->left = temp->right;
        temp->right = node;
        updateHeight(node);
        updateHeight(temp);
        return temp;
    }

    Node *rotateLeftRight(Node *node){
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    Node *rotateRightLeft(Node *node){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    Node *balance(Node *node){
        if(balanceFactor(node) == 2){
            if(balanceFactor(node->left) < 0){
                node = rotateLeftRight(node);
            }
            else{
                node = rotateRight(node);
            }
        }
        else if (balanceFactor(node) == -2){
            if(balanceFactor(node->right) > 0){
                node = rotateRightLeft(node);
            }   
            else{
                node = rotateLeft(node);
            }
        }
        updateHeight(node);
        return node;
    }

    void insert(int key, string value){
        root = addNode(root, key, value);
    }

    Node* addNode(Node *node, int key, string value){
        if (node == nullptr){
            return new Node(key, value);
        }
        if (key < node->key){
            node->left = addNode(node->left, key, value);
        }
        else if (key > node->key){
            node->right = addNode(node->right, key, value);
        }
        else{
            node->value = value; 
            return node;
        }
        return balance(node);
    }

    bool search(Node *node, int key){
        if(node == NULL) return false;
        if(key < node->key) return search(node->left, key);
        else if(key > node->key) return search(node->right, key);
        else return true;
    }

    void inorderTraversal(Node* node){
        if (node == nullptr) return;
        inorderTraversal(node->left);
        cout << node->key << " : " << node->value << " >> ";
        inorderTraversal(node->right);
    }

    void preorderTraversal(Node *node){
        if (node == nullptr) return;
        cout << node->key << " : " << node->value << " >> ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    } 

    void levelorderTraversal(Node *node){
        queue <Node *> q;
        Node *p = root;
        q.push(p);
        while(!q.empty()){
            p = q.front();
            q.pop();
            cout<<p->key<<" : "<<p->value<<" >> ";
            if(p->left) q.push(p->left);
            if(p->right) q.push(p->right);
        }
        cout<<endl;
    }
};

void func(){
    cout<<"_________________________________\n\n";
    cout<<"\t1. Insert\n\t2. Display\n\t3. LevelOrder\n\t4. EXIT\n";
    cout<<"_________________________________\n\n";
}

int main(){
    AVL a;
    int choice, key;
    string value;

    cout<<"\n================ AVL TREE ================\n\n";
    func();

    while(true){
        cout<<"\nEnter choice : ";
        cin>>choice;

        if(choice == 0) func();
        else if(choice == 1){
            cout<<"\nEnter Key : ";
            cin>>key;
            cout<<"Enter Value : ";
            cin>>value;
            a.insert(key,value);
        }
        else if(choice == 2){
            cout<<"\n_____________________________________________\n\n";
            a.inorderTraversal(a.root);
            cout<<"\n_____________________________________________\n\n";
            a.preorderTraversal(a.root);
            cout<<"\n_____________________________________________\n\n";            
        }
        else if(choice == 3){
            cout<<"\n_____________________________________________\n\n";
            a.levelorderTraversal(a.root);
            cout<<"_____________________________________________\n\n";
        }
        else{
            cout<<"\n============ THANK YOU ============\n\n";
            break;
        }
    }

    return 0;
}