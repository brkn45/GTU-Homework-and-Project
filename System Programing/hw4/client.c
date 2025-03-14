#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#define MAX_BUF 1024
int helpDisplay(char message[100]);
int compare_strings(char *str1, char *str2); 
void listfun(char * childFifo,int *fd);
void readFfun(char * childFifo);
void uploadFun(char * message,char * childFifo);
void downloadFun(char* message,char * childFifo);
void quitFun(char * childFifo,int * childFd);


int childFd;

void sigint_handler(int signal) {
    printf("\nTaken signal.\nClient quit program.\n");
    write(childFd,"quit",strlen("quit"));
    exit(0);
}

int main(int argc, char *argv[]) {
    int fd;
    // FIFO file path
    
    char myfifo[100] = "/tmp/";
    char childFifo[100] = "/tmp/";
    // Creating the named pipe (FIFO) with read/write permissions
    if(argc !=3){
        printf("error");
        return 0;
    }
    signal(SIGINT, sigint_handler);
       
    strcat(myfifo,argv[2]);
    //mkfifo(myfifo, 0666);
    char arr[80];
    char str[50];
    char slash[100] = "/";
        // Process1 writes
    
    
    char message[1000] ="";
    fd = open(myfifo, O_RDWR);
         
    sprintf(str, "%d", getpid());
    //strcat(slash,str);
    //strcat(childFifo,str);
    //strcat(childFifo,slash);
    childFifo[strcspn(childFifo, "\n")] = 0;
    strcat(childFifo,str);
    
    char tmpfifo[100] = "";
    int tryfd;
    printf("argv1:%s\n",argv[1]);
    if(strncmp(argv[1],"tryConnect",10) == 0 ){
        
        printf("try girdi\n");
        
        strcat(tmpfifo,childFifo);
        strcat(tmpfifo,"try");
        mkfifo(tmpfifo,0666);
        write(fd,tmpfifo,strlen(tmpfifo) +1);
         
        tryfd = open(tmpfifo,O_RDONLY);

        if(tryfd < 0){
            printf("cant open try fifo");
        }
        
        
        read(tryfd,message,sizeof(message));
        printf("try message:%s\n",message);
        if(strncmp(message,"no",2) == 0){
            printf("Que is full\n");
            close(tryfd);
            
            return -1;
        }
        
    }
    
    strcat(childFifo,"\0");
    printf("myfifo:%s\n",childFifo);
    write(fd, childFifo, strlen(childFifo) +1); 
    printf("send message: %s\n",childFifo);
    close(tryfd);
    unlink(tmpfifo);

    



    close(fd);
    mkfifo(childFifo,0666);
    
    
    while(1){
        
        
        childFd = open(childFifo, O_WRONLY);
        if(childFd < 0){
            printf("file open error:%s\n",childFifo);
            write(childFd, "quit", strlen("quit") + 1);
            break;
        }
        printf(">> Enter comment : ");
        fgets(message, 1000, stdin);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        if(strlen(message) <1){
            fgets(message, 100, stdin);
        }
        //message[strcspn(message, "\n")] = 0;
        write(childFd, message, strlen(message) + 1);
        
        
        
        helpDisplay(message);

        if(strncmp(message,"list",4) == 0){
            listfun(childFifo,&fd);
        }
        else if(strncmp(message,"readF",5) == 0){
            readFfun(childFifo);
        }
        else if(strncmp(message,"writeT",6) == 0){
            printf("Printed file");

        }
        else if(strncmp(message,"upload",6) == 0){
            uploadFun(message,childFifo);
            
        }
        else if(strncmp(message,"download",8) == 0){
            downloadFun(message,childFifo);
           
        
        }
        else if(strncmp(message,"quit",4) == 0){
            quitFun(childFifo,&childFd);
           
        } 
        else if(strncmp(message,"killServer",10) == 0){
            printf("waiting for logfile ...\n");
            printf("logfile write request granted...\n");
            printf("killed Server\n");
            kill(atoi(argv[2]),SIGKILL);
            exit(1);
        }   
    }
    
    return 0;
}

