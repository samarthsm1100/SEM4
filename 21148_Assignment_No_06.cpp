#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

class Node
{
    int data;
    Node *next;

    public:

    Node(){
        data = -1;
        next = NULL;
    }

    Node(int d){
        data = d;
        next = NULL;
    }

    friend class Graph;
};

class Graph
{
    Node **Head, *srcNode, *frontNode;
    int numVertices;
    queue <int> q;
    stack <int> st;
    bool *visited;

    public:

    Graph(int v){
        numVertices = v;
        Head = new Node*[v];
        visited = new bool[v];
        for(int i=0; i<v; i++){
            Head[i] = new Node(i);
            visited[i] = false;
        }
    }

    void Insert(int s, int d){
        Node *temp = new Node(d);
        Node *itr = Head[s];
        while(itr->next != NULL){
            itr = itr->next;
        }
        itr->next = temp;
    }

    void Display(){
        int v = numVertices;
        for (int i = 0; i < v; i++)
        {
            cout << i << "--->";
            Node *temp = Head[i];
            temp = temp->next;
            while(temp != NULL){
                cout<<temp->data<<" ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    void BFS(int s){
        srcNode = Head[s];
        frontNode = srcNode;
        q.push(frontNode->data);

        cout<<"BFS Search : ";
        while(!q.empty()){
            frontNode = Head[q.front()];
            if(!visited[frontNode->data])
                cout<<frontNode->data<<" ";
            visited[frontNode->data] = true;
            q.pop();
            frontNode = frontNode->next;
            while(frontNode){
                if(!visited[frontNode->data]){
                    q.push(frontNode->data);
                }
                frontNode = frontNode->next;
            } 
        }
        cout<<endl;
        for(int i=0;i<numVertices; i++){
            visited[i] = false;
        }
    }

    void DFS(int s){
        srcNode = Head[s];
        frontNode = srcNode;
        st.push(frontNode->data);

        cout<<"DFS Search : ";
        while(!st.empty()){
            frontNode = Head[st.top()];
            if(!visited[frontNode->data])
                cout<<frontNode->data<<" ";
            visited[frontNode->data] = true;
            st.pop();
            frontNode = frontNode->next;
            while(frontNode){
                if(!visited[frontNode->data]){
                    st.push(frontNode->data);
                }
                frontNode = frontNode->next;
            }
        }
        cout<<endl;
        for(int i=0;i<numVertices; i++){
            visited[i] = false;
        }
    }
    
};

void func(){
    cout<<"___________________________\n\n";
    cout<<"\t1. Insert\n\t2. Display\n\t3. BFS\n\t4. DFS\n";
    cout<<"___________________________\n\n";
}

int main() {
   int choice, src, dest;
   cout<<"\n============ GRAPH ============\n\n";
   cout<<"\nEnter number of nodes in graph : ";
    int temp;
    cin>>temp;
    Graph g(temp);
   cout<<"\n<-----------  MENU  ---------->\n";
   func();

   while(true){
    cout<<"\nEnter your choice : ";
    cin>>choice;

    if(choice == 0){
        func();
    }
    else if(choice == 1){
        cout<<"\nEnter Source : ";
        cin>>src;
        cout<<"Enter Destination : ";
        cin>>dest;
        g.Insert(src,dest);
    }
    else if(choice == 2){
        cout<<"<-------- ADJ LIST REPRESENTATION ------->\n\n";
        g.Display();
    }
    else if(choice == 3){
        cout<<"\nEnter source to start BFS : ";
        cin>>src;
        g.BFS(src);
    }
    else if(choice == 4){
        cout<<"Enter source to start DFS : ";
        cin>>src;
        g.DFS(src);
    }
    else{
        cout<<"\n======= THANK YOU =======\n\n";
        break;
    }
   }
   return 0;
}