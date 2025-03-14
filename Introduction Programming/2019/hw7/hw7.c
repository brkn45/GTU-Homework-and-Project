#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum player_type {none=-1,cap ,car };
enum block_type {start=0,property,fortune, tax, punish };

struct player
{
	enum player_type type;
	int current_block_id;
	int owned_block_ids[11];
	int account;
	int turn_to_wait;
	char * name;


	
};

struct block
{
	int id;
	char * name;
	int price;
	int rent;
	int rent_1;
	int rent_2;
	int rent_3;
	int house_price;
	int h_count;
	struct player owner;
	enum block_type type;
};
void init_the_board(struct block board[20]);
void show_board(struct block board[20],struct player player_one, struct player player_two);
void show_properties(struct block board[20]);
void buy_property(struct block* current_block, struct player* current_player);
void sell_property(struct block board[20], struct player* current_player);
void gameplay (struct block board[20], struct player player_one, struct player player_two);
int roll_dice();
void show_my_account(struct block board[20], int queue,struct player player_one, struct player player_two);
void my_proporty(struct block board[20],int queue);
void buy_house(struct block * current_block,struct player *current_player);
void rent(struct block *board,struct player player_one,struct player player_two);
int main(){
	struct block board[20];
	struct player player_one;
	struct player player_two;
	init_the_board(board);
    srand(time(NULL)); 
    player_one.name="Cap";
    player_two.name="Car";
    player_one.type=cap;
    player_two.type=car;
    player_one.current_block_id=0;
    player_two.current_block_id=0;
    player_one.account=100000;
    player_two.account=100000;
    player_one.turn_to_wait=0;
    player_two.turn_to_wait=0;

    //show_board(board,player_one,player_two);
    gameplay(board,player_one,player_two);


}

