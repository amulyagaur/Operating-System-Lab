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
sem_t s1,s2;
void* one()
{
    while(1)
    {
        sem_wait(&s1);
        printf("1\n");
        sleep(1);
        printf("1\n");
        sem_post(&s2);
    }
}
void* zero()
{
    while(1)
    {
        sem_wait(&s2);
        printf("0\n");
        sleep(1);
        printf("0\n");
        sem_post(&s1);
    }
}

int main()
{
    printf("HI\n");
    sem_init(&s1,0,1);
    sem_init(&s2,0,0);
    pthread_t t1,t2;
    pthread_create(&t1,NULL,one,NULL);
    pthread_create(&t2,NULL,zero,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}