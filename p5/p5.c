#include <assert.h> 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <string.h>
//-----------------------------------------GLOBALS----------------------------------------
#define MAX 100
int arrivalTimes[MAX]; 
int burstTimes[MAX];
int QUANTUM = 100;
int SIZE = 0;
#define SIZE_2  20

//-------------------------------------QUEUE STRUCT--------------------------------------
struct queue {
    int data[SIZE_2];
    int front, back; 

}queue;
void push(int x) {
    queue.data[queue.front] = x;
    queue.front = (queue.front+1) % SIZE_2;
}
int pop() {
    int x = queue.data[queue.back];
    queue.back = (queue.back+1) % SIZE_2;
    return x;
}
int empty() {
    return queue.front == queue.back;
}
//----------------------------------------------FIRST COME FIRST SERVE---------------------
 void FCFC(int* burst, int* arriv) {

    int clock = 0;

    int finish = 0;
    int totWaitTime = 0;
    int totTaTime = 0;
    clock = clock + arriv[0]; // set the clock to the first arrival time...
    for(int i = 0; i < SIZE; i++)
    {
        // THE WAIT TIME(finish time(clock) - arrival time) - burst
        if (clock < arriv[i]) // if there is a lag in the system, or the clock time is less than the arrival time...
        {
            clock = arriv[i];

        }
        clock = clock + burst[i];
        finish = clock;
        totWaitTime = totWaitTime + ((finish - arriv[i])-burst[i]);

        //THE TURN AROUND TIME>>> (finish time - arrival time)
        totTaTime = totTaTime + (finish - arriv[i]);
    }

    float turnAround = (totTaTime/1.00)/SIZE;
    float totWait = (totWaitTime/1.00)/SIZE;
     printf("First Come First Serve\n");
    printf("Avg. Response: %.2f, Avg. T.A.: %.2f, Avg. Wait: %.2f \n",totWait ,turnAround ,totWait);

}

//-----------------------------------------------------ROUND ROBIN------------------------------------------------------------
void RoundRobin(int* burst,int* arriv) {
    int clock = 0, wait = 0, resp = 0, ta = 0, next = 0, remain[SIZE];
    queue.front = 0;
    queue.back = 0;
    //cpy burst to remain
    for(int i = 0; i < SIZE; i++)
    {
        remain[i] = burst[i];
    }
    while (empty() == 0 || next < SIZE)
    {
        if(next < SIZE && arriv[next] > clock && empty() == 1) // if there is a lag in the system...
        {
            clock = arriv[next];
        }
          for(int i = next; i < SIZE; i++)// loading next times into th
          {
          if(arriv[i] <= clock) {
            push(i);
            next++;
          }
        }
        assert(empty() == 0);//make sure something is in the q
        int x = pop();
        if (remain[x] == burst[x])
        {
            // when it starts - when it comes into the q
            resp = resp + (clock - arriv[x]);
        }
        if(remain[x] <= QUANTUM) // if burst time is less than quantum... WE ARE FINISHING
        {
           clock = clock + remain[x];
            int tempTA = clock - arriv[x];
            ta = ta + tempTA;
            wait = wait + (tempTA - burst[x]);
            remain[x] = 0;
        }
        else
        {
            remain[x] = remain[x] - QUANTUM;
            clock = clock + QUANTUM;
            
            for(int i = next; i < SIZE; i++)
            {
              if(arriv[i] <= clock) {
                push(next);
                next++;
              }
            }
            push(x);
        }
    }
    float response = (resp/1.00)/SIZE;
    float turnAround = (ta/1.00)/SIZE;
    float totWait = (wait/1.00)/SIZE;
     printf("Round Robin\n");
    printf("Avg. Response: %.2f, Avg. T.A.: %.2f, Avg. Wait: %.2f \n",response ,turnAround ,totWait);
}
//--------------------------------------------------------------MAIN------------------------------------------------------------------- 
int main() {
 //read from a the process-list.txt
 FILE * in;
 in = fopen("processlist.txt", "r");
  
memset(arrivalTimes, 0, sizeof(int) * MAX);//set arrive to zero 
memset(burstTimes, 0, sizeof(int) * MAX);
// int i = 1;
 while (fscanf(in,"%d %d", arrivalTimes + SIZE, burstTimes + SIZE) !=EOF)
 {
     SIZE++;
 }
 FCFC(burstTimes,arrivalTimes);
 RoundRobin(burstTimes, arrivalTimes);
}//end main
