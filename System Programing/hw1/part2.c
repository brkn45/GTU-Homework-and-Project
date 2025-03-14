#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int my_dup(int oldfd) { //
    return fcntl(oldfd, F_DUPFD, 0);
}

int my_dup2(int oldfd, int newfd) {
    int status;

    
    if (oldfd == newfd) {
        status = fcntl(oldfd, F_GETFL);
    if (status == -1) {
        errno = EBADF;
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
    int flags = O_WRONLY | O_CREAT;

    int fd1 = open("test.txt", flags,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd1 == -1) {
        perror("open");
        return 1;
    }



    int fd2 = my_dup(fd1);
    if (fd2 == -1) {
        perror("my_dup");
        return 1;
    }
    
    printf("fd1: %d, fd2: %d\n", fd1, fd2);

    int fd3 = my_dup2(fd1, 12);
    if (fd3 == -1) {
        perror("my_dup2");
        return 1;
}



    printf("fd1: %d, fd3: %d\n", fd1, fd3);
    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}