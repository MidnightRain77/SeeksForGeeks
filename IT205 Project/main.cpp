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

//Function to check if the serial number is a VIP
int hashFunction(int Serial_No){
    return ( !Serial_No % (M/8) ) ? 1 : 0;
}

//Initializes the pair
void createSerialNo ( pair<short int, int> (&SerialStat)[N] ){
    for ( int i = 0 ; i < M ; i++ ){
        SerialStat[i].first = 0;
    }
}

//Function to randomly assign M/2 people to the entry gates
void Assign_to_Random_Gate( pair<short int, int> (&SerialStat)[N], deque<int> (&Queue)[N]){
    srand((unsigned int)(time(0)));
    for ( int i = 0 ; i < M ; i++ ){
        int gate = rand() % N;
        int serial;
        do{
            serial = rand() % M;
        }while( !SerialStat[serial].first );
        Queue[gate].push_front(serial);
        SerialStat[serial].first = 1;
    }
}

//Function to minimize the time for entry of the first M/2 randomly assigned people
void Distribute( deque<int> (&Queue)[N] ){
    long limit = M/N, extra = 0, data, shift;
    vector <int> reshuff;
    for ( int i = 0 ; i < N ; i++ ){
        if ( Queue[i].size() > limit ){
            shift = Queue[i].size() - limit;
            extra += shift;
            while ( shift ){
                reshuff.push_back(Queue[i].front());
                Queue[i].pop_front();
                shift--;
            }
        }
    }
    for ( int i = 0 ; i < N ; i++ ){
        if ( Queue[i].size() < limit ){
            data = limit - Queue[i].size();
            if ( extra > data ){
                extra -= data;
                while ( data ){
                    Queue[i].push_front(reshuff.back());
                    reshuff.pop_back();
                    data--;
                }
            }
            else{
                while ( extra ){
                    Queue[i].push_front(reshuff.back());
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

//Counts the total number of people waiting in the queue
long CountPeopleLeft ( deque<int> (&Queue)[N] ){
    long left = 0;
    for ( int i = 0 ; i < N ; i++ )
        left += Queue[i].size();
    return left;
}

//Function to suggest the least waiting time
void entryQueueManager ( deque<int> (&Queue)[N] ){
    long min = Queue[0].size();
    for ( int i = 1 ; i < N ; i++ ){
        if ( Queue[i].size() < min )
            min = Queue[i].size();
    }
    cout<<"Least waiting time is: "<< p*min <<" minutes"<<endl;
    cout<<"Following queue numbers have the least waiting time as of now:"<<endl;
    for ( int i = 0 ; i < N ; i++ ){
        if ( min == Queue[i].size() )
            cout<<i+1<<" ";
    }
    cout<<endl;
    cout<<"You can choose from queue number 1 to "<<N<<endl;
}

//Function to automatically dequeue people into the stadium
void autodequeue( deque<int> (&Queue)[N] ){
    this_thread::sleep_for(minutes(p));
    if ( CountPeopleLeft(Queue) ){
        for ( int i = 0 ; i < N ; i++ ){
            if ( Queue[i].size() ){
                Queue[i].pop_back();
            }
        }
        autodequeue(Queue);
    }
    else
        return;
}

int main() {
    int x = 0;
    pair<short int, int> SerialNo[N];
    deque<int> Queue[N];
    createSerialNo(SerialNo);
    Assign_to_Random_Gate(SerialNo, Queue);
    Distribute(Queue);
    cout<<endl<<endl;
    Stopwatch stat;
    thread t(autodequeue);
    t.detach();
    do{
        continue;
    }while(CountPeopleLeft(Queue));
    cout<<"Total time: "<<stat.ElapsedMinutes()<<endl;
        return 0;
}
