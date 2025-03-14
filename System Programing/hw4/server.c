#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <semaphore.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>

#define MAX_BUF 1024
#define FIFO_DIRECTORY "/tmp/"

#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
//#define CHILDREN 5
typedef struct {
    int logfd;
    int childNum;
    sem_t *semaphore;
    char arr[100];
    char message[100];
} arg_struct;

void readF(char *filename, int lineNumber,int readfd);
void writeT(char* filename, int lineNumber, char* newLine);
int compare_strings(char *str1, char *str2);
void listFun(char * arr);
void readFfun(char * message,char *arr);
void writeTfun(char * message);
void uploadFun(char * message,char * arr);
void download(char * message,char * arr);


void handle_sigint(int sig) 
{ 
    printf("Caught signal %d\n", sig);
    printf("Exit Server\n");
    
    exit(1);
}

void *ThreadFunction(void *arguments) {

        
        arg_struct* args = (arg_struct*)arguments;
        char childFifo[100] ="";
        char tmp[100] ="";
        
        //printf("fifo:%s\n",arr);
        
        int childFd;
        char pidStr[100];
        sprintf(pidStr, "%ld\n", pthread_self()); 
        

        write(args->logfd,"\nThread Created.\nThread ID: ",strlen("\nThread Created.\nThread ID: "));
        write(args->logfd,pidStr,strlen(pidStr));
        
        printf("Child process PID:%d\n",getpid()); 
        while (1) {
            //printf("file open during  arr:%s\n",arr);
            childFd = open(args->arr, O_RDONLY);
            if(childFd < 0){
                printf("file name:%s\n",args->arr);
                printf("file open error:%d\n",childFd);
                write(args->logfd,"Fifo file Cant Open\n",strlen("Fifo file Cant Open\n"));
                sem_post(args->semaphore);
                pthread_exit(NULL);

            }
            int serverByte =0;
        
            serverByte = read(childFd, args->message, sizeof(args->message));
            printf("Client Comment>>%s", args->message);
            write(args->logfd,"\n>>Client Comment: ",strlen("\n>>Client Comment: "));
            write(args->logfd,args->message,strlen(args->message));
            if(serverByte == -1){
                printf("Serverr Error\n");
                write(args->logfd,"Server Error.\n",14);
                sem_post(args->semaphore);
                pthread_exit(NULL);
            }
            
            //message[strcspn(message, "\n")] = 0;
        
            
            if(strncmp(args->message,"list",4) == 0){
                listFun(args->arr);
            }
            else if(strncmp(args->message,"readF",5) == 0){
                readFfun(args->message,args->arr);
            }
            else if(strncmp(args->message,"writeT",6) == 0){
                
                writeTfun(args->message);


            }
            else if(strncmp(args->message,"upload",6) == 0){
                uploadFun(args->message,args->arr);
            }
            else if(strncmp(args->message,"download",8) == 0){                   
                download(args->message,args->arr);                    
            }
            else if(strncmp(args->message,"quit",4) == 0){
                printf(">>Log file genaritng\n");
                printf(">> client0%d disconnected..\n",args->childNum); 
                write(args->logfd,"Client Process Quit\n",sizeof("Client Process Quit\n"));                      
                sem_post(args->semaphore);
                
                pthread_exit(NULL);
                
            }
            else if(strncmp(args->message,"killServer",10) == 0){
                write(args->logfd,"Process Killed\n",strlen("Process Killed\n")+1);
                write(args->logfd,"kill signal from client terminating...\n",strlen("kill signal from client terminating...\n"));
                printf("kill signal from client0%d.. terminating...\n",args->childNum);
                printf(">>Process Killed\n");
                sem_post(args->semaphore);
                close(args->logfd);
                
                pthread_exit(NULL);
            } 
            close(childFd);

        }
        sem_post(args->semaphore);
        pthread_exit(NULL); // Important: child should exit here!
        printf(">> client01 disconnected...\n");
        
        
        
    
                
}

