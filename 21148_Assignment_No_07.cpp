#include <bits/stdc++.h>
using namespace std;

class Graph {
    int numV;
    int **Matrix;
    int *parent;

    public:

    void GraphCreate(int v){
        numV = v;
        Matrix = new int*[v];
        parent = new int[v];
        for(int i=0; i<v ; i++){
            Matrix[i] = new int[v];
        }
        for(int i=0; i<numV; i++){
            for(int j=0; j<numV; j++){
                Matrix[i][j] = INT_MAX;
            }
        }
    }

    void addEdge(int s, int d, int w){
        Matrix[s][d] = w;
        Matrix[d][s] = w;
    }

    void removeEdge(int s, int d){
        Matrix[s][d] = INT_MAX;
        Matrix[d][s] = INT_MAX;
    }

    void Display(){
        cout<<"\nDisplaying Matrix : "<<endl<<endl;
        for(int i=0; i<numV; i++){
            for(int j=0; j<numV; j++){
                if(Matrix[i][j] == INT_MAX){
                    cout<<0<<"  ";
                }
                else{
                    cout<<Matrix[i][j]<<"  ";
                }
            }
            cout<<endl<<endl;
        }
    }

    bool isValidEdge(int u, int v, vector <bool> inMST){
        if (u == v)
            return false;
        if (inMST[u] == false && inMST[v] == false)
            return false;
        else if (inMST[u] == true && inMST[v] == true)
            return false;
        return true;
    }

    void Prims(){
        vector <bool> inMST(numV, false);
        inMST[0] = true;

        int edgeCount=0, minCost = 0;
        while(edgeCount < numV-1){
            int mini = INT_MAX, a=-1, b=-1;
            for(int i=0; i<numV; i++){
                for(int j=0; j<numV; j++){
                    if(Matrix[i][j] < mini){
                        if(isValidEdge(i,j,inMST)){
                            mini = Matrix[i][j];
                            a = i;
                            b = j;
                        }
                    }
                }
            }
            if(a != -1 && b != -1){
                cout<<"\nEdge "<<edgeCount++<<" | "<<a<<" : "<<b<<" | ";
                cout<<"Cost = "<<mini<<endl;
                minCost += mini;
                inMST[b] = inMST[a] = true;
            }
        }
        cout<<"\nMinimum Cost is : "<<minCost<<endl;
    }

    int find(int i){
        while (parent[i] != i)
            i = parent[i];
        return i;
    }

    void union1(int i, int j){
        int a = find(i);
        int b = find(j);
        parent[a] = b;
    }

    void Kruskals(){
        int mincost = 0;

        for (int i = 0; i < numV; i++)
            parent[i] = i;
 
        int edge_count = 0;
        while (edge_count < numV - 1) {
            int min = INT_MAX, a = -1, b = -1;
            for (int i = 0; i < numV; i++) {
                for (int j = 0; j < numV; j++) {
                    if (find(i) != find(j) && Matrix[i][j] < min) {
                        min = Matrix[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
 
            union1(a, b);
            cout<<"\nEdge "<<edge_count++<<" | "<<a<<" : "<<b<<" | ";
                cout<<"Cost = "<<min<<endl;
            mincost += min;
        }
        cout<<"\nMinimum Cost is : "<<mincost<<endl;
    }
};

void func(){
    cout<<"_________________________________\n\n";
    cout<<"\t1. Create Graph\n\t2. AddEdge\n\t3. RemoveEdge\n\t4. Display\n\t5. Prims MST\n\t6. Kruskals MST\n";
    cout<<"_________________________________\n\n";
}

int main(){
    int choice, u, v, w;
    Graph g;

    cout<<"\n============== MST ==============\n\n";
    func();

    while(true){

        cout<<"\nEnter your choice : ";
        cin>>choice;


        if(choice == 0){
            func();
        }
        else if(choice == 1){
            cout<<"\nEnter number of Vertices : ";
            cin>>u;
            g.GraphCreate(u);
            cout<<endl;
        }
        else if(choice == 2){
            cout<<"__________________________\n";
            cout<<"\nAdding Edge"<<endl;
            cout<<"\nEnter u : ";
            cin>>u;
            cout<<"Enter v : ";
            cin>>v;
            cout<<"Enter weight : ";
            cin>>w;
            g.addEdge(u,v,w);
            cout<<"__________________________\n";
        }
        else if(choice == 3){
            cout<<"__________________________\n";
            cout<<"\nRemoving Edge"<<endl;
            cout<<"\nEnter u : ";
            cin>>u;
            cout<<"Enter v : ";
            cin>>v;
            g.removeEdge(u,v);
            cout<<"__________________________\n";
        }
        else if(choice == 4){
            cout<<"__________________________\n";
            g.Display();
            cout<<"__________________________\n";
        }
        else if(choice == 5){
            cout<<"__________________________\n";
            g.Prims();
            cout<<"__________________________\n";
        }
        else if(choice == 6){
            cout<<"__________________________\n";
            g.Kruskals();
            cout<<"__________________________\n";
        }
        else{
            cout<<"\n========== THANK YOU ==========\n\n";
            break;
        }
    }

    return 0;
}