#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define N_BOWLS 5
#define THINK_STATE 1
#define EAT_STATE 0
#define To_the_Left (phil + 4) % N
#define To_the_Right (phil + 1) % N

int state[N];
int philList[N] = { 0, 1, 2, 3, 4 };
int forks[N] = { 0, 1, 2, 3, 4 };
int bowls[N] = { 1, 2, 3, 4, 5 };

// sem_t mutex;
// sem_t S[N];

void IsEating(int phil)
{
	if (state[phil] == THINK_STATE && state[To_the_Left] != EAT_STATE && state[To_the_Right] != EAT_STATE) {
		state[phil] = EAT_STATE;
		printf("Philosopher %d takes forks %d and %d\n", phil + 1, forks[To_the_Left] + 1, forks[phil] + 1);
    	printf("Philosopher %d is Eating from Rice bowl %d.\n", phil + 1, bowls[phil]);
	}
}

void pick_up_forks(int phil){
	state[phil] = THINK_STATE;
	IsEating(phil);
}

void put_down_forks(int phil){
	state[phil] = THINK_STATE;
	printf("Philosopher %d putting forks %d and %d down\n", phil + 1, forks[To_the_Left] + 1, forks[phil] + 1);
	printf("Philosopher %d is thinking\n", phil + 1);
	IsEating(To_the_Left);
	IsEating(To_the_Right);
}

void* philosopher_dinner(void* num)
{
	while (1) {
		int* i = num;
		pick_up_forks(*i);
		put_down_forks(*i);
	}
}

int main(){
	int i;
	pthread_t phil_id[N];
	// +---------------------------------------------+
	// | Modified Dining Philosopher Problem Starts! |
	// | * Omitted Hungry state                      |
	// +---------------------------------------------+
	printf("Modified Dining Philosopher Problem Starts!\n");
	for (i = 0; i < N; i++) {
		pthread_create(&phil_id[i], NULL, philosopher_dinner, &philList[i]);
		printf("Philosopher %d is Thinking\n", i + 1);
	}
	for (i = 0; i < N; i++){
		pthread_join(phil_id[i], NULL);
	}
}