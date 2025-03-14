#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 20

int child_pid[MAX_ARGS];
int child_count = 0;

void execute_cmd(char *cmd, int input_fd, int output_fd);
void parse_and_run_cmd(char *cmd_line);


void sigint_handler(int signum) {
    printf("\nReceived SIGINT signal\n");
    for (int i = 0; i < child_count; i++) {
        kill(child_pid[i], SIGINT);
    }
    child_count = 0;
}

void sigterm_handler(int signum) {
    printf("\nReceived SIGTERM signal\n");
    for (int i = 0; i < child_count; i++) {
        kill(child_pid[i], SIGTERM);
    }
    child_count = 0;
}

void sigkill_handler(int signum) {
    printf("\nReceived SIGKILL signal\n");
    for (int i = 0; i < child_count; i++) {
        kill(child_pid[i], SIGKILL);
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);
    signal(SIGKILL, sigkill_handler);

    char cmd_line[MAX_CMD_LENGTH];

    while (1) {
        printf("> ");
        if (fgets(cmd_line, MAX_CMD_LENGTH, stdin) == NULL) {
            perror("Error reading command");
            continue;
        }

        if (strncmp(cmd_line, ":q", 2) == 0) {
            int pid = getpid();
            /*int result = kill(pid, SIGKILL);

            if (result != 0) {
                perror("Error killing process");
                exit(1);
            }
            */

           exit(0);
        }

        parse_and_run_cmd(cmd_line);
    }

    return 0;
}


void parse_and_run_cmd(char *cmd_line) {
    char *cmd;
    int pipefd[2];
    int input_fd = -1;
    
    while ((cmd = strsep(&cmd_line, "|")) != NULL) {
        int output_fd = -1;

        if (cmd_line) {
            if (pipe(pipefd) == -1) {
                perror("Error creating pipe");
                return;
            }
            output_fd = pipefd[1];
        }
        execute_cmd(cmd, input_fd, output_fd);
        if (input_fd != -1) {
            close(input_fd);
        }

        if (output_fd != -1) {
            close(output_fd);
        }
        input_fd = pipefd[0];
    }
}

void log_child_process(pid_t pid, char *cmd) {
    char log_file_name[32];
    time_t t = time(NULL);
    strftime(log_file_name, sizeof(log_file_name), "%Y%m%d_%H%M%S.log", localtime(&t));

    FILE *log_file = fopen(log_file_name, "a");
    if (log_file) {
        fprintf(log_file, "PID %d: %s\n", pid, cmd);
        fclose(log_file);
    } else {
        perror("Error opening log file");
    }
}

void execute_cmd(char *cmd, int input_fd, int output_fd) {
    char *args[MAX_ARGS];
    int arg_count = 0;

    args[arg_count++] = strtok(cmd, " \n");
    while (args[arg_count - 1] != NULL && arg_count < MAX_ARGS - 1) {
        if (strcmp(args[arg_count - 1], "<") == 0) {
            char *filename = strtok(NULL, " \n");
            if (filename) {
                input_fd = open(filename, O_RDONLY);
                if (input_fd == -1) {
                    perror("Error opening input file");
                    return;
                }
            }
        } else if (strcmp(args[arg_count - 1], ">") == 0) {
            char *filename = strtok(NULL, " \n");
            if (filename) {
                output_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (output_fd == -1) {
                    perror("Error opening output file");
                    return;
                }
            }
        } else {
            arg_count++;
        }
        args[arg_count - 1] = strtok(NULL, " \n");
    }
    args[arg_count] = NULL;

    pid_t pid = fork();
    if (pid == 0) {
        if (input_fd != -1) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != -1) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        if (execvp(args[0], args) == -1) {
            perror("Error executing command");
            exit(1);
        }
    } else if (pid > 0) {
        if (input_fd != -1) {
            close(input_fd);
        }
        if (output_fd != -1) {
            close(output_fd);
        }

        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("Error waiting for child process");
        } else {
            log_child_process(pid, cmd);
        }
    } else {
        perror("Error creating child process");
    }
}