void init_the_board(struct block board[20]){
	struct block temp;
	struct player temp_player;
	temp_player.type=none;

    temp.id=0;
    temp.name="Start";
    temp.price=0;
    temp.rent=0;
    temp.rent_1=0;
    temp.rent_2=0;
    temp.rent_3=0;
    temp.owner=temp_player;
    temp.house_price=0;
    temp.h_count=0;
    temp.type=start;
    board[temp.id]=temp;
    temp.type=tax;
    temp.name="Car park";
    temp.id=2;
    temp.price=1500;
    board[temp.id]=temp;
    temp.name="Car fix";
    temp.id=8;
    temp.price=1750;
    board[temp.id]=temp;
    temp.name="Bills";
    temp.id=10;
    temp.price=2000;
    board[temp.id]=temp;
    temp.name="Oil";
    temp.id=12;
    temp.price=2250;
    board[temp.id]=temp;
	temp.name="Vocation";
    temp.id=18;
    temp.price=5000;
    board[temp.id]=temp;

	temp.type=punish;
	temp.name="Wait 2 turn";
	temp.price=2;
    temp.id=5;
    board[temp.id]=temp;
	temp.name="Wait 1 turn";
	temp.price=1;
    temp.id=15;
    board[temp.id]=temp;


    temp.type=property;

    temp.id=1;
    temp.name="Esenyurt";
    temp.price=16000;
    temp.rent=800;
    temp.rent_1=4000;
    temp.rent_2=9000;
    temp.rent_3=25000;
    temp.house_price=10000;
    temp.h_count=0;
    board[temp.id]=temp;

    temp.id=3;
    temp.name="Tuzla";
    temp.price=16500;
    temp.rent=850;
    temp.rent_1=4250;
    temp.rent_2=9500;
    temp.rent_3=26000;
    temp.house_price=12000;
    temp.h_count=0;
    board[temp.id]=temp;

    temp.id=4;
    temp.name="Arnavutkoy";
    temp.price=17000;
    temp.rent=850;
    temp.rent_1=4500;
    temp.rent_2=10000;
    temp.rent_3=28000;
    temp.house_price=12000;
    temp.h_count=0;
    board[temp.id]=temp;

    temp.id=6;
    temp.name="Catalca";
    temp.price=20000;
    temp.rent=1000;
    temp.rent_1=5000;
    temp.rent_2=12000;
    temp.rent_3=30000;
    temp.house_price=13000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=7;
    temp.name="Beykoz";
    temp.price=23000;
    temp.rent=1100;
    temp.rent_1=5500;
    temp.rent_2=12500;
    temp.rent_3=33000;
    temp.house_price=13000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=9;
    temp.name="Maltepe";
    temp.price=30000;
    temp.rent=1350;
    temp.rent_1=7000;
    temp.rent_2=15000;
    temp.rent_3=40000;
    temp.house_price=15000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=11;
    temp.name="Sisli";
    temp.price=33000;
    temp.rent=1500;
    temp.rent_1=8000;
    temp.rent_2=16000;
    temp.rent_3=42000;
    temp.house_price=16000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=13;
    temp.name="Atasehir";
    temp.price=35000;
    temp.rent=1600;
    temp.rent_1=8500;
    temp.rent_2=17000;
    temp.rent_3=45000;
    temp.house_price=17000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=14;
    temp.name="Sariyer";
    temp.price=40000;
    temp.rent=1750;
    temp.rent_1=9500;
    temp.rent_2=19000;
    temp.rent_3=48000;
    temp.house_price=19000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=16;
    temp.name="Kadikoy";
    temp.price=43000;
    temp.rent=1900;
    temp.rent_1=11000;
    temp.rent_2=21500;
    temp.rent_3=55000;
    temp.house_price=23000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=17;
    temp.name="Besiktas";
    temp.price=60000;
    temp.rent=2500;
    temp.rent_1=15000;
    temp.rent_2=28000;
    temp.rent_3=60000;
    temp.house_price=30000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=19;
    temp.name="Bebek";
    temp.price=70000;
    temp.rent=3500;
    temp.rent_1=20000;
    temp.rent_2=35500;
    temp.rent_3=65000;
    temp.house_price=35000;
    temp.h_count=0;
    board[temp.id]=temp;

}
void show_board(struct block board[20],struct player player_one, struct player player_two){
    int i,j, size[6];
    printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for(i=0;i<6;i++){
       if(strlen(board[i].name)<8){
            printf("|\t%s\t\t",board[i].name);
       }
       else{
            printf("|\t%s\t",board[i].name );

       }


    }
    printf("|\n");
    for(i=0;i<6;i++){
        if(strlen(board[i].name)<8){
            if(board[i].type==property || board[i].type==tax){
                printf("|\t%d$\t\t",board[i].price );
            }
            else{
                printf("|\t\t\t");
            }

        }
        else{
            if(board[i].type==property || board[i].type==tax){
                printf("|\t%d$\t\t",board[i].price );
            }
            else{
                printf("|\t\t\t");
            }
        }
    }
    printf("|\n");
    for(i=0;i<6;i++){

        if(player_one.current_block_id==i && player_two.current_block_id==i ){
            printf("|\t%s %s\t\t",player_one.name , player_two.name);


        }
        
        else if(player_two.current_block_id==i){
            printf("|\t%s\t\t",player_two.name );


        }
        else if(player_one.current_block_id==i){
            printf("|\t%s\t\t",player_one.name );
        }
        else{
            printf("|\t\t\t");
        }
    }
    printf("|\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for(i=0;i<4;i++){
       if(strlen(board[19-i].name)<8){
            printf("|\t%s\t\t",board[19-i].name);

       }
       else{
            printf("|\t%s\t",board[19-i].name );

       }
       printf("|");
       for(j=0;j<4;j++){
            printf("\t\t\t" );
       }
       
       if(strlen(board[6+i].name)<8){
            printf("|\t%s\t\t",board[6+i].name);
       }
       else{
            printf("|\t%s\t",board[6+i].name );

       }
       printf("|\n");
       
        if(strlen(board[19-i].name)<8){
            if(board[19-i].type==property || board[19-i].type==tax){
                printf("|\t%d$\t\t",board[19-i].price );
            }
            else{
                printf("|\t\t\t");
            }

        }
        else{
            if(board[19-i].type==property || board[19-i].type==tax){
                printf("|\t%d$\t\t",board[19-i].price );
            }
            else{
                printf("|\t\t\t");
            }
        }
        printf("|");
        for(j=0;j<4;j++){
            printf("\t\t\t" );
       }
       if(strlen(board[6+i].name)<8){
            if(board[6+i].type==property || board[6+i].type==tax){
                printf("|\t%d$\t\t",board[6+i].price );
            }
            else{
                printf("|\t\t\t");
            }

        }
        else{
            if(board[6+i].type==property || board[6+i].type==tax){
                printf("|\t%d$\t\t",board[6+i].price );
            }
            else{
                printf("|\t\t\t");
            }
        }
        printf("|\n");
        
       
            if(player_one.current_block_id==19-i  && player_two.current_block_id==19-i  ){
                printf("|\t%s %s\t\t",player_one.name , player_two.name);


            }
            
            else if(player_two.current_block_id==19-i){
                printf("|\t%s\t\t",player_two.name );


            }
            else if(player_one.current_block_id==19-i){
                printf("|\t%s\t\t",player_one.name );
            }
            else{
                printf("|\t\t\t");
            }
            printf("|");
            for(j=0;j<4;j++){
                printf("\t\t\t" );
            }

            if(player_one.current_block_id==6+i  && player_two.current_block_id==6+i  ){
                printf("|\t%s %s\t\t",player_one.name , player_two.name);


            }
            
            else if(player_two.current_block_id==6+i){
                printf("|\t%s\t\t",player_two.name );


            }
            else if(player_one.current_block_id==6+i){
                printf("|\t%s\t\t",player_one.name );
            }
            else{
                printf("|\t\t\t");
            }
            
        printf("|\n");
        if(i<3)
            printf("------------------------\t\t\t\t\t\t\t\t\t\t\t\t---------------------------\n");
        else
            printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");

          
    }

    for(i=0;i<6;i++){
       if(strlen(board[15-i].name)<8){
            printf("|\t%s\t\t",board[15-i].name);
       }
       else{
            printf("|\t%s\t",board[15-i].name );

       }


    }
    printf("|\n");
    for(i=0;i<6;i++){
        if(strlen(board[15-i].name)<8){
            if(board[i].type==property || board[15-i].type==tax){
                printf("|\t%d$\t\t",board[15-i].price );
            }
            else{
                printf("|\t\t\t");
            }

        }
        else{
            if(board[i].type==property || board[i].type==tax){
                printf("|\t%d$\t\t",board[15-i].price );
            }
            else{
                printf("|\t\t\t");
            }
        }
    }
    printf("|\n");
    for(i=0;i<6;i++){

        if(player_one.current_block_id==15-i && player_two.current_block_id==15-i ){
            printf("|\t%s %s\t\t",player_one.name , player_two.name);


        }
        
        else if(player_two.current_block_id==15-i){
            printf("|\t%s\t\t",player_two.name );


        }
        else if(player_one.current_block_id==15-i){
            printf("|\t%s\t\t",player_one.name );
        }
        else{
            printf("|\t\t\t");
        }
    }
    printf("|\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");
   





}
void show_properties(struct block board[20]){
    int i,num;

    for(i=0;i<19;i++){
        if(board[i].type==property ){
            printf("%d-\t%s\n",board[i].id,board[i].name );
        }
    }
    printf("0-\t exit\n"); 
    scanf("%d",&num);
    for (i = 0; i < 20; ++i){
        if(num==board[i].id){
            if(board[i].type==property ){
                printf("---------------------------------\n");
                printf("|\t%s\t\t|\n",board[i].name);
                printf("---------------------------------\n");
                printf("|\tRent\t%d\t\t|\n",board[i].rent);
                printf("|\tRent\t%d\t\t|\n",board[i].rent_1);
                printf("|\tRent\t%d\t\t|\n",board[i].rent_2);
                printf("|\tRent\t%d\t\t|\n",board[i].rent_3);
                printf("---------------------------------\n");
                printf("|\tHouse Price\t%d\t|\n",board[i].price);
                printf("---------------------------------\n");

            }
        }
    }

}
void buy_property(struct block* current_block, struct player* current_player){
    int num;
    printf("do you want to buy property\n1-Yes \n2- No");
    scanf("%d",&num);
    
    if(num==1){
        if(current_block->owner.type==none ){
            if(current_player->account>current_block->price){
                current_block->owner.name=current_player->name;
                current_block->type=current_player->type;
                current_player->account=current_player->account - current_block->price;
            }
            else{
                printf("not enough money\n");
            }
        }    

    }
    


}
int roll_dice(){
    int dice=0;
    dice=3;//rand()%10;
    return dice;
}
void gameplay (struct block board[20], struct player player_one, struct player player_two){
    int queue=0;
    int num,flag=0;
    
    while(player_one.account != 0 || player_two.account != 0){
        show_board(board,player_one,player_two);
        printf("\n\n\n");
        printf("queue player %d\n",queue%2+1);
       
        printf("1- Roll the Dice\n");
        printf("2- Show My account\n");
        printf("3- Show my  properties\n");
        printf("4- show property deeds\n");
        printf("5- Buy property\n");
        printf("6- Buy house\n");
        printf("7- sell property\n");
        printf("Please select option to continue\n");
        
        scanf("%d",&num);
        if(num==1){
            
            if(queue%2+1==1){
                if(player_one.turn_to_wait==0){
                    player_one.current_block_id=player_one.current_block_id+roll_dice();
                }
                
                
                if(player_one.current_block_id>=20){
                    player_one.current_block_id=player_one.current_block_id%20;
                    player_one.account=player_one.account+1000;
                }
            }
            else if(queue%2+1==2){
                if(player_two.turn_to_wait==0){
                    player_two.current_block_id=player_two.current_block_id+roll_dice();
                }
                

                if(player_two.current_block_id>=20){
                    player_two.current_block_id=player_two.current_block_id%20;
                    player_two.account=player_two.account+1000;

                }

            }
            queue++;
        }
        else if(num==2){
            show_my_account(board, queue,player_one,player_two);
        }
        else if(num==3){
            my_proporty(board,queue);
        }
        else if(num==4){
            show_properties(board);
        }
        else if(num==5){
            if(queue%2+1==1){
                buy_property(&board[player_one.current_block_id],&player_one);
            }
            else if(queue%2+1==2){
                buy_property(&board[player_two.current_block_id],&player_two);
            }


        }
        else if(num==6){
            if(queue%2+1==1){
                buy_house(&board[player_one.current_block_id],&player_one);
            }
            else if(queue%2+1==2){
                buy_house(&board[player_two.current_block_id],&player_two);
            }

        }
        else if(num==7){
            if(queue%2+1==1){
                sell_property(board,&player_one);
            }
            else if(queue%2+1==2){
                sell_property(board,&player_two);
            }

        }
        if(queue%2+1==1){
            if(board[player_one.current_block_id].owner.type ==car )
                rent(&board[player_one.current_block_id],player_one,player_two);

        }
        else if(queue%2+1==2){
            if(board[player_two.current_block_id].owner.type ==car )
                rent(&board[player_two.current_block_id],player_one,player_two);
        }
        if((board[player_one.current_block_id].type==punish || board[player_two.current_block_id].type==punish) && ((player_one.turn_to_wait==0) && (player_two.turn_to_wait==0))){
            if(board[player_one.current_block_id].type==punish ){
                if(board[player_one.current_block_id].id==5){
                    player_one.turn_to_wait=2;
                    
                }
                else if(board[player_one.current_block_id].id==15){
                    player_one.turn_to_wait=1;
                    
                }
            }
            else if(board[player_two.current_block_id].type==punish && player_two.turn_to_wait==0){
                if(board[player_two.current_block_id].type==punish){
                    if(board[player_two.current_block_id].id==5){
                        player_two.turn_to_wait=2;
                        
                    }
                    else if(board[player_two.current_block_id].id==15){
                        player_two.turn_to_wait=1;
                        
                }
            }

            }
        }
        else if(player_one.turn_to_wait>0){
                    printf("bura girdi7\n");
                    player_one.turn_to_wait=player_one.turn_to_wait-1;
         }
        else if(player_two.turn_to_wait>0){
                    printf("bura girdi8\n");
                    player_two.turn_to_wait=player_two.turn_to_wait-1;
         }
        
     }       
}
void show_my_account(struct block board[20],int queue,struct player player_one, struct player player_two){
    int i=0;
    if(queue%2+1==1){
        printf("your account :%d\n",player_one.account );
        

    }
    else if(queue%2+1==2){
        printf("your account :%d\n",player_two.account );

    }
    
}
void my_proporty(struct block board[20],int queue){
    int i;
    printf("queue:%d\n",queue );
    if(queue%2+1==1){
        for(i=0;i<20;i++){
            if(board[i].owner.type==cap){
                printf("%s : %d\n",board[i].name,board[i].h_count );
            }
        }
    }
    else if(queue%2+1==2){
        for(i=0;i<20;i++){
            if(board[i].owner.type==car){
                printf("%s : %d\n",board[i].name,board[i].h_count );
            }
        }
    }

}

