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
pthread_mutex_t mut;
pthread_cond_t cond;
int n, buf;
void *producer(void *arg)
{
    int p = *((int *)arg);
    pthread_mutex_lock(&mut);
    while (buf == n)
        pthread_cond_wait(&cond, &mut);

    sleep(1);
    buf++;
    printf("Producer %d producing %d\n", p, buf);

    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mut);
}
void *consumer(void *arg)
{
    int p = *((int *)arg);
    pthread_mutex_lock(&mut);
    while (buf == 0)
        pthread_cond_wait(&cond, &mut);
    sleep(1);
    buf--;
    printf("Consumer %d consuming %d\n", p, buf);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mut);
}
int main()
{
    scanf("%d", &n);
    
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
