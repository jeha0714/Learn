#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void *reads(void *arg);
void *accus(void *arg);
static sem_t sem_one;
static sem_t sem_two;
static int num;

int main(int argc, char *argv[])
{
	pthread_t id_t1, id_t2;
	sem_init(&sem_one, 0, 0);
	sem_init(&sem_two, 0, 1);

	pthread_create(&id_t1, NULL, reads, NULL);
	pthread_create(&id_t2, NULL, accus, NULL);

	pthread_join(id_t1, NULL);
	pthread_join(id_t2, NULL);

	sem_destroy(&sem_one);
	sem_destroy(&sem_two);
	return (0);
}

void *reads(void *arg)
{
	int i;
	for (i = 0; i < 5; i++)
	{
		fputs("Input num: ", stdout);

		sem_wait(&sem_two);
		scanf("%d", &num);
		sem_post(&sem_one);
	}
	return (NULL);
}
void *accus(void *arg)
{
	int sum = 0, i;
	sleep(3);
	for (i = 0; i < 5; i++)
	{
		sem_wait(&sem_one);
		sum += num;
		sem_post(&sem_two);
	}
	printf("Result: %d \n", sum);
	return (NULL);
}
