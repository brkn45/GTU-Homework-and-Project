#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int my_dup1(int oldfd) { 
    return fcntl(oldfd, F_DUPFD, 0);
}

int my_dup2(int oldfd, int newfd) {
    int status;

    // handle the specialcase   where  oldfd  equals  newfd.
    if (oldfd == newfd) {
        //is oldfd valid
        status = fcntl(oldfd, F_GETFL);
        if (status == -1) {
            errno = EBADF; // if  oldfd has error assing to errnoc EBADF= bad file decriptor
            return -1;
        }
        return newfd;
    }

    int saved_errno = errno; 
    close(newfd);
    errno = saved_errno;
    
    status = fcntl(oldfd, F_DUPFD, newfd);
    if (status == -1) {
        return -1;
    }
    return status;
}
int main() {
    char buffer[50];
    int flags =  O_CREAT | O_RDWR;
    int fd1 = open("test.txt", flags,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd1 == -1) {
        perror("open");
        return 1;
    }

    printf("-----------Dub1 Function----------");
    int fd2 = my_dup1(fd1); // copy of decriptor
    if (fd2 == -1) {
        perror("my_dup1");
        return 1;
    }
    printf("\nfd1: %d, fd2: %d\n", fd1, fd2); // file decriptor address
    write(fd1,"first", 5); // firstli fd1 write in same file
    write(fd2,"second",6); // secondly fd2 write in same file
    lseek(fd1,SEEK_SET,0);
    
    int n= read(fd1,buffer,12);
    buffer[n] ='\0';
    printf("Read file:%s",buffer);
    off_t offset1 = lseek(fd1, 0, SEEK_CUR);
    off_t offset2 = lseek(fd2, 0, SEEK_CUR);    
    printf("\nFile offset1: %lld  \nFile offset2 : %lld\n", (long long) offset1, (long long) offset2);  

    printf("\n-----------Dub2 Function----------");
    int fd3;
    my_dup2(fd1, fd3);
    if (fd3 == -1) {
        perror("my_dup2");
        return 1;
    }      

       
    offset1 = lseek(fd1, 0, SEEK_CUR);
    off_t offset3 = lseek(fd3, 0, SEEK_CUR);
    printf("\nfd1: %d, fd3: %d\n", fd1, fd3);
    printf("File offset1: %lld  \nFile offset3 : %lld\n", (long long) offset1, (long long) offset3);  

    int fd4=3;
    my_dup2(fd1, fd4);
    if (fd4 == -1) {
        perror("my_dup2");
        return 1;
    }      
    offset1 = lseek(fd1, 0, SEEK_CUR);
    off_t offset4 = lseek(fd4, 0, SEEK_CUR);
    printf("\nfd1: %d, fd4: %d\n", fd1, fd4);
    printf("File offset1: %lld  \nFile offset4 : %lld\n", (long long) offset1, (long long) offset4);  
    close(fd1);
    close(fd2);
    close(fd3);
    
    return 0;
}