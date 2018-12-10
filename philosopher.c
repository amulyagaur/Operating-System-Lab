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

sem_t s[5];
void* philosopher(void *arg)
{
    int p=*((int*)arg);
    while(1)
    {
        printf("Philosopher %d thinking\n",p);
        sleep(1);
        sem_wait(&s[p]);
        sem_wait(&s[(p+1)%5]);
        printf("Philosopher %d eating\n",p);
        sleep(2);
        printf("Philosopher %d finished eating\n",p);
        sem_post(&s[p]);
        sem_post(&s[(p+1)%5]);
    }
}

int main()
{
    int id[5];
    for(int i=0;i<5;i++)
    {
        sem_init(&s[i],0,1);
        id[i]=i;
    }
    pthread_t pt[5];
    for(int i=0;i<5;i++)
    {
        pthread_create(&pt[i],NULL,philosopher,(void*)&id[i]);
    }
    for(int i=0;i<5;i++)
        pthread_join(pt[i],NULL);
    return 0;
}