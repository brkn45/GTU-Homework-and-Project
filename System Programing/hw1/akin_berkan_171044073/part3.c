#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>



int main() {
    char buffer[100];
    int flags =  O_CREAT | O_RDWR;
    int fd1 = open("test2.txt", flags,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    
    if (fd1 == -1 ) {
        perror("open fd1");
        return 1;
    }  
    printf("----------- Test #1 ----------\n");

    int dup_fd = dup(fd1);
    if (dup_fd == -1) {
        perror("dup");
        close(fd1);
        return 1;
    }  

    off_t offset1 = lseek(fd1, 0, SEEK_CUR);
    off_t offsetdub = lseek(dup_fd, 0, SEEK_CUR);

    if (offset1 != offsetdub) {
        printf("File Offsets Diffirent\n");
        printf("File offset1: %lld  \nFile offsetdub : %lld\n", (long long) offset1, (long long) offsetdub);

    } 
    else {
        printf("File offsets match\n");
        printf("File offset1: %lld  \nFile offsetdub : %lld\n", (long long) offset1, (long long) offsetdub);
    }

   
       
    printf("----------- Test #2 ----------\n");
    const char *text = "Hello world!";
    int byte_num = write(fd1, text, strlen(text)) ;
    if (byte_num  != strlen(text)) {
        perror("write");
        close(fd1);
        return 1;
    }

    
    printf("Write File Hello world!\n");
    offset1 = lseek(fd1, 0, SEEK_CUR);
    offsetdub = lseek(dup_fd, 0, SEEK_CUR);

    if (offset1 != offsetdub) {
        printf("File Offsets Diffirent\n");
        printf("File offset1: %lld  \nFile offsetdub : %lld\n", (long long) offset1, (long long) offsetdub);

    } 
    else {
        printf("File offsets match\n");
        printf("File offset1: %lld  \nFile offsetdub : %lld\n", (long long) offset1, (long long) offsetdub);
    }

    printf("----------- Test #3 ----------\n");
    if (lseek(fd1, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fd1);
        close(dup_fd);
        return 1;
    }
    offset1 = lseek(fd1, 0, SEEK_CUR);
    if (offset1 != offsetdub) {
        printf("File Offsets Diffirent\n");
        printf("File offset1: %lld  \nFile offsetdub : %lld\n", (long long) offset1, (long long) offsetdub);

    } 
    else {
        printf("File offsets match\n");
        printf("File offset1: %lld  \nFile offsetdub : %lld\n", (long long) offset1, (long long) offsetdub);
    }


    ssize_t bytes_read = read(dup_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read");
        close(fd1);
        close(dup_fd);
        return 1;
}

    buffer[bytes_read] = '\0';
    printf("Read from duplicated file descriptor: %s\n", buffer);
    close(fd1);
    close(dup_fd);
    return 0;
}