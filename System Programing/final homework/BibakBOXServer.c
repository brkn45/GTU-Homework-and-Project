#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define BUF_SIZE 1024
#define MAX_CLNT 256

char clientDir[256];
char permantDir[256];
char startDir[256];
void *handle_client(void *arg);
int fileCheck(char* filePath);
void  server_scan(int clnt_sock);
void listFilesAndDirectories(const char* path,int sock);
char* extract_filename(char* path);
void  fileScan(int clnt_sock );


void signal_handler(int signal_number) {
    if (signal_number == SIGINT) {
        printf("Take CTRL+C Signal \n");
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;
    char buffer[BUF_SIZE] = {0};
    pthread_t *thread_pool;
    
    
    if (argc != 4) {
        printf("Usage: %s <dirName>  <thread pool size> <port>\n", argv[0]);
        exit(1);
    }
    signal(SIGINT, signal_handler);
    int thread_pool_size = atoi(argv[2]);
    thread_pool = malloc(sizeof(pthread_t) * thread_pool_size);

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        perror("socket() error");
        exit(1);
    }

    if (chdir(argv[1]) != 0) {
        perror("chdir");
        return 1;
    }
    if (chdir("..") == -1) {
                
             perror("chdir error");
                
    }
    strcpy(permantDir,argv[1]);
    strcpy(startDir,argv[1]);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[3]));

    if (bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1) {
        perror("bind() error");
        exit(1);
    }

    if (listen(serv_sock, 5) == -1) {
        perror("listen() error");
        exit(1);
    }

    clnt_adr_sz = sizeof(clnt_adr);

    // Client connections are handled in an infinite loop.
    int client_count = 0;
    while (1) {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if (clnt_sock == -1) {
            perror("accept() error");
            break;
        }

        // Connection is successful.
        printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));
        

        
        // Assign a thread to handle this client.
        pthread_create(&thread_pool[client_count % thread_pool_size], NULL, handle_client, &clnt_sock);
        
        
        client_count++;
        

        
    }

    // Wait for all threads to finish.
    for (int i = 0; i < thread_pool_size; i++) {
        pthread_join(thread_pool[i], NULL);
    }

    free(thread_pool);
    close(serv_sock);

    return 0;
}



void *handle_client(void *arg) {
    int clnt_sock=*((int*)arg);
    char tmpMsg[250];
    char nullmsg[250];
    while(1){
        printf("\n\n-----------------Client to Server Controll-----------\n\n");
        memset(clientDir, 0, sizeof(nullmsg));
        read(clnt_sock,nullmsg,sizeof(nullmsg));
        printf("-------------------------------\n");
        write(clnt_sock,"geldi\0",6);
        //printf("1)Client Request(nullmsg):%s\n",nullmsg);
        //printf("1)Server Response: geldi\n");
        if(strncmp(clientDir,"bitti",5) ==0){
            strcpy(clientDir,extract_filename(startDir));
        }
        else{
            strcpy(clientDir,extract_filename(startDir));
            strcpy(permantDir,extract_filename(startDir));
        }
        
        //printf("Clie per:%s\n",clientDir);
        fileScan(clnt_sock);
        printf("\n\n-----------------Server to Client Control-----------\n\n");
        /*memset(clientDir, 0, sizeof(clientDir));
        read(clnt_sock, clientDir, sizeof(clientDir));

        write(clnt_sock,"geldi\0",6);
        printf("-------------------------------\n");
        printf("7)Client Request:%s\n",clientDir);
        printf("7)Server Response:geldi\n");*/
        server_scan(clnt_sock);
        write(clnt_sock,"return\0",7);
        read(clnt_sock,tmpMsg,sizeof(tmpMsg));
        //printf("Server Request:return\n");
        //printf("Client Response:%s\n",tmpMsg);
        
        sleep(5);
    }
    
}

