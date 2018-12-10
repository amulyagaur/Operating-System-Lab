#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    struct stat buf;
    stat("./SystemCalls.pdf",&buf);
    printf("%ld\n",buf.st_ino);
    printf("%ld\n",buf.st_size);
    printf("%ld\n",buf.st_blksize);
    printf("%ld\n",buf.st_blocks);
    return 0;
}