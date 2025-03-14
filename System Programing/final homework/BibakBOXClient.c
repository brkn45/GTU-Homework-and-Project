#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

#define IP_ADDR "127.0.0.1"

char clientDir[256] = ".";
void error_handling(char *message);
char* extract_filename(char* path);
void listFilesAndDirectories(const char* path,int sock);
void handle_client(int arg);
int fileCheck(char* filePath);
void *scan_server(void *arg);
void loopFun(char **argv,int sock);

void signal_handler(int signal_number) {
    if (signal_number == SIGINT) {
        printf("Take CTRL+C Signal \n");
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    if(argc != 3) {
        printf("Usage : %s <dirName> <port>\n", argv[0]);
        exit(1);
    }
    pthread_t thread;
    pthread_create(&thread, NULL, scan_server, argv);
    signal(SIGINT, signal_handler);
    pthread_join(thread, NULL);
    return 0;
}


void *scan_server(void *arg){
    char** argv = (char**)arg;
    int sock;
    struct sockaddr_in serv_addr;
    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(IP_ADDR);
    serv_addr.sin_port=htons(atoi(argv[2]));
  
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) 
        error_handling("connect() error!");
    else
        printf("Connected...........\n");
    char cwd[256];
    if (chdir(argv[1]) != 0) {
        perror("chdir");
        
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Working Directory: %s\n", cwd);
        }
    char tmpStr[256];
    while(1){

        if(chdir(cwd) == -1) {
            perror("chdir error");
        
        }
        strcpy(clientDir,cwd);
        loopFun(argv,sock);
        
        
        
        
        
       
        sleep(5);
    }
    
}

void loopFun(char **argv,int sock){

    
    char opmsg[BUF_SIZE];
    int result, opnd_cnt, i;
    char filename[256] = "example.txt";
    char message[256];
    FILE *fp = fopen(filename, "rb");
    char buf[BUF_SIZE];
    

    write(sock, argv[1], strlen(argv[1])+1);  // send file name
    read(sock,message,sizeof(message));
    printf("-------------------------------\n");
    //printf("1)Client Request: %s\n",argv[1]);
    //printf("1)Server Response: %s\n",message);
    //while(1) {
        
        //write(sock, buf, BUF_SIZE);

    char myPath[256]; // Dizinin boyutunu ihtiyaçlarınıza göre ayarlayabilirsiniz
    if (getcwd(myPath, sizeof(myPath)) != NULL) {
        printf("\n\n-----------------Client to Server Controll-----------\n\n");
        //printf("Program Driectory: %s\n", myPath);
        listFilesAndDirectories(myPath,sock);
        
        write(sock,"return\0",7);
        memset(message, 0, sizeof(message));
        read(sock,message,sizeof(message));
        //printf("-------------------------------\n");
        //printf("6)Client Request: return\n");
        //printf("6)Server Response: %s\n",message);
        
       
        printf("\n\n-----------------Server to Client Controll-----------\n\n");
        handle_client(sock);
        //printf("Sg 3\n");
    } else {
        perror("getcwd error");
        return ;
    }    
        
    //}
    //fclose(fp);

    //close(sock);
}





void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void listFilesAndDirectories(const char* path,int sock) {
    DIR* directory;
    struct dirent* entry;
    struct stat fileStat;
    char message[20];
    int fd;
    char buffer[BUF_SIZE];
    ssize_t bytesRead;
    directory = opendir(path);
    if (directory == NULL) {
        printf("Unable to open directory: %s\n", path);
        return;
    }
    
    while ((entry = readdir(directory)) != NULL) {
        char newPath[256];
        snprintf(newPath, sizeof(newPath)+1, "%s/%s", path, entry->d_name);
        
        if (stat(newPath, &fileStat) == -1) {
            printf("Unable to access file/directory: %s\n", newPath);
            continue;
        }
        
        if (S_ISDIR(fileStat.st_mode)) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            
            //char * tmpStr = extract_filename(newPath);
            //Dir information for server
            write(sock,"dir\0",4);
            memset(message, 0, sizeof(message));
            read(sock,message,sizeof(message));
            //printf("-------------------------------\n");
            //printf("2)Client Request: dir\n");
            //printf("2)Server response:%s\n",message);
            write(sock,extract_filename(newPath),strlen(extract_filename(newPath)) +1);
            memset(message, 0, sizeof(message));
            read(sock,message,sizeof(message));
            printf("-------------------------------\n");
            printf("Client Request: %s\n",extract_filename(newPath));
            printf("Server response:%s\n",message);
           
            
            
            
            
            
            listFilesAndDirectories(newPath,sock);
            write(sock,"return\0",7);
            memset(message, 0, sizeof(message));
            read(sock,message,sizeof(message));
            //printf("-------------------------------\n");
            //printf("7)Client Request: return\n");
            //printf("7)Server response:%s\n",message);
        } else {
            //char * tmpStr = ;
            write(sock,extract_filename(newPath),strlen(extract_filename(newPath))+1);

            memset(message, 0, sizeof(message));
            read(sock,message,sizeof(message));
            printf("-------------------------------\n");
            printf("Client Request: %s\n",extract_filename(newPath)); 
            printf("Server response:%s\n",message);
            if(strncmp(message,"geldi\0",5)==0){
                memset(message, 0, sizeof(message));
                read(sock,message,sizeof(message));
                printf("Server Request:%s\n",message); // var veya yok gelmesi gerekiyor
            }
            //printf("3)Server Message:%s\n",message);
            //printf("File: %s\n", tmpStr);
            
            if(strncmp(message,"yok\n",3)==0){
               
                
                char tmpPath[250];
                /*strcpy(tmpPath,newPath);
                strcpy(tmpPath,"\\");
                strcpy(tmpPath,tmpStr);*/
                close(fd);
                fd = open(newPath, O_RDONLY);
                if (fd < 0) {
                    perror("open");
                    
                }
                
                while ((bytesRead = read(fd, buffer, BUF_SIZE)) > 0) {
                    
                    //printf("push message:%s\n",buffer);
                    write(sock,buffer,BUF_SIZE);
                    memset(message, 0, sizeof(message));
                    read(sock,message,sizeof(message));
                    //printf("File Status:%s\n",message);
                    memset(buffer, 0, BUF_SIZE);
                   
                }
                
                write(sock,"bitti\0",6);
                read(sock,message,sizeof(message));
                printf("-------------------------------\n");
                printf("Client Request: bitti\n");
                printf("Server Response: %s\n",message);
                printf("File Succesfuly Tranfer to Server");
                close(fd);
            }
            //sleep(5);
            
        }
    }
    printf("-------------------------------\n");
    printf("******Client to Server Control Done******\n");
    closedir(directory);
}


