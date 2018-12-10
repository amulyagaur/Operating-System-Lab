#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
pthread_mutex_t lock;
pthread_cond_t cond;
int cn=1;

void* print(void *arg)
{
    int p=*((int*)arg);
    pthread_mutex_lock(&lock);

    while(p!=cn)
        pthread_cond_wait(&cond,&lock);

    for(int i=0;i<10;i++)
    {
        printf("%d\n",p);
    }
    cn++;
    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&lock);
    return 0;
}

int main()
{
    pthread_t th[10];
    int id[10];
    for(int i=1;i<=10;i++)
    id[i-1]=i;
    for(int i=0;i<10;i++)
    {
        pthread_create(&th[i],NULL,print,(void*)&id[i]);
    }
    for(int i=0;i<10;i++)
    {
        pthread_join(th[i],NULL);
    }
}