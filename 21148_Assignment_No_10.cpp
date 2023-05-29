#include <bits/stdc++.h>
#define size 100
using namespace std;

class Heap{
    int arr[size],n;

    public:

    Heap(){}

    void Create(){
        cout<<"\nEnter number of elements : ";
        cin>>this->n;
    }

    void Insert(){
        cout<<"__________________________________________\n";
        cout<<"\nEnter Elements : ";
        for(int i=0; i<n; i++){
            cin>>arr[i];
        }
        cout<<endl;
        cout<<"__________________________________________\n\n";
    }

    void Heapify(int n, int i){
        int l = 2*i+1;
        int r = 2*i+2;
        int large = i;
        if(l<n && arr[l]>arr[i]){
            large = l;
        }
        if(r<n && arr[r]>arr[large]){
            large = r;
        }
        if(large != i){
            swap(arr[i],arr[large]);
            Heapify(n, large);
        }
    }

    void BuildHeap(){
        for(int i=(n/2)-1; i>=0; i--){
            Heapify(n,i);
        }
    }

    void HeapSort(){
        BuildHeap();
        for(int i=n-1; i>=0; i--){
            swap(arr[0],arr[i]);
            Heapify(i,0);
        }
    }

    void Display(){
        cout<<"__________________________________________\n";
        cout<<"\nAfter HeapSort : ";
        for(int i=0; i<n; i++){
            cout<<arr[i]<<"  ";
        }
        cout<<endl;
        cout<<"___________________________________________\n\n";
    }
};

void func()
{
    cout << "___________________________\n\n";
    cout << "\t1. Create\n\t2. Insert\n\t3. HeapSort\n\t4. Exit\n";
    cout << "___________________________\n\n";
}

int main(){
    int choice,temp;
    Heap h;

    cout<<"\n========= HEAP SORT ==========\n\n";
    func();

    while(true){

        cout<<"\nEnter choice : ";
        cin>>choice;

        if(choice == 0) func();
        else if(choice == 1){
            h.Create();
        }
        else if(choice == 2){
            h.Insert();
        }
        else if(choice == 3){
            h.HeapSort();
            h.Display();
        }
        else{
            cout<<"\n======== THANK YOU ========\n";
            break;
        }
    }

    return 0;
}