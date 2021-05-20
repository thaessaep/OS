#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mtx1, mtx2;

struct City{
	
	char* city;
	int time;
};

struct Number{
	
	int number;
	int time;
};

char buffer[12];


void* thread_W(void* arg){
	
	struct City *args = (struct City*)arg;
	
	for(int i = 0; i < 12; i++){
		pthread_mutex_lock(&mtx1);
		if(i == 6){
			usleep(100000);
		}		
		buffer[i] = args->city[i];
		pthread_mutex_unlock(&mtx2);
		usleep(args->time);
	}
	pthread_exit(NULL);
}

void* thread_R(void* arg){

	struct Number *args = (struct Number*)arg;
	
	for(int i = 0; i < 12; i++){
		pthread_mutex_lock(&mtx2);
		
		switch(args->number){
			case 1:
				printf("\033[%d;20H", i+1);
				break;
			case 2:
				printf("\033[%d;40H", i+1);
				break;
			case 3:
				printf("\033[%d;60H", i+1);
				break;	
		}
		printf("%c", buffer[i]);
		usleep(args->time);
		pthread_mutex_unlock(&mtx1);
	}
	
	
	pthread_exit(NULL);
}


int main(int argc, char** argv){	

	printf("\033[2J\n");
	
	pthread_mutex_init(&mtx1, NULL);
	pthread_mutex_init(&mtx2, NULL);
	
	struct City first = { "Novosibirsk" };
	struct City second = { "Semipalantink" };
	struct City third = { "Ekaterinburg" };
	if(argc > 2){
		first.time = second.time = third.time = atof(argv[1]) * 100000;
	}
	else{
		first.time = second.time = third.time = 100000;
	}
	
	struct Number number1 = { 1 };
	struct Number number2 = { 2 };
	struct Number number3 = { 3 };
	if(argc > 1){
		number1.time = number2.time = number3.time = atof(argv[2]) * 100;
	}
	else{
		number1.time = number2.time = number3.time = 30000;
	}
	
	
	pthread_t threadW1, threadW2, threadW3, threadR1, threadR2, threadR3;
	pthread_create(&threadW1, NULL, (void*)thread_W, &first);
	pthread_create(&threadW2, NULL, (void*)thread_W, &second);
	pthread_create(&threadW3, NULL, (void*)thread_W, &third);
	pthread_create(&threadR1, NULL, (void*)thread_R, &number1);
	pthread_create(&threadR2, NULL, (void*)thread_R, &number2);
	pthread_create(&threadR3, NULL, (void*)thread_R, &number3);
	
	for(int i = 0; i < 14; i++){
		printf("\n");
		usleep(300000);
	}

	pthread_join(threadW1, NULL);
	pthread_join(threadW2, NULL);
	pthread_join(threadW3, NULL);
	pthread_join(threadR1, NULL);
	pthread_join(threadR2, NULL);
	pthread_join(threadR3, NULL);
	printf("\n");
	return 0;
}
