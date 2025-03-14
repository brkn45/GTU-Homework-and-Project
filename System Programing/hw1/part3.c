#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>



int main() {
    char buffer[100];

    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return 1;
 }


    const char *text = "Hello, world!";
    if (write(fd, text, strlen(text)) != strlen(text)) {
        perror("write");
        close(fd);
        return 1;
}


    int dup_fd = dup(fd);
    if (dup_fd == -1) {
        perror("dup");
        close(fd);
        return 1;
 }


    off_t offset1 = lseek(fd, 0, SEEK_CUR);
    off_t offset2 = lseek(dup_fd, 0, SEEK_CUR);


    if (offset1 != offset2) {
        fprintf(stderr, "File offsets do not match: %lld vs %lld\n", (long long) offset1, (long long) offset2);
    } else {
    printf("File offsets match: %lld\n", (long long) offset1);
 }


    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        close(dup_fd);
        return 1;
    }


    offset1 = lseek(fd, 0, SEEK_CUR);
    offset2 = lseek(dup_fd, 0, SEEK_CUR);

    if (offset1 != offset2) {
        fprintf(stderr, "File offsets do not match after lseek: %lld vs %lld\n", (long long) offset1, (long long) offset2);
    } else {
        printf("File offsets match after lseek: %lld\n", (long long) offset1);
    }


    ssize_t bytes_read = read(dup_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        close(dup_fd);
        return 1;
}

    buffer[bytes_read] = '\0';
    printf("Read from duplicated file descriptor: %s\n", buffer);
    close(fd);
    close(dup_fd);
    return 0;
}