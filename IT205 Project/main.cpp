#include <iostream>
#include<cstdlib>
using namespace std;
#define M 10 //M is number of people that are given entry to the stadium
#define N 5 //N is the total number of queues
#define p 5 //p is five minutes
int queue[N]; //queue[N] is an array which stores the number of people in N queues
int n;

//random function is used so that inital random assisgnment of M/2 people can be done
void AssignRand(){
    srand((unsigned int)(time(0)));
    int range=0;
    for ( int i = 0 ; i < N ; i++ ){
        queue[i] = rand() % ( (M/4 + 1) - range );
        range += queue[i];
    }
    //To minimize the number of zeros in random assignment we have used two for loops
    range = 0;
    int stat=0;
    for ( int i = N - 1 ; i > -1 ; i-- ){
        stat = rand() % ( (M/4 + 1) - range );
        queue[i] += stat;
        range += stat;
    }
    //Below code ensures that exactly M/2 poeple are randomly assigned to N queues
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

//By distribute function, uniformity will be maintained in all the queues so time for last person to enter the stadium will be reduced, therby minimizing the time for M people to enter the stadium
void Distribute(){
    int limit = M/N;
    int extra=0;
    for(int i=0;i<N;i++){
        if(queue[i]>limit){
            extra+= (queue[i] - limit);
            queue[i]=limit;
        }
    }
    int data;
    for(int i=0;i<N;i++){
        if(queue[i]<limit){
            data=limit-queue[i];
            if(extra>data){
                queue[i]+=data;
                extra-=data;
            }
            else{
                queue[i]+=extra;
                break;
            }
            if(extra<=0)
                break;
        }
    }
}

//EntryQueueManager suggests people the queue by which they can get into stadium in least time
void entryQueueManager(){
    n=0;
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
        n++;
    }
    cout<<endl;
    cout<<"You can choose from queue number 1 to "<<N<<endl;
}

int main() {
    AssignRand();
    Distribute();
    int q,choice,q2;
    for(int i=0;i<(M/2 + M%2);i++){
        cout<<"Suggestions by entry queue manager:"<<endl;
        entryQueueManager();
        while(1){
            cout<<"Enter the queue number you want to join: ";
            cin>>q;
            if(q>0 && q<N+1){
                queue[q-1]++;
                break;
            }
            else{
                cout<<"Invalid queue number, enter correctly again!"<<endl;
            }
        }
        cout<<"You are now in queue no. "<< q <<endl;
        cout<<"Choose"<<endl;
        cout<<"1.If you want to switch from your current queue"<<endl;
        cout<<"2.If you are satisfied with your current queue"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                if(n==1){
                    cout<<"You don't have choice to switch as we only 1 queue"<<endl;
                }
                else{
                    entryQueueManager();
                    while(1){
                        cout<<"Enter the queue number you want to switch to: ";
                        cin>>q2;
                        if(q2>0 && q2<N+1){
                            queue[q2-1]++;
                            break;
                        }
                        else{
                            cout<<"Invalid queue number, enter correctly again!"<<endl;
                        }
                    }
                    queue[q-1]--;
                    cout<<"You are now in queue no. "<< q2 <<endl;
                }
                break;
            case 2:
                break;
            default:
                cout<<"Invalid choice, so default is that you are satisfied with your current queue"<<endl;
        }
        if(i==(M/2-1)+(M%2))
            cout<<"Now all persons are arranged in the queues"<<endl;
        else
            cout<<"Now, enter next person"<<endl<<endl;
    }
    
        return 0;
}
