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
    Stopwatch() : start( high_resolution_clock::now() ){}
    
    long ElapsedMinutes(){
        return duration_cast<minutes>( high_resolution_clock::now() - start ).count();
    }
};

//Function to check if the serial number is a VIP
int HashFunction ( int Serial_No ){
    return ( !(Serial_No % (M/8)) ) ? 1 : 0;
}

//Initializes the pair
void CreateSerialNo ( pair<short int, int> (&SerialStat)[M] ){
    for ( int i = 0 ; i < M ; i++ ){
        SerialStat[i].first = 0;
    }
}

//Function to randomly assign M/2 people to the entry gates
void AssignRandomGate ( pair<short int, int> (&SerialStat)[M], deque<int> (&Queue)[N] ){
    srand ( (unsigned int) ( time(0) ) );
    for ( int i = 0 ; i < M/2 ; i++ ){
        int gate = rand() % N;
        int serial;
        do{
            serial = rand() % M;
        } while( SerialStat[serial].first );
        Queue[gate].push_front(serial);
        SerialStat[serial].first = 1;
    }
}

//Function to minimize the time for entry of the first M/2 randomly assigned people
void Distribute ( deque<int> (&Queue)[N] ){
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
                    Queue[i].push_front( reshuff.back() );
                    reshuff.pop_back();
                    data--;
                }
            }
            else{
                while ( extra ){
                    Queue[i].push_front( reshuff.back() );
                    reshuff.pop_back();
                    extra--;
                }
                break;
            }
            if ( extra <= 0 )
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
void Suggestion ( deque<int> (&Queue)[N] ){
    long min = Queue[0].size();
    for ( int i = 1 ; i < N ; i++ ){
        if ( Queue[i].size() < min )
            min = Queue[i].size();
    }
    cout << "Least waiting time is: " << p*min << " minutes" << endl;
    cout << "Following queue numbers have the least waiting time as of now:" << endl;
    for ( int i = 0 ; i < N ; i++ ){
        if ( min == Queue[i].size() )
            cout << i + 1 << " ";
    }
    cout << endl;
    cout << "You can choose from queue number 1 to " << N << endl;
}

//Function to delete a particular serial number from a queue
void Delete ( deque<int> (&Queue)[N], int Gate, int Serial_No ){
    for ( size_t i = 0 ; i < Queue[Gate].size() ; ++i ){
        if ( Queue[Gate][i] == Serial_No ){
            auto it = Queue[Gate].begin() + i;
            Queue[Gate].erase(it);
        }
    }
}

//Function to automatically dequeue people into the stadium
void AutoDequeue ( deque<int> (&Queue)[N], pair<short int, int> (&SerialStat)[M] ){
    this_thread::sleep_for(minutes(p));
    if ( CountPeopleLeft ( Queue ) ){
        for ( int i = 0 ; i < N ; i++ ){
            if ( Queue[i].size() ){
                SerialStat[Queue[i].back()].first = 2;
                Queue[i].pop_back();
            }
        }
        AutoDequeue( Queue, SerialStat );
    }
    else
        return;
}

int main() {
    pair<short int, int> SerialStat[M];
    deque<int> Queue[N];
    CreateSerialNo(SerialStat);
    AssignRandomGate(SerialStat, Queue);
    Distribute(Queue);
    Stopwatch stat;
    thread t(AutoDequeue, std::ref(Queue), std::ref(SerialStat));
    t.detach();
    int sr_num;
    int queue_num;
    int n=0;
    while(true){
        n+=1;
        while(true){
            cout << "Enter your serial number: ";
            cin >> sr_num;
            sr_num = sr_num - 1000000;
            cout << endl;
            if ( sr_num >= 0 && sr_num <= M ){
                if ( SerialStat[sr_num].first == 0 )
                {
                    if ( HashFunction(sr_num) ){
                        cout << "You have VIP access to the stadium so you will be provided with direct entry" << endl;
                        SerialStat[sr_num].first = 2;
                    }
                    else{
                        SerialStat[sr_num].first = 1;
                        cout << "Suggestions by entry queue manager:" << endl;
                        Suggestion(Queue);
                        cout << "Enter the queue number you want to enter: ";
                        cin >> queue_num;
                        cout << endl;
                        while ( queue_num <= 0 || queue_num > N ){
                            cout << "Enter valid queue number: ";
                            cin >> queue_num;
                        }
                        SerialStat[sr_num].second = queue_num - 1;
                        Queue[queue_num - 1].push_front(sr_num);
                    }
                }
                else if ( SerialStat[sr_num].first == 1 ){
                    cout << "You want to switch your queue, so Suggestions by entry queue manager:" << endl;
                    Suggestion(Queue);
                    cout << "Enter the queue number you want to enter: ";
                    cin >> queue_num;
                    while ( queue_num <= 0 || queue_num > N ){
                        cout << "Enter valid queue number: ";
                        cin >> queue_num;
                    }
                    Delete(Queue, SerialStat[sr_num].second, sr_num);
                    SerialStat[sr_num].second = queue_num - 1;
                    Queue[queue_num - 1].push_front(sr_num);
                }
                else{
                    cout << "Re-entry is not allowed!" << endl;
                }
                break;
            }
            else
            {
                cout << "Invalid serial number entered!" << endl;
                continue;
            }
        }
        while ( ( n < ( M / 2 - 1 ) + ( M % 2 ) ) || CountPeopleLeft(Queue) != 0 ){
            cout << "Moving onto the next person..." << endl << endl;
            n++;
            break;
        }
        if ( ( n < ( M / 2 - 1 ) + ( M % 2 ) ) || CountPeopleLeft(Queue) != 0 ){
            continue;
        }
        else
            break;
    }
    do{
        continue;
    }while(CountPeopleLeft(Queue));
    cout << "Total time: " << stat.ElapsedMinutes() << endl;
        return 0;
}
