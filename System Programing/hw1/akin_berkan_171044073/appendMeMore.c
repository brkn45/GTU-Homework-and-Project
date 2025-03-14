#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {

if (argc < 3 || argc > 4) {

    fprintf(stderr, "Usage: %s filename num-bytes [x]\n", argv[0]); //*
    exit(1);

    }

    char *filename = argv[1];
    int num_bytes = atoi(argv[2]);
    int use_lseek = (argc == 4 && argv[3][0] == 'x');

    int flags = O_WRONLY | O_CREAT;

    if (!use_lseek)
    {
    flags |= O_APPEND;
    }

    int fd = open(filename, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }


    for (int i = 0; i < num_bytes; i++) {
        if (use_lseek) {
            lseek(fd, 0, SEEK_END);
    }
        write(fd, "a", 1);
    }

    close(fd);
    return 0;

}