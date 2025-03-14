#include <stdio.h>
#include <stdlib.h>

void menu(); // all sellection oparation here
void read_news(char buffer[500], char file_path[12], int is_Only_Title); // for read news and write teminale
void append_file(char* file_path, char c); // this functio readed file wirte readed_news_id.txt file
double f_func(int x);	// for 3 part
double g_func(double f(int x), int a); // for3 part
int is_there(int num,char file_path[20]); // news file is readed or not readed
void readed(char file_path[20]); // write readed news on teminale
void read_magic_numbers(char buffer_magic[12], char buffer_news[500]); // for readed news to  find magic number



int main(){ 
	menu();


}

void menu(){
	int num=0,num_readed ,flag=0,choice=20;
	char ch;
	char buffer[500];
	char file_path_1[12]="news/1.txt"; // this file news name
	char file_path_2[12]="news/2.txt";
	char file_path_3[12]="news/3.txt";
	char file_path_4[12]="news/4.txt";
	char file_path_readed[20]="readed_news_id.txt";
	FILE *fp_readed;
	fp_readed=fopen("readed_news_id.txt","a+");
	while(1){
		flag=0;
		fseek(fp_readed,0,SEEK_SET);
		printf("\n\n**********Daily Press*********\n\n\nToday's news are listed for you:\n\n\n");
		printf("Title of 1. news:YENİ TİP KORONAVİRÜS SALGININDA SON 24 SAAT \n");
		printf("Title of 2. news:Fatih Terim'in kızı Merve Terim patladı! ""İnanılmaz sinirliyim...""\n");
		printf("Title of 3. news:Kapıköy Gümrük Kapısı'ndaki yolcu giriş ve çıkışları geçici süreyle durduruldu\n");
		printf("Title of 4. news:Son dakika… Bakan Selçuk: 7 milyar liraya yakın asgari ücret desteği vereceğiz\n");
		printf("What do you want to\n");
		printf("a.Read a new\nb.List the readed news\nc.Get decrypted İnformation from the news\n");
		scanf(" %c",&ch);
		
		if(ch=='a'){ // if choose readed news
			printf("Which news do you want to read:\n");
			scanf("%d",&num);
			flag=is_there(num,file_path_readed);
			if(flag==1){ // flag equation is 1 news already readed  or flag 0 didnt read
				printf("This news readed.Do you want to read again Yes(1)/ No(0)\n");
				scanf("%d",&choice);
				if(choice==1){
					if(num==1){
					read_news(buffer,file_path_1,1);
					}
					else if(num==2){
						read_news(buffer,file_path_2,2);
					}
					else if(num==3){
						read_news(buffer,file_path_3,3);
					}
					else if(num==4){
						read_news(buffer,file_path_4,4);
					}
				}
				else if(choice==0){ 
					printf("Do you wnat to continue. Yes(y)/No(n)\n");
					scanf(" %c",&ch);
					if(ch=='n'){
						exit(1);
					}
				}
			}
			else {
				if(num==1){
					read_news(buffer,file_path_1,1);
					append_file(file_path_readed,'1'); // this function write readed_news_id.txt file
				}
				else if(num==2){
					read_news(buffer,file_path_2,2);
					append_file(file_path_readed,'2');
				}
				else if(num==3){
					read_news(buffer,file_path_3,3);
					append_file(file_path_readed,'3');
				}
				else if(num==4){
					read_news(buffer,file_path_4,4);
					append_file(file_path_readed,'4');	
				}
			}
		}	
		else if(ch=='b'){
			readed(file_path_readed); // write terminale readed news file
			printf("Do you wnat to continue. Yes(y)/No(n)\n");
			scanf(" %c",&ch);
			if(ch=='n'){
				exit(1);
			}
		}
		else if(ch=='c'){  // find magic number
			printf("Which news would you like to decrypt:");
			scanf("%d",&choice);
			if(choice==1){
				read_magic_numbers(file_path_1,buffer);
			}
			else if(choice==2){
				read_magic_numbers(file_path_2,buffer);
			}
			else if(choice==3){
				read_magic_numbers(file_path_3,buffer);
			}
			else if(choice==4){
				read_magic_numbers(file_path_4,buffer);
			}
		}
	
	}
}	

void read_news(char buffer[500], char file_path[12], int is_Only_Title){ // readed news and write terminale
	FILE *fp;
	
	int i=0,num=0,flag=0;
	fp=fopen(file_path,"r");
	
	
	
	while(!feof(fp)){
		fscanf(fp,"%c",&buffer[i]);
		i++;
	}
	printf("%s",buffer );

	
		
	

	
	
	fclose(fp);
	
}
void append_file(char* file_path, char c){ // this function write readed_news_id.txt file
	FILE *fp_readed;
	char f_c;
	int flag=0;
	fp_readed=fopen(file_path,"a+");
	while(!feof(fp_readed)){
		fscanf(fp_readed,"%c",&f_c);
		if(c==f_c)
			flag=1;
	}
	if(flag==0){
		fprintf(fp_readed, "%c \n",c );
	}
	fclose(fp_readed);
}

int is_there(int num,char file_path_readed[20]){ // file  readed or didnt readed
	FILE * fp;
	fp=fopen(file_path_readed,"r+");
	int file_num=0;
	while(!feof(fp)){
		fscanf(fp,"%d",&file_num);
		if(file_num==num)
			return 1;
	}
	return 0;

}
void readed(char file_path[20]){ // write reade file on terminale
	int num;
	FILE *fp;
	fp=fopen(file_path,"r+");
	while(!feof(fp)){

		fscanf(fp,"%d ",&num);
		printf("%d. new is readed \n", num);
	}
}
void read_magic_numbers(char buffer_magic[12], char buffer_news[500]){ // readed magic number
	FILE *fp;
	char c;
	int i=0;
	double result=0;
	fp=fopen(buffer_magic,"r");
	
	while(!feof(fp)){
		fscanf(fp,"%c",&buffer_news[i]);
		
		if(buffer_news[i]=='#'){ // if find '#' in paragrapf after character number and calculation magic number
			i++;
			fscanf(fp,"%c",&buffer_news[i]);
			result=result +g_func(f_func,atoi(&buffer_news[i]));

		}
		i++;
	}
	printf("%s \n\n",buffer_news );
	if(buffer_magic[0]=='1'){
		printf("number of tests performed:%.2lf\n",result );
	}
	else if(buffer_magic[0]=='2'){
		printf("number of sick people:%.2lf\n",result );
	}
	else if(buffer_magic[0]){
		printf("number of deaths:%.2lf\n",result);
	}
	else if(buffer_magic[0]){
		printf("number of sick people:%.2lf\n",result );
	}
}
double f_func(int x){ // for magic number
	int result=0;
	
	result=x*x*x -x*x +2;
	return (double)result;
}
double g_func(double f(int x),int a){ // for magic number
	double result=0;
	result=f(a)*f(a);
	return result;
}