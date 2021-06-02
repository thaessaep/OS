#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

int rc = 0;
sem_t rsem, wsem;

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
	
	while(1){
		sem_wait(&wsem);

		for(int i = 0; i < 12; i++){
			if(i == 6){
				usleep(100000);
			}		
			buffer[i] = args->city[i];
		}

		sem_post(&wsem);
		usleep(args->time);
		
	}
	pthread_exit(NULL);
}

void* thread_R(void* arg){

	struct Number *args = (struct Number*)arg;
	char copy[12];
	int i = 0;
	
	while(1){
		
		sem_wait(&rsem);
		
		rc += 1;
		if(rc == 1){
			sem_wait(&wsem);
		}
		sem_post(&rsem);
		
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
		
		strcpy(copy, buffer);
		printf("%s\n", copy);
		i++;
		
		sem_wait(&rsem);
		rc -= 1;
		if(rc == 0){
			sem_post(&wsem);
		}
		sem_post(&rsem);
		usleep(args->time);
	}
	
	pthread_exit(NULL);
}


int main(int argc, char** argv){	

	printf("\033[2J\n");
	
	sem_init(&wsem, 0, 1);
	sem_init(&rsem, 0, 1);
	
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
		number1.time = number2.time = number3.time = 300;
	}
	
	
	pthread_t threadW1, threadW2, threadW3, threadR1, threadR2, threadR3;
	pthread_create(&threadW1, NULL, (void*)thread_W, &first);
	pthread_create(&threadW2, NULL, (void*)thread_W, &second);
	pthread_create(&threadW3, NULL, (void*)thread_W, &third);
	pthread_create(&threadR1, NULL, (void*)thread_R, &number1);
	pthread_create(&threadR2, NULL, (void*)thread_R, &number2);
	pthread_create(&threadR3, NULL, (void*)thread_R, &number3);
	
	for(int i = 0; i < 20; i++){
		printf("\n");
		usleep(300000);
	}

	pthread_join(threadW1, NULL);
	pthread_join(threadR1, NULL);
	pthread_join(threadW2, NULL);
	pthread_join(threadR2, NULL);
	pthread_join(threadW3, NULL);
	pthread_join(threadR3, NULL);
	printf("\n");
	sem_destroy(&wsem);
	sem_destroy(&rsem);
	return 0;
}
