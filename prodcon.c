#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>
sem_t s, f, e;
int n, buf;
void *producer(void *arg)
{
    int p = *((int *)arg);
    sem_wait(&e);
    sem_wait(&s);
    sleep(1);
    buf++;
    printf("Producer %d producing %d\n", p, buf);
    sem_post(&s);
    sem_post(&f);
}
void *consumer(void *arg)
{
    int p = *((int *)arg);
    sem_wait(&f);
    sem_wait(&s);
    sleep(1);
    buf--;
    printf("Consumer %d consuming %d\n", p, buf);
    sem_post(&s);
    sem_post(&e);
}
int main()
{
    scanf("%d", &n);
    sem_init(&s, 0, 1);
    sem_init(&f, 0, 0);
    sem_init(&e, 0, n);
    int id[20];
    pthread_t p[20], c[20];
    for (int i = 0; i < 20; i++)
    {
        id[i] = i;
        pthread_create(&p[i], NULL, producer, &id[i]);
    }
    for (int i = 0; i < 20; i++)
        pthread_create(&c[i], NULL, consumer, &id[i]);

    for (int i = 0; i < 20; i++)
    {
        pthread_join(c[i], NULL);
        pthread_join(p[i], NULL);
    }
    
}
