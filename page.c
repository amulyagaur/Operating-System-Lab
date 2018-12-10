#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    long long n;
    scanf("%lld",&n);
    printf("offset %lld\n",n&((1LL<<12)-1));
    long long m=((1LL<<32)-1LL)-((1LL<<12)-1);
    printf("pageno %lld\n",(n&m)>>12 );
    return 0;
}