#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
int n,m,A[50][50],M[50][50],N[50][50],av[50],sf[50],buf[50];
int cn=0;
pthread_mutex_t lock;
pthread_cond_t cond;
void* print(void *arg)
{
    int p=*((int*)arg);
    pthread_mutex_lock(&lock);

    while(p!=sf[cn])
        pthread_cond_wait(&cond,&lock);

    printf("%d\n",p);
    
    cn++;
    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&lock);
    return 0;
}
bool isok(int i)
{
    for(int k=0;k<m;k++)
        if(buf[k]<N[i][k])
            return false;
    return true;
}

bool safe()
{
    int f[50]={0},c=-1,r=0;
    while(1)
    {
        r=0;
    for(int i=0;i<n;i++)
    {
        if(f[i]==0 && isok(i))
        {
            c++;
            sf[c]=i;
            f[i]=1;
            for(int j=0;j<m;j++)
                buf[j]+=A[i][j];
        }
        else
            r++;
    }
    if(r==n)
    {
        if(c==(n-1))
            return true;
        else
            return false;
    }
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    printf("Enter available\n");
    for(int i=0;i<m;i++)
    {
        scanf("%d",&av[i]);
        buf[i]=av[i];
    }

    printf("Enter current Allocation\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&A[i][j]);
        }
    }

    printf("Enter Max Allocation\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&M[i][j]);
        }
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            N[i][j]=M[i][j]-A[i][j];
        }
    }

    if(safe())
    {
        for(int i=0;i<n;i++)
            printf("%d ",sf[i]);
        printf("\n");
        pthread_t pr[n];
        int pid[n];
        for(int i=0;i<n;i++)
            pid[i]=i;
        for(int i=0;i<n;i++)
        {
            pthread_create(&pr[i],NULL,print,&pid[i]);
        }
        for(int i=0;i<n;i++)
        {
            pthread_join(pr[i],NULL);
        }
    }
    else
    {
        printf("Unsafe\n");
    }
    return 0;
}