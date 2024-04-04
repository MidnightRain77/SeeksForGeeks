#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <utility>
#include <deque>
#include <vector>
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
        return duration_cast<minutes>(high_resolution_clock::now()-start).count();
    }
};

int countPeepsLeft(int queue[]){
    int left = 0;
    for ( int i = 0 ; i < N ; i++ )
        left += *(queue + i);
    return left;
}

//Returns the hashed value
int hashFunction(int i){
    return ( i % (M/8) );
}

//Initializes the pair
void createSerialNo ( pair<int, pair<bool, short int>> (&SerialNo)[N] ){
    for ( int i = 0 ; i < M ; i++ ){
        SerialNo[i].first = 1000000 + i;
        SerialNo[i].second.second = 0;
        if ( !hashFunction(i) ){
            SerialNo[i].second.first = true;
        }
        else{
            SerialNo[i].second.first = false;
        }
    }
}

//Function to automatically dequeue people into the stadium
void autodequeue(int* queue){
    this_thread::sleep_for(minutes(p));
    if ( countPeepsLeft(queue) ){
        for ( int i = 0 ; i < N ; i++ ){
            if ( *(queue + i) ){
                (*(queue + i))--;
            }
        }
        autodequeue(queue);
    }
    else
        return;
}

//Function to randomly assign M/2 people to the entry gates
void Assign_to_Random_Gate(int* queue, pair<int, pair<bool, short int>> (&SerialNo)[N], deque<int> (&SerialNo_Queue)[N]){
    srand((unsigned int)(time(0)));
    for ( int i = 0 ; i < M ; i++ ){
        int gate = rand() % N;
        queue[gate]++;
        int serial;
        do{
            serial = rand() % M;
        }while( !SerialNo[serial].second.second );
        SerialNo_Queue[gate].push_front(SerialNo[serial].first);
        SerialNo[serial].second.second = 1;
    }
}

//Function to minimize the time for entry of the first M/2 randomly assigned people
void Distribute(int* queue, deque<int> (&SerialNo_Queue)[N]){
    int limit = M/N;
    int extra = 0, data, shift;
    vector <int> reshuff;
    for ( int i = 0 ; i < N ; i++ ){
        if ( *(queue + i) > limit ){
            shift = *(queue + i) - limit;
            extra += shift;
            *(queue + i) = limit;
            while ( shift ){
                reshuff.push_back(SerialNo_Queue[i].front());
                SerialNo_Queue[i].pop_front();
                shift--;
            }
        }
    }
    for ( int i = 0 ; i < N ; i++ ){
        if ( *(queue + i) < limit ){
            data = limit - *(queue + i);
            if ( extra > data ){
                *(queue + i) += data;
                extra -= data;
                while ( data ){
                    SerialNo_Queue[i].push_front(reshuff.back());
                    reshuff.pop_back();
                    data--;
                }
            }
            else{
                *(queue + i) += extra;
                while ( extra ){
                    SerialNo_Queue[i].push_front(reshuff.back());
                    reshuff.pop_back();
                    extra--;
                }
                break;
            }
            if( extra <= 0 )
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
    int queue[N], x = 0;
    pair<int, pair<bool, short int>> SerialNo[N];
    deque<int> SerialNo_Queue[N];
    createSerialNo(SerialNo);
    Assign_to_Random_Gate(queue, SerialNo, SerialNo_Queue);
    Distribute(queue, SerialNo_Queue);
    for ( int i = 0 ; i < N ; i++ ){
        cout<<queue[i]<<" ";
    }
    cout<<endl<<endl;
    Stopwatch stat;
    thread t(autodequeue, queue);
    t.detach();
    int q, choice, q2;
    for(int i=0;i<( M / 2 + M  % 2 );i++){
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
        if(i==(M/2-1)+(M%2)){
            cout<<"The stadium is full!"<<endl;
        }
        else
            cout<<"Moving onto the next person..."<<endl<<endl;
    }
    do{
        x=0;
        for(int i=0;i<N;i++){
            x+=queue[i];
        }
    }while(x!=0);
    cout<<"Total time: "<<stat.ElapsedMinutes()<<endl;
        return 0;
}
