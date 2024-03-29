#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define M 100
#define N 20
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
    Node* createList(Node* var, int data, int i);
    void AssignRand();
    void display();
    void EntryManager(Node* var);
    void findFlag();
    Node* getHead();
    void Suggestions();
};

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
    findFlag();
}

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

Node* QueueManager::getHead(){
    return head;
}

void QueueManager::AssignRand(){
    srand((unsigned int)(time(0)));
    int range=0;
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
    int data=0;
    for(int i=0;i<N;i++){
        data+=queue[i];
    }
    if(data!=M/2){
        if(data<M/2){
            queue[0]+=(M/2-data);
        }
        else{
            queue[0]+=(data-M/2);
        }
    }
}

void QueueManager::findFlag(){
    flag = head;
    while(flag && ((flag->People)<(M/N))){
        flag=flag->next;
    }
}

void QueueManager::display(){
    Node* temp = head;
    while ( temp ){
        cout<< temp->QueueNo<<"->"<< temp->People <<"  ";
        temp=temp->next;
    }
    cout<<endl;
}

void QueueManager::EntryManager(Node* temp){
    while ( temp->People == temp->next->People )
        temp = temp->next;
    
    unsigned int limit = temp->next->People;
    
    while (flag && flag->People - M/N && temp->People!=limit ){
        flag->People--;
        temp->People++;
    }
    if (flag && temp->People!=limit ){
        if ( flag->next ){
            flag = flag->next;
            EntryManager(temp);
        }
        else{
            return;
        }
    }
    else if (flag && flag->People - M/N){
        if ( flag ){
            EntryManager(head);
        }
        else{
            return;
        }
    }
    else if ( flag && flag->next ){
        flag = flag->next;
        EntryManager(head);
    }
}

void QueueManager::Suggestions(){
    Node* temp = head;
    cout<<"Least waiting time is: "<< p*head->People <<" minutes"<<endl;
    cout<<"Following queue numbers have the least waiting time as of now:"<<endl;
    while ( temp->next && temp->People == temp->next->People ){
        cout<<temp->QueueNo<<" ";
        temp = temp->next;
    }
    
    if ( temp->next )
        cout<<temp->QueueNo<<" ";
    cout<<endl;
}

int main(){
    QueueManager q;
    q.display();
    cout<<endl<<endl;
    q.EntryManager(q.getHead());
    q.display();
    cout<<endl<<endl;
    return 0;
}