int main(int argc, char *argv[]) {
    int fd;
    // FIFO file path
    
    char myfifo[100] = "";
    char arr[80] ="";
    char slash[100] = "/";
    int childPid;
    int pid= getpid();
    char pidSrt[100] ="";
    char message[1000] ="";
        // Process2 reads
    char clientPidStr[100] ="";
    int clientCount = atoi(argv[2]);
    char samName[100] ="sam";
     char logFile[100] ="";
    char tmpChar[50] ="";
    int childCount =0;
    
    if(argc != 4 ){
        printf("input error");
        return 0;
    }
    int threadNum = atoi(argv[3]); 
    pthread_t threadpool[threadNum]; // thread num;

    printf("Thread Pool Size:%d\n",threadNum);

    signal(SIGINT, handle_sigint); 
    strcat(myfifo,FIFO_DIRECTORY);   
    sprintf(pidSrt, "%d", getpid());
    strcat(logFile,pidSrt);
    strcat(logFile,".log");
    


    if (chdir(argv[1]) != 0) {
        perror("cant open\n");
        mkdir(argv[1],0666);
        if (chdir(argv[1]) != 0){
            perror("cant open\n");
        }
    }
    int logfd = open(logFile,O_WRONLY| O_CREAT, S_IRUSR | S_IWUSR ); 
    write(logfd,">> Server Started PID:",strlen(">> Server Started PID:"));
    write(logfd,pidSrt,strlen(pidSrt));
    write(logfd,"\nEntered The Given Directory\nDirectory: ",strlen("Entered The Given Directory\nDirectory: "));
    write(logfd,argv[1],strlen(argv[1]));
    strcat(samName,pidSrt);

   
    printf(">> Server Started PID:%s\n",pidSrt);
    printf(">> waiting for clients...\n");
    strcat(myfifo,pidSrt);
    printf("Directory: %s\n",argv[1]);
    printf("Max Client Count:%d\n",clientCount);
    write(logfd,"\nMax Client Count:  ",strlen("Max Client Count:  "));
    sprintf(tmpChar, "%d\n", clientCount);
    write(logfd,tmpChar,strlen(tmpChar));
    //strcat(myfifo,pidSrt);
    //printf("Fifo Directory:%s",argv[1]);
    //printf("\nmyfifo:%s",myfifo);

    strcat(samName,pidSrt);
    sem_t *semaphore = sem_open(samName, O_CREAT | O_EXCL, SEM_PERMS, clientCount);

    if (semaphore == SEM_FAILED) {
        perror("sem_open/sem_unlink failed");
        exit(EXIT_FAILURE);
    }

    arg_struct args;
    
    /*for (int i = 0; i < threadNum; ++i) {
        
    }*/


    mkfifo(myfifo, 0666);
    int value;
    int tryConnect =1;
    int threadCounter =0;
        while(1){
            
            fd = open(myfifo, O_RDWR);
           
            if( fd <0){
                printf("fifo:%s\n",myfifo);
                printf("Open file Error\n");
                
            }
            
            read(fd, arr, sizeof(arr));
            printf("client message:%s\n",arr);
            
            sem_getvalue(semaphore, &value);
            printf("Semafor Value:%d\n",value);
            write(logfd,"\nSemafor Value:  ",strlen("Semafor Value:  "));
            sprintf(tmpChar, "%d\n", value);
            write(logfd,tmpChar,strlen(tmpChar));
            //printf("arr:%s\n",arr);
            if(compare_strings(arr,"try\0") == 1){
                
                
                int tryfd = open(arr, O_WRONLY);
                if(tryfd <0){
                    printf("try file cant open\n");
                    tryConnect =0;
                }             
                else{
                    if(value==0){
                        write(tryfd,"no\0",3);
                        tryConnect =0;
                    }
                    else{
                        
                        write(tryfd,"yes\0\n",4);
                        tryConnect =0;
                        //printf("semafor serbest ise arr:%s\n",arr);
                    }
                }
                
               
                close(tryfd);
            }
            
            if(tryConnect == 1){
                strcpy(args.arr,arr);
                strcpy(args.message,message);
                args.semaphore = semaphore;
                args.childNum = childCount;
                args.logfd = logfd;

                
                
                write(logfd,"Waiting for Critical Region\n",strlen("Waiting for Critical Region\n"));
                
                sem_wait(semaphore);
                write(logfd,"Enter Critical Region\n",strlen("Enter Critical Region\n"));
                childCount++;
               
                printf(">> Client PID %s connected as client0%d\n",pidSrt,childCount);
                close(fd);
                
                pthread_create(&threadpool[threadCounter++], NULL, ThreadFunction, (void*)&args);
                
               
                //pthread_join(threadpool[threadCounter++], NULL);
                
                
            }
            
            tryConnect =1;
            close(fd);
        }

    
      
        
    
    return 0;
}

