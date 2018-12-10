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
    creat("file.txt",777);
    int fd= open("file.txt",O_RDWR);
    char *str = "hello World!";
    write(fd,str,strlen(str));
    close(fd);
    fd= open("file.txt",O_RDWR);
    char buf[500];
    read(fd,buf,15);
    printf("%s\n",buf);
    close(fd);
    fd= open("file.txt",O_RDWR);
    //printf("%d\n",lseek(fd,0,SEEK_END));
    int sz = lseek(fd,0,SEEK_END);
    char ch;
    sz--;
    while(sz>=0)
    {
        lseek(fd,sz,0);
        read(fd,&ch,1);
        printf("%c\n",ch);
        sz--;
    }
    link("file.txt","hw.txt");
    system("ls");
    unlink("file.txt");
    system("ls");
    return 0;
}