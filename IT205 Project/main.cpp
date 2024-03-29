#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define M 1000
#define N 10
#define p 5 //p is five minutes

class Node{
public:
    unsigned short int QueueNo;
    unsigned int People;
    Node* next;
};

class QueueManager{
    Node* head = NULL;
    int queue[N];
    Node* flag = NULL;
public:
    QueueManager();
    Node* createList(Node* head, int data, int i);
    void AssignRand();
    void display();
};

//Constructor to assign random values and sort them according the random values
QueueManager::QueueManager (){
    AssignRand();
    Node* head=NULL;
    Node* temp= new Node;
    temp->QueueNo=1;
    temp->People=queue[0];
    temp->next=NULL;
    head=temp;
    
    for(int i=1;i<N;i++){
        head=createList(head, queue[i], i);
    }
    this->head = head;
}

//Function for creating nodes and sorting
Node* QueueManager::createList(Node* head, int data, int i){
    
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
    else{
        while(temp->next!=NULL && temp->next->People<=data){
            temp=temp->next;
        }
        if(temp->next==NULL){
            temp->next=newP;
            newP->next=NULL;
        }
        else{
            newP->next=temp->next;
            temp->next=newP;
        }
        return head;
    }
}

void QueueManager::AssignRand(){
    int range=0;
    srand((unsigned int)time(0));
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
}

void QueueManager::display(){
    Node* temp = head;
    while ( temp ){
        cout<< temp->People << " ";
        temp=temp->next;
    }
    cout<<endl;
}

int main() {
    
    QueueManager q;
    q.display();
        return 0;
}