void readF(char *filename, int lineNumber,int readfd) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    int count = 1;
    char line[256];
    char fileStr[1000];
    if (lineNumber != -1) {
        // print specific line
        while (fgets(line, sizeof(line), file) != NULL) {
            if (count == lineNumber) {
                printf("Line %d: %s\n", count, line);
                strcat(fileStr,line);
                break;
            }
            else {
                count++;
            }
        }
    } else {
        // print all lines
        while (fgets(line, sizeof(line), file) != NULL) {
            strcat(fileStr,line);
            printf("%s", line);
        }
    }
    write(readfd, fileStr, strlen(fileStr) + 1);
    fclose(file);
}

void writeT(char* filename, int lineNumber, char* newLine) {
    FILE* file;
    int fd;
    char line[256];
    char temp[10000] = "";  // to store all lines
    int count = 1;
    struct flock lock;
    file = fopen(filename, "r");
    fd = fileno(file);
    if (file == NULL) {
        // if file does not exist, create it and write to it
        file = fopen(filename, "w");
        fprintf(file, "%s\n", newLine);
    } else {
        lock.l_type = F_WRLCK; /* Yazma kilidi */
        lock.l_whence = SEEK_SET; /* Başlangıçtan itibaren */
        lock.l_start = 0; /* Başlangıç offset */
        lock.l_len = 0; 
        if (fcntl(fd, F_SETLK, &lock) == -1) {
            perror("fcntl");
            
        }

        while (fgets(line, sizeof(line), file) != NULL) {
            if (count == lineNumber) {
                // change line
                strcat(temp, newLine);
                strcat(temp, "\n");
            } else {
                // keep line
                strcat(temp, line);
            }
            count++;
        }
        if (lineNumber < 0 || lineNumber >= count) {
            // add line to the end
            strcat(temp, newLine);
            strcat(temp, "\n");
        }
        fclose(file);

        // write all lines
        file = fopen(filename, "w");
        fprintf(file, "%s", temp);
    }
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    fclose(file);
}

