#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define M 10000
#define N 30
#define p 5 //p is five minutes
int queue[N];

class Node{
public:
    unsigned short int QueueNo;
    unsigned int People;
    Node* next;
};

class QueueManager{
    Node* head;
public:
    QueueManager();
};

//QueueManager::QueueManager (){
//    int range=0;
//    srand(time(0));
//    for ( int i = 1 ; i < N + 1 ; i++ ){
//        Node* t = new Node;
//        t->QueueNo = i;
//
//    }
//}

Node* createList(Node* head, int data, int i){
    
    Node* temp=NULL;
    temp=head;
    Node* newP=new Node;
    newP->People=data;
    newP->QueueNo=i+1;
    if(data<=head->People){
        newP->next=head;
        head=newP;
        return head;
    }
    else
    {
        while(temp->next!=NULL && temp->next->People<=data){
            temp=temp->next;
        }
        if(temp->next==NULL){
            temp->next=newP;
            newP->next=NULL;
        }
        else
        {
            newP->next=temp->next;
            temp->next=newP;
        }
        return head;
    }
}


void AssignRand(){
    int range=0;
    srand(time(0));
    for ( int i = 0 ; i < N ; i++ ){
        queue[i] = rand() % ( (M/4 + 1) - range );
        range += queue[i];
    }
    range = 0;
    int stat=0;
    for ( int i = N - 1 ; i > -1 ; i-- ){
        stat = rand() % ( (M/4 + 1) - range );
        queue[i] += stat;
        range += stat;
    }
    
    Node* head=NULL;
    Node* temp= new Node;
    temp->QueueNo=1;
    temp->People=queue[0];
    temp->next=NULL;
    head=temp;
    
    for(int i=1;i<N;i++){
        
        head=createList(head, queue[i], i);
    }
    Node* temp3=head;
    while(temp3){
        cout<< temp3->QueueNo << " " << temp3->People<< endl;
        temp3=temp3->next;
    }
}

void entryQueueManager(){
    int min = queue[0];
    for ( int i = 1 ; i < N ; i++ ){
        if ( queue[i] < min )
            min = queue[i];
    }
    cout<<"Least waiting time is: "<< p*min <<" minutes"<<endl;
    cout<<"Following queue numbers have the least waiting time as of now:"<<endl;
    for ( int i = 0 ; i < N ; i++ ){
        if ( min == queue[i] )
            cout<<i+1<<" ";
    }
    cout<<endl;
}

int main() {
    AssignRand();
    while(1){
        cout<<"Choose one of the following:"<<endl;
        cout<<"1. You know what queue to join."<<endl;
        cout<<"2. You want to use the entry queue manager to help you decide."<<endl;
        cout<<"3. You want to change your current queue and need the help of entry manager."<<endl;
        cout<<"4. You want to change your current queue and already know which queue to shift to."<<endl;
        cout<<"5. Exit."<<endl;
        char option;
        int q, o;
        cin>>option;
        switch(option){
            case '1':
                cout<<"Enter the queue number you want to join: ";
                cin>>q;
                queue[q-1]++;
                cout<<"You are now in queue no. "<<q<<endl;
                break;
            case '2':
                entryQueueManager();
                cout<<"Enter the queue number you want to join: ";
                cin>>q;
                queue[q-1]++;
                cout<<"You are now in queue no. "<<q<<endl;
                break;
            case '3':
                cout<<"Enter the queue number you're currently in: ";
                cin>>o;
                entryQueueManager();
                cout<<"Enter the queue number you want to join: ";
                cin>>q;
                queue[q-1]++;
                queue[o-1]--;
                cout<<"You are now in queue no. "<<q<<endl;
                break;
            case '4':
                cout<<"Enter the queue number you're currently in: ";
                cin>>o;
                cout<<"Enter the queue number you want to join: ";
                cin>>q;
                queue[q-1]++;
                queue[o-1]--;
                cout<<"You are now in queue no. "<<q<<endl;
                break;
            case '5':
                exit(0);
            default:
                cout<<"Invalid Option!"<<endl;
        }
    }
        return 0;
}