void buy_house(struct block * current_block,struct player *current_player){
    int num;
    if(current_player->type == current_block->type){
        printf("do you want to buy property\n1-Yes \n2- No\n");
        scanf("%d",&num);
        if(current_block->h_count<3){
            if(num==1){
                if(current_player->account>current_block->price){
                    current_block->h_count=current_block->h_count+1;
                    current_player->account=current_player->account - current_block->price;
                }
                else{
                    printf("not enough money\n");
                }

            }
        }
    }    
} 
void sell_property(struct block board[20], struct player* current_player){
    int num;
    int i;
    if(current_player->type==cap)
        my_proporty(board,0);
    else if(current_player->type==car)
        my_proporty(board,1);

    printf("Select property to sell\n");
    scanf("%d",&num);
    for(i=0;i<20;i++){
        if(num==board[i].id){
            printf("do you want to sell property\n1- Yes 2- No");
            scanf("%d",&num);
            if(num==1){
                if(board[i].h_count<=3 && board[i].h_count>0){
                    board[i].h_count=board[i].h_count-1;
                    current_player->account=current_player->account+board[i].price;
                }
                else if(board[i].h_count==0 && board[i].owner.type==current_player->type){
                    board[i].owner.type=none;
                    current_player->account=current_player->account +board[i].price;
                }

            }
        }
    }
    

}  
void rent(struct block *board,struct player player_one,struct player player_two){
    int i;
    if(board->owner.type==car){
        for(i=0;i<=3;i++){
            if(board->h_count==i){
                if(i==0){
                    player_one.account=player_one.account - board->rent;
                    player_two.account=player_two.account + board->rent;
                }
                else if(i==1){
                    player_one.account=player_one.account - board->rent_1;
                    player_two.account=player_two.account + board->rent_1;
                }
                else if(i==2){
                    player_one.account=player_one.account - board->rent_2;
                    player_two.account=player_two.account + board->rent_2;
                }
                else if(i==3){
                    player_one.account=player_one.account - board->rent_3;
                    player_two.account=player_two.account + board->rent_3;
                }
            }
        }
    }
    else if(board->owner.type==cap){
        for(i=0;i<=3;i++){
            if(board->h_count==i){
                if(i==0){
                    player_one.account=player_one.account + board->rent;
                    player_two.account=player_two.account - board->rent;
                }
                else if(i==1){
                    player_one.account=player_one.account + board->rent_1;
                    player_two.account=player_two.account - board->rent_1;
                }
                else if(i==2){
                    player_one.account=player_one.account + board->rent_2;
                    player_two.account=player_two.account - board->rent_2;
                }
                else if(i==3){
                    player_one.account=player_one.account + board->rent_3;
                    player_two.account=player_two.account - board->rent_3;
                }
            }
        }
    }

    

}