#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
int x=0;
void* f()
{
    x+=500;
}
int main()
{
    pthread_t p;
    int res=-1;
    pthread_create(&p,NULL,f,NULL);
    pthread_join(p,(void*)&res);
    printf("%d\n",res);
}