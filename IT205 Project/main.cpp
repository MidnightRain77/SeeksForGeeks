#include <iostream>
#include<cstdlib>
#include <chrono>
using namespace std::chrono;
using namespace std;
const int M = 20; //Capacity of the stadium
const int N = 5; //Number of entry gates
const int p = 1; //mins it takes for a single attendee to enter any gate

//Calculate the time passed since the opening of entry gates
class Stopwatch{
    time_point <high_resolution_clock> start;
public:
    Stopwatch() : start(high_resolution_clock::now()){}
    
    long ElapsedMinutes(){
        return duration_cast<seconds>(high_resolution_clock::now()-start).count();
    }
};

//Function to randomly assign M/2 people to the entry gates
void AssignRand(int queue[]){
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
    //Ensuring that exactly M/2 poeple are assigned
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

//Function to minimize the time for entry of the first M/2 randomly assigned people
void Distribute(int queue[]){
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

//Function to suggest the least waiting time
void entryQueueManager(int queue[]){
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
    cout<<"You can choose from queue number 1 to "<<N<<endl;
}

int main() {
    int queue[N];
    AssignRand(queue);
    Distribute(queue);
    Stopwatch stat;
    int q, choice, q2;
    for(int i=0;i<(M/2 + M%2);i++){
        cout<<"Suggestions by entry queue manager:"<<endl;
        entryQueueManager(queue);
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
                if(N==1){
                    cout<<"You don't have choice to switch as we only 1 queue"<<endl;
                }
                else{
                    entryQueueManager(queue);
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
                cout<<"Invalid choice! So by default option 2 is selected..."<<endl;
        }
        cout<<"Time elapsed: "<<stat.ElapsedMinutes();
        if(i==(M/2-1)+(M%2)){
            cout<<"The stadium is full!"<<endl;
            cout<<"Total time: "<<stat.ElapsedMinutes()<<endl;
        }
        else
            cout<<"Moving onto the next person..."<<endl<<endl;
    }
        return 0;
}
