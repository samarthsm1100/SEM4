#include <iostream>
#define size 10
#define ll long long int
using namespace std;

class Data{
    public:

    ll tele;
    string name;

    Data(){
        tele = 0;
        name = "undefined";
    }

    Data(int t, string s){
        tele = t;
        name = s;
    }
};

class Hash{
    Data arr[size];
    int count;

    public:

    int without = 0, with = 0;

    Hash(){
        count = 0;
    }

    int HashIt(ll key){
        return key%size;
    }

    void Insert(ll num, string name){
        if(count >= size){
            cout<<"\nHash Table is FULL"<<endl;
            return;
        }
        int hashIndex = HashIt(num);
        int hashIndexCopy = hashIndex;
        do{
            if(arr[hashIndex].tele == 0){
                arr[hashIndex].tele = num;
                arr[hashIndex].name = name;
                count++;
                break;
            }
            else{
                hashIndex = (hashIndex+1)%size;
            }
            without++;
        }while(hashIndexCopy != hashIndex);
    }

    void RInsert(ll num, string name){
        if(count >= size){
            cout<<"\nHash Table is FULL"<<endl;
            return;
        }
        int hashIndex = HashIt(num);
        int hashIndexCopy = hashIndex;
        do{
            if(arr[hashIndex].tele == 0){
                arr[hashIndex].tele = num;
                arr[hashIndex].name = name;
                count++;
                break;
            }
            else{
                int hashIndexOfCollision = HashIt(arr[hashIndex].tele);
                if(hashIndex != hashIndexOfCollision && hashIndex == hashIndexCopy){
                     ll teleCollision = arr[hashIndex].tele;
                     string nameCollison = arr[hashIndex].name;

                     arr[hashIndex].tele = num;
                     arr[hashIndex].name = name;

                     RInsert(teleCollision, nameCollison);
                     break;
                }
                else{
                    hashIndex = (hashIndex + 1)%size;
                }
            }
            with++;
        }while(hashIndexCopy != hashIndex);
    }

    void Display(){
        cout<<endl<<endl;
        for(int i=0; i<10; i++){cout<<char(6);}
        cout<<" HASH TABLE ";
        for(int i=0; i<10; i++){cout<<char(6);}
        cout<<endl<<endl;
        for(int i=0; i<size; i++){
            if(arr[i].tele != 0)
            cout<<i<<" - "<<arr[i].name<<" : "<<arr[i].tele<<endl;
        }
        cout<<"________________________________\n";
        cout<<endl;
    }

    bool Search(ll num){
        int hashIndex = HashIt(num);
        int hashIndexCopy = hashIndex;
        do{
            if(arr[hashIndex].tele == num){
                return true;
            }
            hashIndex = (hashIndex+1)%size;
        }while( hashIndex != hashIndexCopy);
        return false;
    }

    void Delete(ll num){
        bool flag = Search(num);
        if(!flag){
            cout<<"\nNot present in Hash Table"<<endl;
            return;
        }
        int hashIndex = HashIt(num);
        int hashIndexCopy = hashIndex;
        do{
            if(arr[hashIndex].tele == num){
                arr[hashIndex].tele = 0;
                count--;
                break;
            }
            else{
                hashIndex = (hashIndex+1)%size;
            }
        }while(hashIndexCopy != hashIndex);
    }
};

void func(){
    cout<<"\n__________________________________________\n";
    cout<<"\n\t1.Insert without replacement\n\t2.Insert with replacement\n";
    cout<<"__________________________________________\n";
}

void menu(){
    cout<<"\n__________________________________________\n";
    cout<<"\n\t1.Insert\n\t2.Delete\n\t3.Display\n\t4.Search\n\t5.EXIT\n";
    cout<<"__________________________________________\n";
}

void InsertWith(Hash &H, int arr[], string names[], int n){
    int choice;
    ll temp;
    string name;

    for(int i=0; i<n; i++){
        H.RInsert(arr[i],names[i]);
    }

    cout<<"\n\tWith Replacement";
    menu();

    while(true){    

        cout<<endl<<char(4)<<" Enter choice in MENU : ";
        cin>>choice;

        if(choice == 0){
            menu();
        }
        else if(choice == 1){
            cout<<"\n------------------------";
            cout<<"\nEnter Telephone Number : ";
            cin>>temp;
            cout<<"Enter name : ";
            cin>>name;
            cout<<"------------------------\n";
            H.RInsert(temp,name);
        }
        else if(choice == 2){
            cout<<"\n------------------------";
            cout<<"\nEnter element to delete : ";
            cin>>temp;
            cout<<"------------------------\n";
            H.Delete(temp);
        }
        else if(choice == 3){         
            cout<<"\n\tWith Replacement";
            H.Display();
        }
        else if(choice == 4){
            cout<<"\n----------------------------";
            cout<<"\nEnter element to search : ";
            cin>>temp;
            if(H.Search(temp)){
                cout<<"\n"<<char(5)<<" Element "<<temp<<" is present"<<endl;
            }
            else{
                cout<<"\n"<<char(5)<<" Element is absent"<<endl;
            }
            cout<<"----------------------------\n";
        }
        else{
            break;
        }
    }
}

void InsertWithout(Hash &H, int arr[], string names[], int n){
    int choice;
    ll temp;
    string name;

    for(int i=0; i<n; i++){
        H.Insert(arr[i],names[i]);
    }

    cout<<"\n\tWithout Replacement";    
    menu();

    while(true){    
        cout<<endl<<char(4)<<" Enter choice in MENU : ";
        cin>>choice;

        if(choice == 0){
            func();
        }
        else if(choice == 1){
            cout<<"\n------------------------";
            cout<<"\nEnter Telephone Number : ";
            cin>>temp;
            cout<<"Enter name : ";
            cin>>name;
            cout<<"------------------------\n";
            H.Insert(temp,name);
        }
        else if(choice == 2){
            cout<<"\n------------------------";
            cout<<"\nEnter element to delete : ";
            cin>>temp;
            cout<<"------------------------\n";
            H.Delete(temp);
        }
        else if(choice == 3){         
            cout<<"\n\tWithout Replacement";    
            H.Display();
        }
        else if(choice == 4){
            cout<<"\n----------------------------";
            cout<<"\nEnter element to search : ";
            cin>>temp;
            if(H.Search(temp)){
                cout<<"\n"<<char(5)<<" Element "<<temp<<" is present"<<endl;
            }
            else{
                cout<<"\n"<<char(5)<<" Element is absent"<<endl;
            }
            cout<<"----------------------------\n";
        }
        else{
            break;
        }
    }
}

int main(){
    Hash H1,H2;
    int choice;
    ll temp;
    string name;

    cout<<"\n=============== HASH ================\n"<<endl;
    
    cout<<"\nEnter number of elements : ";
    cin>>choice;
    cout<<endl;
    int arr[choice];
    string names[choice];
    for(int i=0;i<choice;i++){
        cout<<"Enter Telephone Number : ";
        cin>>arr[i];
        cout<<"Enter Name : ";
        cin>>names[i];
        cout<<endl;
    }

    InsertWith(H1, arr, names, choice);
    InsertWithout(H2, arr, names, choice);

    cout<<"\n\t---- Comparisons ----\n";
    cout<<"\nInsertion With Replacement : "<<H1.with<<endl;
    cout<<"\nInsertion Without Replacment : "<<H2.without<<endl;

    cout<<"\n\n========== THANK YOU ===========\n";

    return 0;
}