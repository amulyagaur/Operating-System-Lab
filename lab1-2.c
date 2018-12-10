#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int main()
{
    struct dirent *dir;
    DIR* ptr = opendir("..");
    while( (dir=readdir(ptr))!= NULL )
    {
        printf("Name : %s Inode no. : %lu\n",dir->d_name,dir->d_ino);
    }
    mkdir("./newfolder1",0);
    chdir("./newfolder1");
    printf("%s\n",getcwd(NULL,0));
    ptr = opendir(".");
    while( (dir=readdir(ptr))!= NULL )
    {
        printf("%s\n",dir->d_name);
    }
    rmdir("./newfolder1");
    return 0;
}