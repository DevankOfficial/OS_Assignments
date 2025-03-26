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
int bowls[N] = { 0, 1, 2, 3, 4 };

sem_t mutex;
sem_t S[N];

void IsEating(int phil)
{
	if (state[phil] == THINK_STATE && state[To_the_Left] != EAT_STATE && state[To_the_Right] != EAT_STATE) {
		state[phil] = EAT_STATE;
		printf("philosopher %d takes forks %d and %d\n", phil + 1, forks[To_the_Left] + 1, forks[phil] + 1);
		printf("philosopher %d is Eating\n", phil + 1);
		sem_post(&S[phil]);
	}
}

void pick_up_forks(int phil)
{

	sem_wait(&mutex);
	state[phil] = THINK_STATE;
	IsEating(phil);
	sem_post(&mutex);
	sem_wait(&S[phil]);
}

void put_down_forks(int phil)
{

	sem_wait(&mutex);
	state[phil] = THINK_STATE;
	printf("philosopher %d putting forks %d and %d down\n", phil + 1, forks[To_the_Left] + 1, forks[phil] + 1);
	printf("philosopher %d is thinking\n", phil + 1);
	IsEating(To_the_Left);
	IsEating(To_the_Right);
	sem_post(&mutex);
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
	sem_init(&mutex, 0, 1);
	// +---------------------------------------------+
	// | Modified Dining philsopher Problem Starts! |
	// | * Omitted Hungry state                      |
	// +---------------------------------------------+
	printf("Modified Dining philosopher Problem Starts!\n");
	for (i = 0; i < N; i++){
		sem_init(&S[i], 0, 0);
	}
	for (i = 0; i < N; i++) {
		pthread_create(&phil_id[i], NULL, philosopher_dinner, &philList[i]);
		printf("philosopher %d is Thinking\n", i + 1);
	}
	for (i = 0; i < N; i++){
		pthread_join(phil_id[i], NULL);
	}
}