int compare_strings(char *str1, char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // Check if both strings are at least 3 characters long
    if (len1 < 3 || len2 < 3) {
        printf("Her iki dizi de en az 3 karakter uzunluğunda olmalıdır.\n");
        return 0;
    }

    // Extract the last 3 characters from each string
    char *last_three_str1 = &str1[len1-3];
    char *last_three_str2 = &str2[len2-3];

    // Compare the last 3 characters and print the result
    if (strcmp(last_three_str1, last_three_str2) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void listFun(char * arr){
    struct dirent *de;  // dirent yapısı için pointer
    DIR *dr = opendir("."); // Geçerli dizini aç
    if (dr == NULL){
        printf("Directory Can Not Open\n" );
        
    }
    char list[200] ="";
    while ((de = readdir(dr)) != NULL){ // Tüm dosyaları oku ve isimlerini yazdır
        printf("%s\n", de->d_name);
        strcat(list,de->d_name);
        strcat(list,"\n");
        
    }
    
    char listfifo[100] ="";
    int listfd;
    strcat(listfifo,arr);
    strcat(listfifo,"l\0");
    printf("listfifo:%s\n",listfifo);

    listfd = open(listfifo, O_WRONLY);
    if(listfd <0 ){
        printf("List Comment Cant Open File\n");
    }
    strcat(list,"\0");
    write(listfd, list, strlen(list)+1);
    close(listfd);    
    closedir(dr);    // Dizini kapat
}

void readFfun(char * message,char *arr){
    char filename[256]="";
    char input[256]="";
    int lineNumber=0;
    char file[1000] ="";

    char readfifo[100]="";
    int readfd;
    char buf[1000] ="";
    strcat(readfifo,arr);
    strcat(readfifo,"r\0");
    readfd = open(readfifo, O_WRONLY);
    if(readfd < 0){
        printf("Readf Fifo File Cant open\n");
        write(readfd,"Error\0",6);
    }
    else{
        if (sscanf(message, "readF %s %d", filename, &lineNumber) == 2) {
            // both filename and lineNumber are provided
            readF(filename, lineNumber, readfd);
        } else if (sscanf(message, "readF %s", filename) == 1) {
            // only filename is provided
            readF(filename, -1,readfd);
        } else {
            printf("Invalid command\n");
        }
        
        close(readfd);
    }
}

void writeTfun(char * message){
    char filename[256] ="";
    char newLine[256] ="";
    int lineNumber;

    if (sscanf(message, "writeT %s %d %[^\n]", filename, &lineNumber, newLine) == 3) {
        // filename, lineNumber and newLine are provided
        writeT(filename, lineNumber, newLine);
    } else if (sscanf(message, "writeT %s %[^\n]", filename, newLine) == 2) {
        // only filename and newLine are provided
        writeT(filename, -1, newLine);
    } else {
        printf("Invalid command\n");
    }
}

void uploadFun(char * message,char * arr){
    char buf[1000]="";
    char filename[256] ="";
    char newLine[256] ="";
    if(sscanf(message, "upload %s", filename) !=1){
        printf("sscanf has error\n");
    }
    printf("filename:%s\n",filename);
    int file = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (0 > file) {
        printf("Unable to open file:%s\n",filename);
        
    }
    else{
        int byte =0;
        char uploadfifo[100]="";
        int upload;
        
        strcat(uploadfifo,arr);
        strcat(uploadfifo,"u\0");

        int uploadfd = open(uploadfifo,O_RDONLY);
        if(uploadfd < 0){
            printf("Upload file cant open");
        }
        else{
            while ((byte = read(uploadfd, buf, sizeof(buf))) > 0) {
            if(byte <=1 ){
                printf("byte error:%d\n",byte);
                printf("buf:\n%s\n",buf);
                break;
            }
            printf("byte:%d\n",byte);
            printf("Uploadin file..:\n%s",buf);
            write(file, buf,byte);
            }
        
            //write(file,"\n",1);
            printf("close file\n");
            close(uploadfd);
            close(file);
            
        }
        
    }
    
}

void download(char * message,char * arr){
    char buf[1000]="";
    char filename[256] ="";
    char newLine[256] ="";
    int flag =1;
    struct flock lock;
    char downloadfifo[100]="";
  
    strcat(downloadfifo,arr);
    strcat(downloadfifo,"d\0");
    int downloadfd = open(downloadfifo, O_WRONLY);
    if(downloadfd <0 ){
        printf("download file cant open\n");
        write(downloadfd,"error\0",6);
        flag =0;
    }
    else{
        if(sscanf(message, "download %s", filename) == 1){
            printf("filename:%s\n",filename);
            filename[strcspn(filename, "\n")] = 0;
        }
        
        
        int file = open(filename, O_RDONLY);
        if ( 0 > file) {
            printf("File not found:%s\n",filename);
            write(downloadfd,"error\0",6);
            flag =0;
        }
        else{
            int bytesRead =0;
            lock.l_type = F_WRLCK; /* Yazma kilidi */
            lock.l_whence = SEEK_SET; /* Başlangıçtan itibaren */
            lock.l_start = 0; /* Başlangıç offset */
            lock.l_len = 0; 
            if (fcntl(file, F_SETLK, &lock) == -1) {
                perror("fcntl");
                
            }
            if(flag == 1){
                while (flag == 1 && (bytesRead = read(file, buf, 1000)) > 0) {
                printf("print:%s\n",buf);
                printf("byte:%d\n",bytesRead);
                write(downloadfd, buf, bytesRead);
                
                }
                close(downloadfd);
            }
            lock.l_type = F_UNLCK;
            fcntl(file, F_SETLK, &lock);
            
        }
    }

}