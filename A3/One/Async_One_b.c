#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

#define N 5
#define sauce_N__ 2
#define THINK_STATE 2
#define SAUCE_STATE 1
#define EAT_STATE 0
#define To_the_Left (phnum + 4) % N
#define To_the_Right (phnum + 1) % N
#define sauceGetter (phnum) % sauce_N__

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };
int forks[N] = { 0, 1, 2, 3, 4 };
int bowls[N] = {1, 2, 3, 4 , 5};
int sauce[sauce_N__] = { 0, 1 };

void hasSauce(int phnum){
	if (state[phnum] == SAUCE_STATE && state[To_the_Left] != EAT_STATE && state[To_the_Right] != EAT_STATE) {
		state[phnum] = EAT_STATE;
		printf("Philosopher %d takes Sauce bowl %d\n", phnum + 1, sauce[sauceGetter]+1);
	}
}
void IsEating(int phnum){
	if (state[phnum] == THINK_STATE && state[To_the_Left] != EAT_STATE && state[To_the_Right] != EAT_STATE) {
		state[phnum] = SAUCE_STATE;
		printf("Philosopher %d takes forks %d and %d\n", phnum + 1, forks[To_the_Left] + 1, forks[phnum] + 1);
		printf("Philosopher %d reachs for Sauce bowl\n", phnum + 1);
	}
}

void pick_up_forks(int phnum){
	state[phnum] = THINK_STATE;
	IsEating(phnum);
}

void taking_sauce(int phnum){
	state[phnum] = SAUCE_STATE;
	hasSauce(phnum);
}
void puts_down_sauce(int phnum){
	state[phnum] = EAT_STATE;
	printf("Philosopher %d indulges in the Sauce.\n", phnum + 1);
    printf("Philosopher %d is Eating from Rice bowl %d.\n", phnum + 1, bowls[phnum]);
	printf("Philosopher %d putting sauce bowl %d down, waiting to indulge in it once more\n", phnum + 1, sauce[sauceGetter]+1);
	hasSauce(To_the_Left);
	hasSauce(To_the_Right);
}

void put_down_forks(int phnum){
	state[phnum] = THINK_STATE;
	printf("Philosopher %d putting forks %d and %d down\n", phnum + 1, forks[To_the_Left] + 1, forks[phnum] + 1);
	printf("Philosopher %d is thinking\n", phnum + 1);
	IsEating(To_the_Left);
	IsEating(To_the_Right);
}

void* philosopher_dinner(void* num){
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
	// +---------------------------------------------+
	// | Modified Dining Philosopher Problem Starts! |
	// | * Omitted Hungry state                      |
	// | * Added Sauce Bowls                         |
	// +---------------------------------------------+
	printf("Modified Dining Philosopher Problem Starts!\n");
	for (i = 0; i < N; i++) {
		pthread_create(&phil_id[i], NULL, philosopher_dinner, &phil[i]);
		printf("Philosopher %d is Thinking\n", i + 1);
	}
	for (i = 0; i < N; i++){
		pthread_join(phil_id[i], NULL);
	}
}