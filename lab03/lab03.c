#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

// prototypes
void* countdown(void*);
void* countup(void*);

// number of threads to execute
int threads;
// number of seconds to execute for
int sec;
// timer flag 0: timer off, 1: timer on
int timer = 0;

// create threads
int main(int argc, char* argv[]) {
	// verify command line args
	if(argc != 3) {
		printf("USAGE: %s [threads(max 6)] [time(sec)]\n", argv[0]);
		return 0;
	}

	// verify number of threads
	if(atoi(argv[1]) < 1 || atoi(argv[1]) > 6) {
		printf("You must have between 1 and 6 threads inclusive\n");
		return 0;
	} else {
		threads = atoi(argv[1]);
	}

	// verify time
	if(atoi(argv[2]) < 1) {
		printf("You must specify a time greater then 0 seconds\n");
		return 0;
	} else {
		sec = atoi(argv[2]);
	}

	int id = 0;
	pthread_t tid;

	// create timer thread
	pthread_create(&tid, NULL, countdown, (void*)(intptr_t) id);
	
	// create counting threads
	int i = 0;
	pthread_t counter;
	for(i = 0; i < threads; ++i) {
		pthread_create(&counter, NULL, countup, (void*)(intptr_t) id);
	}	

	pthread_join(tid, NULL);

	timer = 0;
	
	return 0;
}

// sets a countdown thread
void* countdown(void* arg) {
	timer = 1;
	sleep(sec);

	return NULL;
}

// threads will count from 0 until timer is up
void* countup(void* arg) {
	int id = (intptr_t) arg;
	int count = 0;
	
	while(timer) {
		printf("Thread: %d, Count: %d\n", id, count++);
	}

	return NULL;
}
