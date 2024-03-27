#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;
#define M 10000
#define N 30
#define p 5 //p is five minutes
int queue[N];

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
}

void entryQueueManager(){
    int min = queue[0];
    for ( int i = 1 ; i < N ; i++ ){
        if ( queue[i] < min )
            min = queue[i];
    }
    cout<<"Least waiting time is: "<<p*min<<" minutes"<<endl;
    cout<<"Following queue numbers have the least waiting time as of now:"<<endl;
    for ( int i = 0 ; i < N ; i++ ){
        if ( min == queue[i] )
            cout<<++i<<" ";
    }
    cout<<endl;
}