void  fileScan(int clnt_sock ){
    int num =1;
    char msg[BUF_SIZE];
    char fileName[100];
    char buffer[BUF_SIZE];
    ssize_t bytesRead;

    //printf("childDir:%s\n",clientDir);
    
    if (chdir(clientDir) != 0) {
        perror("chdir");
        pthread_exit(0);
    }
    while(num>0)
    {
        memset(msg, 0, sizeof(msg));
        num=read(clnt_sock, msg, sizeof(msg));
        printf("-------------------------------\n");
        printf("Client Request: %s\n", msg);
        if(strncmp(msg,"return\0",6)==0){
            write(clnt_sock,"bitti\0",6);
            printf("Server response: bitti\n");
            
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
        
       
        write(clnt_sock,"geldi\0",6);
        printf("Server response: geldi\n");

        if(strncmp(msg,"dir\0",3) ==0){
            memset(msg, 0, sizeof(msg));
            num=read(clnt_sock, msg, sizeof(msg));
            printf("-------------------------------\n");
            printf("Client Request:%s\n",msg);
            if(fileCheck(msg) == 1){
                write(clnt_sock,"var\0",4);
                printf("Server Response: var\n");
                memset(clientDir, 0, sizeof(clientDir));
                char tmpPath[250];
                strcpy(tmpPath,clientDir);
                strcpy(clientDir,msg);
                //printf("1)cl Dir:%s\n",clientDir);
                fileScan(clnt_sock);
                memset(clientDir, 0, sizeof(clientDir));
                strcpy(clientDir,tmpPath);
            }
            else{
                write(clnt_sock,"yok\0",4);
                printf("Server Response: yok\n");
                if (mkdir(msg, S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
                    perror("mkdir error");
                    pthread_exit(0);
                }
                memset(clientDir, 0, sizeof(clientDir));
                char tmpPath[250];
                strcpy(tmpPath,clientDir);
                strcpy(clientDir,msg);
                //printf("cl Dir:%s\n",clientDir);
                fileScan(clnt_sock);
                memset(clientDir, 0, sizeof(clientDir));
                strcpy(clientDir,tmpPath);
            }    
        }
        else{
            if(fileCheck(msg) == 1){
                write(clnt_sock,"var\0",4);
                /*char cwd[256];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                        printf("Geçerli dizin: %s\n", cwd);
                    }*/
                printf("Server Request: var\n");
            }
            else{
                write(clnt_sock,"yok\0",4);
                printf("Server Request: yok\n");
                int fd = open(msg,  O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
                if (fd < 0) {
                    //printf("dosya acma hatasi\n");
                    //perror("open");
                    
                }
                
                while((bytesRead = read(clnt_sock,buffer,BUF_SIZE)) > 0){
                    
                    if(strncmp(buffer,"bitti\0",5)==0){
                        write(clnt_sock,"geldi\0",6);
                        printf("Server Response: geldi\n");
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
        
        
        //printf("num:%d\n",num);

    }
    printf("-------------------------------\n");
    printf("******Client to Server Control Done******\n");
    return;
}

int fileCheck(char* filePath) {
    struct stat fileInfo;
    
    if (access(filePath, F_OK) != -1) {
        //printf("%s: File exists.\n", filePath);
        return 1;
    } else {
        //printf("%s: File does not exist.\n", filePath);
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

void  server_scan(int clnt_sock){
    
    char msg[250];
    /*read(clnt_sock, msg, sizeof(msg));
   
    write(clnt_sock,"geldi\0",6);
    printf("-------------------------------\n");
    printf("4)Client Request:%s\n",msg);
    printf("4)Server Response:geldi\n");*/

    listFilesAndDirectories(permantDir,clnt_sock);
    /*write(clnt_sock,"return\0",7);
    memset(msg, 0, sizeof(msg));
    read(clnt_sock, msg, sizeof(msg));
    write(clnt_sock,"geldi\0",5);
    printf("-------------------------------\n");
    printf("5)Client Request:%s\n",msg);
    printf("5)Server Response:geldi\n");*/
    
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
    
    printf("Path:%s\n",path);
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
            
            char * tmpStr = extract_filename(newPath);
            //Dir information for server
            write(sock,"dir\0",4);
            memset(message, 0, sizeof(message));
            read(sock,message,sizeof(message));
            
            printf("-------------------------------\n");
            //printf("2)Client Request: dir\n");
            //printf("2)Server response:%s\n",message);

            write(sock,tmpStr,sizeof(tmpStr));
            memset(message, 0, sizeof(message));
            read(sock,message,sizeof(message));
           
            printf("-------------------------------\n");
            printf("Client Request: %s\n",extract_filename(newPath));
            printf("Server response:%s\n",message);
            
            
            //printf("Directory: %s\n", newPath);
            //printf("2)Server Message:%s\n",message);
            
            
            listFilesAndDirectories(newPath,sock);
            write(sock,"return\0",7);
            memset(message, 0, sizeof(message));
            read(sock,message,sizeof(message));
            printf("7)Client Request: return\n");
            printf("7)Server response:%s\n",message);
        } else {
            char * tmpStr = extract_filename(newPath);
            write(sock,tmpStr,strlen(tmpStr));
            memset(message, 0, sizeof(message));
            read(sock,message,sizeof(message));

            printf("-------------------------------\n");
            printf("4)Client Request: %s\n",extract_filename(newPath)); 
            printf("4)Server response:%s\n",message);

            if(strncmp(message,"geldi\0",5)==0){
                memset(message, 0, sizeof(message));
                read(sock,message,sizeof(message));
            }
            //printf("3)Server Message:%s\n",message);
            //printf("File: %s\n", tmpStr);
            
            if(strncmp(message,"yok\n",3)==0){
               
                
                char tmpPath[250];
                /*strcpy(tmpPath,newPath);
                strcpy(tmpPath,"\\");
                strcpy(tmpPath,tmpStr);*/
                fd = open(newPath, O_RDONLY);
                if (fd < 0) {
                    perror("open");
                    
                }
                
                while ((bytesRead = read(fd, buffer, BUF_SIZE-1)) > 0) {
                    
                    //printf("push message:%s\n",buffer);
                    write(sock,buffer,BUF_SIZE);
                    memset(message, 0, sizeof(message));
                    read(sock,message,sizeof(message));
                    //printf("File Status:%s\n",message);
                    memset(buffer, 0, BUF_SIZE);
                }
                write(sock,"bitti\0",6);
                printf("-------------------------------\n");
                printf("5)Client Request: bitti\n");
                printf("5)Server Response: %s\n",message);
                close(fd);
            }
            //sleep(5);
            
        }
    }
    printf("-------------------------------\n");
    printf("******Server to Client Control Done******\n");
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