int helpDisplay(char message[100]){

    
    if(strncmp(message,"help readF",10) ==0){
        printf("readF <file> <line #>\n  display the #th line of the <file>, returns with an  \n  error if <file> does not exists\n");
    }
    else if(strncmp(message,"help list",9) ==0){
        printf("list\n");
        printf("sends a request to display the list of files in Servers directory.\n");
    }
    else if(strncmp(message,"help writeT",11) ==0){
        printf("writeT <file> <line #> <string>\n");
        printf("request to write the content of “string” to the #th line the <file>, if the line # is not given writes to the end of file. If the file does not exists in Servers directory creates and edits the file at the same time\n");
    }
    else if(strncmp(message,"help upload",11) == 0){
        printf("upload <file>\n");
        printf("uploads the file from the current working directory of client to the Servers directory (beware of the cases no file in clients current working directory and file with the same name on Servers side)\n");
    }
    else if(strncmp(message,"help download",13) == 0){
        printf("download <file>");
        printf("request to receive <file> from Servers directory to client side\n");

    }
    else if(strncmp(message,"help quit",9) ==0 ){
        printf("quit\n");
        printf("Send write request to Server side log file and quits\n");
    }
    else if(strncmp(message,"help killServer",15) ==0 ){
        printf("killServer\n");
        printf("Sends a kill request to the Server\n");
    }
    else if(strncmp(message,"help",4) ==0){
        printf("Available comments are :\n");
        printf("help, list, readF, writeT, upload, download, quit, killServer\n");
    }
    else{
        return -1;
    }
        
    return 0;
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

void listfun(char * childFifo,int * fd){
    char listfifo[100] ="";
            int listfd;
            char buf[1000]="";
            //close(childFd);
            strcat(listfifo,childFifo);
            strcat(listfifo,"l\0");
            mkfifo(listfifo,0666);
            listfd = open(listfifo, O_RDONLY);
            if(listfd < 0){
                printf("Can't Open Child Fifo\n");
            }
            
            read(listfd,buf, sizeof(buf));
            printf("%s\n",buf);
            close(*fd);
            unlink(listfifo);
}

void readFfun(char * childFifo){
    printf("readf girdi\n");
            char readfifo[100]="";
            int readfd;
            char buf[1000]="";
            
            strcat(readfifo,childFifo);
            strcat(readfifo,"r\0");
            mkfifo(readfifo,0666);
            readfd = open(readfifo, O_RDONLY);
            if(readfd <0 ){
                printf("ReadF file Cant Open\n");
            }
            else{
                read(readfd, buf, sizeof(buf));
                printf("%s\n",buf);
            }
            
            
            
            close(readfd);
            unlink(readfifo);
}

void uploadFun(char * message,char * childFifo){
    char filename[256] ="";
            char newLine[256] ="";
            char buf[1000] ="";
            int bytesRead;

            char uploadfifo[100]="";
            int upload;
            struct flock lock;


            if(sscanf(message, "upload %s", filename) == 1){
                printf("filename:%s\n",filename);
                filename[strcspn(filename, "\n")] = 0;
            }
            
            strcat(uploadfifo,childFifo);
            strcat(uploadfifo,"u\0");
            mkfifo(uploadfifo,0666);
            int uploadfd = open(uploadfifo,O_WRONLY);
            int file = open(filename, O_RDONLY);
            if ( 0 > file) {
                printf("File not found:%s\n",filename);
                
            }
            else{
                lock.l_type = F_WRLCK; /* Yazma kilidi */
                lock.l_whence = SEEK_SET; /* Başlangıçtan itibaren */
                lock.l_start = 0; /* Başlangıç offset */
                lock.l_len = 0; 
                if (fcntl(file, F_SETLK, &lock) == -1) {
                    perror("fcntl");
                    
                }
                while ((bytesRead = read(file, buf, 100)) > 0) {
                    printf("print:%s\n",buf);
                    printf("byte:%d\n",bytesRead);
                    write(uploadfd, buf, bytesRead);
                
                }
                lock.l_type = F_UNLCK;
                fcntl(file, F_SETLK, &lock);
            }
            
            
            
            close(uploadfd);
            
            close(file);
}

void downloadFun(char* message,char * childFifo){
    char buf[1000]="";
            char filename[256] ="";
            char newLine[256] ="";
            
            char downloadfifo[100]="";
           
            
            strcat(downloadfifo,childFifo);
            strcat(downloadfifo,"d\0");
            mkfifo(downloadfifo,0666);

            int downloadfd = open(downloadfifo, O_RDONLY);

            if(downloadfd < 0){
                printf("Download file cant open\n");

            }
            else{
                if(sscanf(message, "download %s", filename) !=1){
                    printf("sscanf has error\n");
                }
                int file = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                if (0 > file) {
                    printf("Unable to open file:%s\n",filename);
                }
                else{
                    int byte;
                    printf("read bekliyor\n");
                    while((byte = read(downloadfd, buf, sizeof(buf))) > 0) {
                        printf("burada");
                        if(byte <1 ){
                            break;
                        }
                        else if(strncmp(buf,"error",5) == 0){
                            printf("Server cant open file\n");
                            break;
                        }
                        printf("byte:%d\n",byte);
                        printf("Uploadin file..:\n%s",buf);
                        write(file, buf,byte);
                        
                        
                }

                }
                close(downloadfd);
                close(file);
            }
            //read(childFd, message, sizeof(message));
            
            
            
            printf("close file\n");
}

void quitFun(char * childFifo,int * childFd){
    printf("Sending write request to server log file\n");
    printf("waiting for logfile ...\n");
    printf("logfile write request granted...\n");
    printf("bye..\n");
    unlink(childFifo);

    //read(childFd, str, sizeof(str));
    printf("cikti\n");
    close(*childFd);
    exit(0);
}