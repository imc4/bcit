#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>

// prototypes
void* countdown(void*);
void* countup(void*);

// number of threads to execute
int threads;
// number of seconds to execute for
int sec;

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

	int i = 0;
	pthread_t tid;

	pthread_create(&tid, NULL, countdown, (void*) i);

	for(i = 1; i < threads; i++) {
		pthread_create(&tid, NULL, countup, (void*) i);
	}
	
	return 0;
}

// sets a countdown thread
void* countdown(void* arg) {
	int id = (int) arg;
	sec--;
	printf("tid: %d, timer: %d\n", id, sec);
	return NULL;
}

// threads will count from 0-infinity until timer is up
void* countup(void* arg) {
	int id = (int) arg;
	static int s = 0;
	printf("tid: %d, s: %d\n", id, ++s);
	return NULL;
}