char* extract_filename(char* path) {
    char* filename = strrchr(path, '/');
    if (filename == NULL) {
        return path; // '/' karakteri yoksa, tam dizgi dosya adıdır
    } else {
        return filename + 1; // '/' karakterinden sonraki karakterler dosya adıdır
    }
}


void handle_client(int arg) {
    int clnt_sock=arg;
    int num =1;
    char msg[BUF_SIZE];
    char fileName[100];
    char buffer[BUF_SIZE];
    ssize_t bytesRead;

    printf("childDir:%s\n",clientDir);
    if (chdir(clientDir) != 0) {
        perror("chdir");
        return;
    }
    while(num>0)
    {
        memset(msg, 0, sizeof(msg));
        
        num=read(clnt_sock, msg, sizeof(msg));
        printf("-------------------------------\n");
        printf("2)Client Request: %s\n", msg);
        if(strncmp(msg,"return\0",6)==0){
            write(clnt_sock,"bitti\0",6);
            printf("2)Server response: bitti\n");
            
            if (chdir("..") == -1) {
                perror("chdir error");
                
            }
            
            break;
        }
        else if(strncmp(msg,"",1)==0){
            if (chdir("..") == -1) {
                perror("chdir error");
                
            }
            break;
        }
        
        //printf("client msg1:%s\n",msg);
        write(clnt_sock,"geldi\0",6);
        printf("2)Server response: geldi\n");

        if(strncmp(msg,"dir\0",3) ==0){
            memset(msg, 0, sizeof(msg));
            num=read(clnt_sock, msg, sizeof(msg));
            printf("-------------------------------\n");
            printf("3)Client Request:%s\n",msg);
            if(fileCheck(msg) == 1){
                write(clnt_sock,"var\0",4);
                printf("3)Server Response: var\n");
                memset(clientDir, 0, sizeof(clientDir));
                char tmpPath[250];
                strcpy(tmpPath,clientDir);
                strcpy(clientDir,msg);
                //printf("1)cl Dir:%s\n",clientDir);
                handle_client(clnt_sock);
                memset(clientDir, 0, sizeof(clientDir));
                strcpy(clientDir,tmpPath);
            }
            else{
                write(clnt_sock,"yok\0",4);
                printf("3)Server Response: yok\n");
                if (mkdir(msg, S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
                    perror("mkdir error");
                    return;
                }
                memset(clientDir, 0, sizeof(clientDir));
                char tmpPath[250];
                strcpy(tmpPath,clientDir);
                strcpy(clientDir,msg);
                //printf("cl Dir:%s\n",clientDir);
                handle_client(clnt_sock);
                memset(clientDir, 0, sizeof(clientDir));
                strcpy(clientDir,tmpPath);
            }    
        }
        else{
            if(fileCheck(msg) == 1){
                write(clnt_sock,"var\0",4);
                printf("2)Server Request: var\n");
            }
            else{
                write(clnt_sock,"yok\0",4);
                printf("2)Server Request: yok\n");
            
                int fd = open(msg,  O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
                if (fd < 0) {
                    //printf("dosya acma hatasi\n");
                    perror("open");
                    
                }
                
                while((bytesRead = read(clnt_sock,buffer,BUF_SIZE)) > 0){
                    
                    if(strncmp(buffer,"bitti\0",5)==0){
                        write(clnt_sock,"geldi\0",6);
                        printf("2)Server Response: geldi\n");
                        break;
                    }

                    write(fd,buffer,strlen(buffer));
                    write(clnt_sock,"geldi\0",6);
                    memset(buffer, 0, BUF_SIZE);
                }
                close(fd);
            }
        
        }
        
       /*if(num <1){
        printf("en alttan cıktı\n");
            break;
        }*/
        
        
        

    }
    printf("-------------------------------\n");
    printf("******Server to Client Control Done******\n");
    return;
}

int fileCheck(char* filePath) {
    struct stat fileInfo;
    
    if (access(filePath, F_OK) != -1) {
        printf("%s: File exists.\n", filePath);
        return 1;
    } else {
        printf("%s: File does not exist.\n", filePath);
        return 0;
    }
    
    if (stat(filePath, &fileInfo) == -1 || !S_ISDIR(fileInfo.st_mode)) {
        return 0;
    }
    
    DIR* directory;
    struct dirent* file;
    
    directory = opendir(filePath);
    if (directory == NULL) {
        return 0;
    }
    
    while ((file = readdir(directory)) != NULL) {
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
            continue;
        }
        
        char newPath[256];
        snprintf(newPath, sizeof(newPath)+1, "%s/%s", filePath, file->d_name);
        fileCheck(newPath);
    }
    
    closedir(directory);
}
