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
sem_t s;
int n;
void* client(void *arg)
{
    int p=*((int*)arg);
    printf("Client %d waiting for connection...\n",p);
    sem_wait(&s);
    printf("Client %d connected!\n",p);
    sleep(1);
    printf("Client %d disconnected\n",p);
    sem_post(&s);
}
int main()
{
    scanf("%d",&n);
    sem_init(&s,0,n);
    pthread_t th[10];
    int tid[10];
    for(int i=0;i<10;i++)
    {
        tid[i]=i+1;
    }
    for(int i=0;i<10;i++)
    {
        pthread_create(&th[i],NULL,client,(void*)&tid[i]);
    }
    for(int i=0;i<10;i++)
    {
        pthread_join(th[i],NULL);
    }
    return 0;
}