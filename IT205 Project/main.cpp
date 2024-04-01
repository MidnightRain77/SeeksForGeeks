#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define M 10000
#define N 100
#define p 5 //p is five minutes

//Class to store data of each queue
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
    QueueManager();//Constructor
    Node* createList(Node* var, int data, int i);
    void AssignRand();
    void display();
    void EntryManager(Node* var);
    void findFlag();
    Node* getHead();
    void EntryQueueManager();
    void Suggestions();
    unsigned int findPeople(int choice);
    void enqueuePeople(unsigned short int Q);
    void dequeuePeople(unsigned short int Q);
    void sort(Node* temp, Node* tail);
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
    findFlag();
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

//Function to get head pointer
Node* QueueManager::getHead(){
    return head;
}

//Function to generate random values
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

//Function to find the node from which onwards I start shifting people
void QueueManager::findFlag(){
    flag = head;
    while(flag && ((flag->People)<(M/N))){
        flag=flag->next;
    }
}

//Function to display the no of people in each queue
void QueueManager::display(){
    Node* temp = head;
    while ( temp ){
        cout<< temp->QueueNo<<"->"<< temp->People <<"  ";
        temp=temp->next;
    }
    cout<<endl;
}

//Function to shift the randomly assigned people, recursively,
//to minimize total entry time
void QueueManager::EntryManager(Node* temp){
    while ( temp->next && temp->People == temp->next->People )
        temp = temp->next;
    
    unsigned int limit;
    limit = temp->next?temp->next->People:temp->People;
    
    while (flag && flag->People - M/N && temp->People!=limit ){
        flag->People--;
        temp->People++;
    }
    //while ended due to second condition
    if (flag && temp->People!=limit ){
        if ( flag->next ){
            flag = flag->next;
            EntryManager(temp);
        }
        else{
            return;
        }
    }
    //while ended due to third condition
    else if (flag && flag->People - M/N){
        if ( flag ){
            EntryManager(head);
        }
        else{
            return;
        }
    }
    //while ended due to both second and third condition
    else if ( flag && flag->next ){
        flag = flag->next;
        EntryManager(head);
    }
}

//Sort after dequeue or enqueue
void QueueManager::sort(Node* temp, Node* tail){
    Node* temp2 = temp;
    while ( tail && temp2->next && temp2->People <= temp->People )
        temp2 = temp2->next;
    if ( tail ){
        if ( temp2->next ){
            tail->next = temp->next;
            temp->next = temp2->next;
            temp2->next = temp;
        }
        else if (tail){
            tail->next = temp->next;
            temp->next = NULL;
            temp2->next = temp;
        }
    }
    
    else if ( temp2->next ){
        head = temp->next;
        temp->next = temp2->next;
        temp2->next = temp;
    }
}

//Function to suggest the minimum waiting time
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
    else if ( temp )
        cout<<temp->QueueNo<<" ";
    cout<<endl;
}

//Function to enqueue people
void QueueManager::enqueuePeople(unsigned short int Q){
    Node* temp = head;
    Node* tail = NULL;
    while ( temp && temp->QueueNo != Q ){
        tail = temp;
        temp = temp->next;
    }
    temp->People++;
    sort(temp, tail);
}

//Function to dequeue people
void QueueManager::dequeuePeople(unsigned short int Q){
    Node* temp = head;
    Node* tail = NULL;
    while ( temp && temp->QueueNo != Q ){
        tail = temp;
        temp = temp->next;
    }
    if ( temp )
        return;
    temp->People--;
    sort(temp, tail);
}

//Entry queue manager after the M/2 peeps are settled in
void QueueManager::EntryQueueManager(){
    unsigned short int q, choice, q2;
    for(int i=0;i<M/2;i++){
        cout<<"Suggestions by entry queue manager:"<<endl;
        Suggestions();
        while(1){
            cout<<"Enter the queue number you want to join(1 to "<<N<<"): ";
            cin>>q;
            if(q>0 && q<N+1){
                enqueuePeople(q);
                break;
            }
            else{
                cout<<"Invalid queue number, enter correctly again!"<<endl;
            }
        }
        cout<<"You are now in queue no. "<< q <<endl;
        cout<<"Choose"<<endl;
        cout<<"1. If you want to switch from your current queue"<<endl;
        cout<<"2. If you are satisfied with your current queue"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                Suggestions();
                while(1){
                    cout<<"Enter the queue number you want to join(1 to "<<N<<"): ";
                    cin>>q;
                    if(q>0 && q<N+1){
                        enqueuePeople(q);
                        break;
                    }
                    else{
                        cout<<"Invalid queue number, enter correctly again!"<<endl;
                    }
                }
                dequeuePeople(q);
                cout<<"You are now in queue no. "<< q2 <<endl;
                break;
            case 2:
                break;
            default:
                cout<<"Invalid choice! So by default option 2 is selected..."<<endl;
        }
        if ( i == M/2 - 1 )
            cout<<"The stadium is full..."<<endl<<endl;
        else{
            cout<<"Moving onto the next person..."<<endl<<endl;
        }
    }
}

int main(){
    QueueManager q;
    q.display();
    cout<<endl<<endl;
    q.EntryManager(q.getHead());
    q.EntryQueueManager();
    return 0;
}
