#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <sys/time.h>

#define PATH 256

typedef struct {
    int src_fd;    
    int dest_fd;   
    char* src_file; 
    char* dest_file; 
} file_copy_t;

// Define a structure to control access to the buffer
typedef struct {
    file_copy_t* buffer; 
    int size;         
    int in;           
    int out;          
    pthread_mutex_t mutex; // mutex lock
    pthread_cond_t not_empty; 
    pthread_cond_t not_full; 
} buffer_t;

// Global variables to use in the main program
buffer_t buffer; // Shared Buffer
int done = 0; // Completion status

int file_count =0;
char bufferT[250];
int total_bytes =0;
void* producer(void* args);

void* consumer(void* args);

void sigterm_handler(int signum) {
    printf("\nFile and Directory is Copyed. Program will Close\n");
    exit(EXIT_SUCCESS);
}


int main(int argc, char* argv[]) {
    // Input control
    if(argc != 5) {
        printf("Program <buffer size> <number of consumers> <source directory> <destination directory>\n");
        return EXIT_FAILURE;
    }
    struct timeval start_time, end_time;
    printf("Start program\n");
    
    gettimeofday(&start_time, NULL);

    int buffer_size = atoi(argv[1]);
    int num_consumers = atoi(argv[2]);
    char* src_dir = argv[3];
    char* dest_dir = argv[4];
    
    //signal function
    signal(SIGINT, sigterm_handler);
    
    buffer.buffer = malloc(sizeof(file_copy_t) * buffer_size);
    buffer.size = buffer_size;
    buffer.in = buffer.out = 0;

   
    pthread_mutex_init(&buffer.mutex, NULL);
    pthread_cond_init(&buffer.not_empty, NULL);
    pthread_cond_init(&buffer.not_full, NULL);

   
    pthread_t producer_thread;
    pthread_t* consumer_threads = malloc(sizeof(pthread_t) * num_consumers);

    //One producer thread creadted
    pthread_create(&producer_thread, NULL, producer, (void*)argv);

    //User input count thread creadted
    for(int i = 0; i < num_consumers; i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }

    // Waiting for threads to complete
    pthread_join(producer_thread, NULL);
    printf("Press Ctrl+C to Exit\n");
    for(int i = 0; i < num_consumers; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    // buffer clean
    free(buffer.buffer);
    free(consumer_threads);

    gettimeofday(&end_time, NULL);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Total time : %.3f saniye\n", elapsed_time);
    printf("Total file: %d\n", file_count);
    printf("Total copyed byte: %d\n", total_bytes);

    return EXIT_SUCCESS;
}


void* producer(void* args) {
    
    char** argv = (char**)args;
    char* src_dir = argv[3];
    char* dest_dir = argv[4];
    char src_path[PATH], dest_path[PATH];
    struct stat entry_stat;

    int src_fd1 =1;
    // Open directories
    DIR* src_d = opendir(src_dir);
    if(src_d == NULL) {
        perror("Failed to open source directory");
        return NULL;
    }

    
    DIR* dest_d = opendir(dest_dir);
    if(dest_d == NULL) {
        // Create the directory in case the target directory cannot be opened
        if(mkdir(dest_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
            perror("Failed to create destination directory");
            closedir(src_d);
            return NULL;
        }
        // Open new Created directoryes
        dest_d = opendir(dest_dir);
        if(dest_d == NULL) {
            perror("Failed to open destination directory");
            closedir(src_d);
            return NULL;
        }
    }

    // Processing files in the source directory
    struct dirent* file;
    while((file = readdir(src_d)) != NULL) {
        
        if(strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
            continue;

        snprintf(src_path, sizeof(src_path) +2, "%s/%s", argv[3], file->d_name);
        snprintf(dest_path, sizeof(dest_path)+2, "%s/%s", argv[4], file->d_name);
        stat(src_path, &entry_stat);
        if(S_ISDIR(entry_stat.st_mode)) {  // If it's a directory
           // Creation of the target directory
            mkdir(dest_path, 0777);
            char* new_dirs[5];
            new_dirs[3] = strdup(src_path);
            new_dirs[4] = strdup(dest_path);

            // Calling the generator function for nested directories with recursively
            producer((void*)new_dirs);

            
            free(new_dirs[3]);
            free(new_dirs[4]);
        } else {  // If it's a file
            file_count++;
            char src_file[strlen(src_dir) + strlen(file->d_name) + 2];
            snprintf(src_file, sizeof src_file, "%s/%s", src_dir, file->d_name);
            
            char dest_file[strlen(dest_dir) + strlen(file->d_name) + 2];
            snprintf(dest_file, sizeof dest_file, "%s/%s", dest_dir, file->d_name);

            
            int src_fd = open(src_file, O_RDONLY);
            if(src_fd == -1) {
                perror("Failed to open source file");
                continue;
            }
            
            int dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if(dest_fd == -1) {
                perror("Failed to open destination file");
                close(src_fd);
                continue;
            }
            // take lock
            pthread_mutex_lock(&buffer.mutex);

            while((buffer.in + 1) % buffer.size == buffer.out) { 
                 read(src_fd1, bufferT, sizeof(bufferT));
                pthread_cond_wait(&buffer.not_full, &buffer.mutex);
                
            }
            buffer.buffer[buffer.in].src_fd = src_fd;
            buffer.buffer[buffer.in].dest_fd = dest_fd;
            buffer.buffer[buffer.in].src_file = strdup(src_file);
            buffer.buffer[buffer.in].dest_file = strdup(dest_file);
            buffer.in = (buffer.in + 1) % buffer.size;

            pthread_cond_signal(&buffer.not_empty); // Warn consumer threads
            pthread_mutex_unlock(&buffer.mutex);
        }

        
        
    }

    
    closedir(src_d);
    closedir(dest_d);

    
    pthread_mutex_lock(&buffer.mutex);
    done = 1;
    pthread_cond_broadcast(&buffer.not_empty); 
    pthread_mutex_unlock(&buffer.mutex);
    
    return NULL;
}

void* consumer(void* args) {
    
    while(1) {
        pthread_mutex_lock(&buffer.mutex);

        // If the buffer is empty and the manufacturer has set the finished flag, terminate the thread
        if(done && buffer.in == buffer.out) {
            pthread_mutex_unlock(&buffer.mutex);
            return NULL;
        }

        // Wait if buffer is empty
        printf("Thread Waiting For Task\n");
        while(!done && buffer.in == buffer.out)
            pthread_cond_wait(&buffer.not_empty, &buffer.mutex);
        
        // Retrieving file information from buffer
        int src_fd = buffer.buffer[buffer.out].src_fd;
        int dest_fd = buffer.buffer[buffer.out].dest_fd;
        char* src_file = buffer.buffer[buffer.out].src_file;
        char* dest_file = buffer.buffer[buffer.out].dest_file;
        buffer.out = (buffer.out + 1) % buffer.size;

        pthread_cond_signal(&buffer.not_full); 
        pthread_mutex_unlock(&buffer.mutex);
       
        // Dosyanın kopyalanması
        char buf[100];
        int size=1;
        
        FILE *fp = fdopen(src_fd,"r");
        if(feof(fp)){
            //printf("feof\n");
            continue;
        }
        while(size > 0) {
            
            memset(buf, 0, sizeof(buf));

            size = read(src_fd, buf, sizeof(buf));
            total_bytes = total_bytes +size;
            //printf("while dongu\n");
            if(size < 1){
                break;
            }
            if(write(dest_fd, buf, size) != size) {
                perror("Failed to write to destination file");
            }
        }
        //printf("while alti\n");
        if(size < 0) {
            perror("Failed to read from source file");
        }

        // Dosyaların kapatılması
        close(src_fd);
        close(dest_fd);

        // Tamamlama durumunun yazdırılması
        printf("Successfully copied\n");
        printf("\nSource:      %s\nDestination: %s\n\n", src_file, dest_file);
        
        free(src_file);
        free(dest_file);
       
    }
}
