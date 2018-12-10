#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t c, b, mutex;
int wt = 0, n = 5;

void *barber()
{
	while (1)
	{
		printf("Barber Sleeping...\n");
		sem_wait(&c);
		sem_wait(&mutex);
		wt--;
		sem_post(&b);
		sem_post(&mutex);
		printf("barber cuts the hair\n");
		sleep(1);
	}
}
void *customer(void *arg)
{
	int p = *((int *)arg);
	sem_wait(&mutex);
	if (wt < n)
	{
		printf("Customer %d enters.\n", p);
		wt++;
		sem_post(&c);
		sem_post(&mutex);
		sem_wait(&b);
		printf("Customer %d getting haircut\n", p);
		sleep(2);
	}
	else
	{
		printf("Customer %d exits\n", p);
		sem_post(&mutex);
	}
}
int main()
{
	sem_init(&c, 0, 0);
	sem_init(&b, 0, 0);
	sem_init(&mutex, 0, 1);
	pthread_t bar, cust[10];
	pthread_create(&bar, NULL, barber, NULL);
	int id[10];
	for (int i = 0; i < 10; i++)
	{
		id[i] = i + 1;
		pthread_create(&cust[i], NULL, customer, (void *)&id[i]);
	}
	pthread_join(bar, NULL);
	for (int i = 0; i < 10; i++)
	{
		pthread_join(cust[i], NULL);
	}
}
