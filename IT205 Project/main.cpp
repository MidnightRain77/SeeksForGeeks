#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <utility>
#include <deque>
#include <vector>
using namespace std::chrono;
using namespace std;
const int M = 100; //Capacity of the stadium
const int N = 10; //Number of entry gates
const int p = 1; //mins it takes for a single spectator to enter any gate

class Counter{
    int Done;
    int count_VIP;
public:
    Counter() : Done(0), count_VIP(0) {};
    
    void increase (){
        Done++;
    }
    
    void increse_VIP(){
        count_VIP++;
    }
    
    int isEmpty(){
        return ( Done >= ( M - count_VIP ) ) ? 1 : 0;
    }
    void displayvip(){
        cout<<count_VIP;
    }
};

//Calculate the time passed since the opening of entry gates
class Stopwatch{
    time_point <high_resolution_clock> start;
public:
    Stopwatch() : start ( high_resolution_clock::now() ) {}
    
    long ElapsedMinutes(){
        return duration_cast<minutes>( high_resolution_clock::now() - start ).count();
    }
};

//Function to check if the serial number is a VIP
int HashFunction ( int Serial_No ){
    return ( !(Serial_No % (M/8)) ) ? 1 : 0;
}

//Initializes the pair
void CreateSerialNo ( pair<short int, int> (&SerialStat)[M], Counter& counter ){
    for ( int i = 0 ; i < M ; i++ ){
        SerialStat[i].first = 0;
        if ( HashFunction(i) ){
            counter.increse_VIP();
        }
    }
}

//Function to randomly assign M/2 people to the entry gates
void AssignRandomGate ( pair<short int, int> (&SerialStat)[M], deque<int> (&Queue)[N] ){
   // srand ( (unsigned int) ( time(0) ) );
    for ( int i = 0 ; i < M/2 ; i++ ){
        int gate = rand() % N;
        int serial;
        do{
            serial = rand() % M;
            if ( !HashFunction(serial) ){
                if ( !SerialStat[serial].first )
                    break;
            }
        } while(true);
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
                    Queue[i].push_front(reshuff.back());
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

//Function to suggest the least waiting time
void Suggestion ( deque<int> (&Queue)[N] ){
    long min = Queue[0].size();
    for ( int i = 1 ; i < N ; i++ ){
        if ( Queue[i].size() <= min )
            min = Queue[i].size();
    }
    cout << "Least waiting time is: " << p*min << " minutes" << endl << flush;
    cout << "Following queue numbers have the least waiting time as of now:" << endl << flush;
    for ( int i = 0 ; i < N ; i++ ){
        if ( min == Queue[i].size() )
            cout << i + 1 << " ";
    }
    cout << endl << "You can choose from queue number 1 to " << N << endl << flush;
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
void AutoDequeue ( deque<int> (&Queue)[N], pair<short int, int> (&SerialStat)[M], Counter& counter ){
    while ( !counter.isEmpty() ){
        this_thread::sleep_for(minutes(p));
        for ( int i = 0 ; i < N ; i++ ){
            if ( Queue[i].size() ){
                SerialStat[Queue[i].back()].first = 2;
                Queue[i].pop_back();
                counter.increase();
            }
        }
    }
}

int main() {
    pair<short int, int> SerialStat[M];
    deque<int> Queue[N];
    int sr_num;
    int queue_num;
    Counter counter;
    CreateSerialNo(SerialStat, counter);
    AssignRandomGate(SerialStat, Queue);
    Distribute(Queue);
    Stopwatch stat;
    thread t(AutoDequeue, std::ref(Queue), std::ref(SerialStat), std::ref(counter));
    t.detach();
    while(true){
        while(true){
            cout << "Welcome to the Entry Queue Management System!" << endl << flush;
            cout << "Please enter your 7-digit serial number: " << flush;
            if ( cin >> sr_num ){
                sr_num -= 1000000;
                cout << endl;
                if ( sr_num >= 0 && sr_num < M ){
                    if ( SerialStat[sr_num].first == 0 ){
                        if ( HashFunction(sr_num) ){
                            cout << "Welcome, VIP! You will be directed to our exclusive entry gate." << endl << endl << endl << flush;
                            SerialStat[sr_num].first = 2;
                        }
                        else{
                            SerialStat[sr_num].first = 1;
                            cout << "Here are the recommended entry gates based on the current wait time:" << endl << flush;
                            Suggestion(Queue);
                            cout << "Please enter your preferred entry gate number: " << flush;
                            cin >> queue_num;
                            cout << endl;
                            while ( queue_num <= 0 || queue_num > N ){
                                cout << "Oops! Please enter a gate number between 1 and " << N << ": " << flush;
                                cin >> queue_num;
                            }
                            SerialStat[sr_num].second = queue_num - 1;
                            Queue[queue_num - 1].push_front(sr_num);
                            //displayassigned(Queue);
                        }
                    }
                    else if ( SerialStat[sr_num].first == 1 ){
                        cout << "It looks like you're already in a queue. Do you wish to switch to a different gate?" << endl << flush;
                        cout << "Here are the recommended entry gates based on the current wait time:" << endl << flush;
                        Suggestion(Queue);
                        cout << "Please enter your preferred entry gate number: " << flush;
                        cin >> queue_num;
                        while ( queue_num <= 0 || queue_num > N ){
                            cout << "Oops! Please enter a gate number between 1 and " << N << ": " << flush;
                            cin >> queue_num;
                        }
                        Delete(Queue, SerialStat[sr_num].second, sr_num);
                        SerialStat[sr_num].second = queue_num - 1;
                        Queue[queue_num - 1].push_front(sr_num);
                        cout << "Your queue has been updated. You are now in the queue for Gate " << queue_num << "." << endl << endl << endl << flush;

                    }
                    else{
                        cout << "You have already entered the stadium. Re-entry is not permitted." << endl << endl << endl << flush;
                    }
                    break;
                }
                else
                {
                    cout << "The serial number you entered is invalid. Please try again with a valid 7-digit serial number." << endl << endl << endl << flush;
                    continue;
                }
            }
            else{
                cin.clear();
                cout << "We couldn't understand your input. Please make sure to enter a 7-digit serial number." << endl << endl << endl << flush;
            }
        }
        
        if ( counter.isEmpty() ){
            break;
        }
        else
            continue;
    }
    cout << "All spectators have been processed. Total processing time: " << stat.ElapsedMinutes() << " minutes." << endl << flush;
        return 0;
}
