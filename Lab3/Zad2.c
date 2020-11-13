#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define DELAY 1000000


void catchtimer(){
    printf("continue prcoccessing signal...\n");
}

void catchexit(int PID){
    printf("cought %d\n", PID);
    exit(0);
}

void catchcontinue(int PID){
    printf("cought %d\n", PID);
}

void catchwait(){
    timer_t gman;
    struct itimerspec value;
  
    value.it_value.tv_sec = 1;
    value.it_value.tv_nsec = 1000000;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_nsec = 0;

    timer_create(CLOCK_REALTIME, NULL,  &gman);
    timer_settime(gman, 0, &value, NULL);

    signal(SIGALRM, catchtimer);
}

void catchskip(int PID){}

int main(){
    int i = 0;
    struct timespec tim, tim2;

    tim.tv_sec  = 0;
    tim.tv_nsec = DELAY;
    signal(SIGUSR1, catchwait);
    signal(SIGUSR2, catchskip);
    signal(SIGTERM, catchexit);
    signal(SIGALRM, catchcontinue);

    while (1){
        ++i;
        printf("%d %d\n", getpid(), i);
        nanosleep(&tim, &tim2);
    } 
}
