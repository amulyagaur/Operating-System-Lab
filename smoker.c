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
sem_t AB, BC, CA, mutex;
void *agent()
{
    while (1)
    {
        sem_wait(&mutex);
        int r = rand() % 3;
        if (r == 0)
            sem_post(&AB);
        else if (r == 1)
            sem_post(&BC);
        else
            sem_post(&CA);
    }
}
void *sa()
{
    while (1)
    {
        sem_wait(&BC);
        printf("Smoker A smoking\n");
        sleep(1);
        sem_post(&mutex);
    }
}
void *sb()
{
    while (1)
    {
        sem_wait(&CA);
        printf("Smoker B smoking\n");
        sleep(1);
        sem_post(&mutex);
    }
}
void *sc()
{
    while (1)
    {
        sem_wait(&AB);
        printf("Smoker C smoking\n");
        sleep(1);
        sem_post(&mutex);
    }
}
int main()
{
    sem_init(&mutex, 0, 1);
    sem_init(&AB, 0, 0);
    sem_init(&BC, 0, 0);
    sem_init(&CA, 0, 0);
    pthread_t ag, a, b, c;
    pthread_create(&ag, NULL, agent, NULL);
    pthread_create(&a, NULL, sa, NULL);
    pthread_create(&b, NULL, sb, NULL);
    pthread_create(&c, NULL, sc, NULL);
    pthread_join(ag, NULL);
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    pthread_join(c, NULL);
    return 0;
}