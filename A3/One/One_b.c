#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h> 
#include <sys/time.h>
#include <math.h>

#define N 5
#define sauce_N__ 2
#define THINK_STATE 2
#define SAUCE_STATE 1
#define EAT_STATE 0
#define To_the_Left (phil + 4) % N
#define To_the_Right (phil + 1) % N
#define sauceGetter (phil) % sauce_N__

int state[N];
int philList[N] = { 0, 1, 2, 3, 4 };
int forks[N] = { 0, 1, 2, 3, 4 };
int bowls[N] = { 1, 2, 3, 4, 5 };
int sauce[sauce_N__] = { 0, 1 };

sem_t mutex;
sem_t S[N];

void hasSauce(int phil){
	if (state[phil] == SAUCE_STATE && state[To_the_Left] != EAT_STATE && state[To_the_Right] != EAT_STATE) {
		state[phil] = EAT_STATE;
		printf("Philosopher %d takes sauce bowl %d\n", phil + 1, sauce[sauceGetter]+1);
		sem_post(&S[phil]);
	}
}
void IsEating(int phil)
{
	if (state[phil] == THINK_STATE && state[To_the_Left] != EAT_STATE && state[To_the_Right] != EAT_STATE) {
		state[phil] = SAUCE_STATE;
		printf("Philosopher %d takes forks %d and %d\n", phil + 1, forks[To_the_Left] + 1, forks[phil] + 1);
		printf("Philosopher %d reachs for sauce bowl\n", phil + 1);
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

void taking_sauce(int phil)
{
	sem_wait(&mutex);
	state[phil] = SAUCE_STATE;
	hasSauce(phil);
	sem_post(&mutex);
	sem_wait(&S[phil]);
}
void puts_down_sauce(int phil){
	sem_wait(&mutex);
	state[phil] = EAT_STATE;
	printf("Philosopher %d has bestowed upon himself this juicy, delicious hot chill sauce.\n", phil + 1);
	printf("Philosopher %d is Eating from Rice bowl %d.\n", phil + 1, bowls[phil]);
	printf("Philosopher %d is putting sauce bowl %d down, waiting to indulge in it once more\n", phil + 1, sauce[sauceGetter]+1);
	hasSauce(To_the_Left);
	hasSauce(To_the_Right);
	sem_post(&mutex);
}

void put_down_forks(int phil)
{

	sem_wait(&mutex);
	state[phil] = THINK_STATE;
	printf("Philosopher %d putting forks %d and %d down\n", phil + 1, forks[To_the_Left] + 1, forks[phil] + 1);
	printf("Philosopher %d is thinking\n", phil + 1);
	IsEating(To_the_Left);
	IsEating(To_the_Right);
	sem_post(&mutex);
}

void* philosopher_dinner(void* num)
{
	while (1) {
		int* i = num;
		pick_up_forks(*i);
		taking_sauce(*i);
		puts_down_sauce(*i);
		put_down_forks(*i);
	}
}

int main(){
	int i;
	pthread_t phil_id[N];
	sem_init(&mutex, 0, 1);
	// +---------------------------------------------+
	// | Modified Dining Philosopher Problem Starts! |
	// | * Omitted Hungry state                      |
	// | * Added Sauce Bowls                         |
	// +---------------------------------------------+
	printf("Modified Dining Philosopher Problem Starts!\n");
	for (i = 0; i < N; i++){
		sem_init(&S[i], 0, 0);
	}
	for (i = 0; i < N; i++) {
		pthread_create(&phil_id[i], NULL, philosopher_dinner, &philList[i]);
		printf("Philosopher %d is Thinking\n", i + 1);
	}
	for (i = 0; i < N; i++){
		pthread_join(phil_id[i], NULL);
	}
}