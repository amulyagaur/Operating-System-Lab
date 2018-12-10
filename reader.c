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

int c=0,rc=0;
sem_t wrt,mutex;

void* writer(void* arg)
{
    int p=*((int*)arg);
    sem_wait(&wrt);
    printf("Writer %d writing\n",p);
    c++;
    sleep(1);
    sem_post(&wrt);
}

void* reader(void* arg)
{
    int p=*((int*)arg);
    sem_wait(&mutex);
    rc++;
    if(rc==1)
        sem_wait(&wrt);
    sem_post(&mutex);

    printf("Reader %d reading %d\n",p,c);
    sleep(5);

    sem_wait(&mutex);
    rc--;
    if(rc==0)
        sem_post(&wrt);
    sem_post(&mutex);
}

int main()
{
    sem_init(&wrt,0,1);
    sem_init(&mutex,0,1);
    int wid[5],rid[5];
    pthread_t rth[5],wth[5];
    for(int i=0;i<5;i++)
    {
        rid[i]=i;
        wid[i]=i;
        
        pthread_create(&wth[i],NULL,writer,&wid[i]);
        pthread_create(&rth[i],NULL,reader,&rid[i]);
    }
    for(int i=0;i<5;i++)
    {
        
        pthread_join(wth[i],NULL);
        pthread_join(rth[i],NULL);
    }
    return 0;
}