#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
using namespace std;
// Boards cosnt row and colum size
#define CIRCLE_BOARD_ROW 7
#define CIRCLE_BOARD_COLUM 7
#define PLUS_BOARD_ROW 9
#define PLUS_BOARD_COLUM 9
#define SHORTPLUS_BOARD_ROW 8
#define SHORTPLUS_BOARD_COLUM 8
#define SMALLPLUS_BOARD_ROW 7
#define SMALLPLUS_BOARD_COLUM 7
#define SQUARE_BOARD_ROW 9
#define SQUARE_BOARD_COLUM 9
#define TRIANGLE_BOARD_ROW 5
#define TRIANGLE_BOARD_COLUM 5

enum GameType  {playerGame=1,computerGame=2};                                 // player type
enum BoardType {circle=1,plus=2,shortPlus=3,smallPlus=4,square=5,triangle=6}; // board type
enum class CellState {peg=1,dot=2,empty=3};                                   // Strong enum
enum Direction{left=1,right=2,up=3,down=4};                                   // Direction number

int gameTypeFun();                                                       // ask user for game type, compurer or user
void startGame(int boardType,vector<vector<CellState>> &board);          // prepare board to given parameter
void initBoard(int boardType,vector<vector<CellState>> &board);          // prepare board
int selectBoard();                                                       // ask user for board type
void createBoard(vector<vector<CellState>> & board,int colum,int row );  // create vector board 
void drawCircle(vector<vector<CellState>> &board);                       // draw first board 
void drawPlusBoard(vector<vector<CellState>> & board);                   // draw second board 
void drawSmallPlusBoard(vector<vector<CellState>> & board);              // draw third board
void drawShortPlusBoard(vector<vector<CellState>> & board);              // draw fourth board 
void drawSquareBoard(vector<vector<CellState>> & board);                 // draw fifth board
void drawTriangelBoard(vector<vector<CellState>> & board);               //draw sixth board 
void printBoard(vector<vector<CellState>> & board,int row,int colum);    // print board all board excluding sixth board
void printTriangle(vector<vector<CellState>> & board,int row,int colum); // print only sixth board
void movementPlayer(vector<vector<CellState>> & board,int boardType);    // player movement
int boardRow(int boardType);    // fun parameter are board type (1-6) and return row size
int boardColum(int boardType);  // fun parameter are board type (1-6) and return colum size
int charToInt(string input);    // fun parameter are movement input commend and return row number
int parseInt(string input);     // fun parameter are movement input commend return colum number
int getDirection(string input); // fun parameter are movement input commend return direction number
int play(int moveRow,int moveColum,int moveDirection,vector<vector<CellState>> & board); // change to seg position
int gameControl(vector<vector<CellState>> & board,int row,int colum); // fun do game controll if game is end
int scoreCalculate(vector<vector<CellState>> & board); // fun do count seg and calculate score
int computerPlayGame(vector<vector<CellState>> & board,int boardType); // computer randum play if  game isn't end 
int computerMovement(vector<vector<CellState>> & board,int boardType); // computer movement
int computerMovementRow(vector<vector<CellState>> & board,int row,int colum); // computer movement horizental
int computerMovementColum(vector<vector<CellState>> & board,int row,int colum); // computer movement vertical
void printComputerMovement(int row,int colum,int direction); // printComputer Movement
char turnIntToChar(int k); // Computer movement 
int main(){ // user sellect board and game type
    vector<vector<CellState>> board;
    int gameType=0,boardType=0;
    boardType = selectBoard();
    gameType = gameTypeFun();
    startGame(boardType,board);
    if(GameType::playerGame  == gameType){
        //startGame(boardType,board);
        movementPlayer(board,boardType);
    }
    else if(GameType::computerGame == gameType){
        srand(time(NULL));
        computerPlayGame(board,boardType);
    }
}
int computerPlayGame(vector<vector<CellState>> & board,int boardType){ // Computer game cycle. if game is end, the loops  stops
    int gamePlayFlag=0,score=0;
    printBoard(board,boardRow(boardType),boardColum(boardType));
    while(true){
        cout<<"###################################################"<<endl;
        gamePlayFlag = gameControl(board,boardRow(boardType),boardColum(boardType));
        if(gamePlayFlag == 1){
            cout<<"Game is End"<<endl;
            score = scoreCalculate(board);
            cout<<"Your score is "<<score<<endl;
            break;    
        }
        else{
            computerMovement(board,boardType);
            if(BoardType::triangle == boardType){
                printTriangle(board,boardRow(boardType),boardColum(boardType));
            }
            else{
                printBoard(board,boardRow(boardType),boardColum(boardType));
            }
            
        }
        
    }
    return 1;
}
int computerMovement(vector<vector<CellState>> & board,int boardType){ // computer move random movement
    int i=0,k=0,row,colum;
    row   = boardRow(boardType);
    colum = boardColum(boardType);
    int flag=0;
       // Initialization, should only be called once.
    int r = rand()%2;
    if(r==0){
        if(flag==0){
            flag = computerMovementRow(board,row,colum);
        }
        if(flag== -1){
            flag = computerMovementColum(board,row,colum);
        }
        
        
    }
    else if(r==1){
        if(flag==0){
            flag = computerMovementColum(board,row,colum);
        }
        if(flag== -1){
            flag = computerMovementRow(board,row,colum);
        }
        
        
    }
    if(flag == 1){
        return 1;
    }
    return -1;
}
int computerMovementRow(vector<vector<CellState>> & board,int row,int colum){ // Computer move horizental
    int i=0,k=0;
    for(i=0;i<row;i++){
        for(k=0;k<(colum-2);k++){
            if(board[i][k] == CellState::peg && board[i][k+1] == CellState::peg && board[i][k+2] == CellState::dot){
                play(i,k,Direction::right,board);
                printComputerMovement(i,k,Direction::right);
                return 1;
            }
            else if(board[i][k] == CellState::dot && board[i][k+1] == CellState::peg && board[i][k+2] == CellState::peg){
                play(i,k+2,Direction::left,board);
                printComputerMovement(i,k+2,Direction::left);
                return 1;
            }
        }
    }
    return -1;
}
int computerMovementColum(vector<vector<CellState>> & board,int row,int colum){ // computer move vertical
    int i=0,k=0;
    for(k=0;k<colum;k++){
        for(i=0;i<(row-2);i++){
            if(board[i][k] == CellState::peg && board[i+1][k] == CellState::peg && board[i+2][k] == CellState::dot){
                play(i,k,Direction::down,board);
                printComputerMovement(i,k,Direction::down);
                return 1;
            }
            else if(board[i][k] == CellState::dot && board[i+1][k] == CellState::peg && board[i+2][k] == CellState::peg){
                play(i+2,k,Direction::up,board);
                printComputerMovement(i+2,k,Direction::up);
                return 1;
            }
        }
    }
    return -1;
}
void printComputerMovement(int row,int colum,int direction){ // print computer movement commend example "Computer Movement: A3-R"
    if(Direction::left==direction){
        cout<<"Computer Movement: "<<turnIntToChar(colum)<<row+1<<"-"<<"L"<<endl;
    }
    else if(Direction::right==direction){
        cout<<"Computer Movement: "<<turnIntToChar(colum)<<row+1<<"-"<<"R"<<endl;
    }
    else if(Direction::up==direction){
        cout<<"Computer Movement: "<<turnIntToChar(colum)<<row+1<<"-"<<"U"<<endl;
    }
    else if(Direction::down==direction){
        cout<<"Computer Movement: "<<turnIntToChar(colum)<<row+1<<"-"<<"D"<<endl;
    }
}
    
char turnIntToChar(int k){ // fun input colum number return Letter for printComputerMovement function
    if(k ==0){
        return 'A';
    }
    else if(k == 1){
        return 'B';
    }
    else if(k == 2){
        return 'C';
    }
    else if(k == 3){
        return 'D';
    }
    else if(k == 4){
        return 'E';
    }
    else if(k == 5){
        return 'F';
    }
    else if(k == 6){
        return 'G';
    }
    else if(k == 7){
        return 'H';
    }
    else if(k == 8){
        return 'I';
    }
    else if( k== 9){
        return 'J';
    }
    return 'z';
}
void movementPlayer(vector<vector<CellState>> & board,int boardType){ // Player Game Fun, There is game cycle here
    int moveRow,moveColum,moveDirection,movementFlag=0,gameFinishControl=0;
    int score=0;
    string input;
    while(true){ // Player game cycle
        if(BoardType::triangle == boardType){
                printTriangle(board,boardRow(boardType),boardColum(boardType));
                cout<<"You have to think of board as a parallelogram. You think to Colum as cross. ou cannot move from left diagonal";
                cout<<"Horizontal movements are normal. Exemple Movement Commend \"A3-U\" "<<endl;
            }
            else{
                printBoard(board,boardRow(boardType),boardColum(boardType));
            }
        cout<<"Select Movement"<<endl;
        cin>>input;
        if(input.size() == 4 && input[2] == '-'){ // input commend controll
            moveColum     = charToInt(input);
            moveRow       = parseInt(input);
            moveDirection = getDirection(input);
            if(moveColum ==-1 || moveDirection == -1 || moveRow == -1){
                cout<<"Wrong Input. Input is Board out"<<moveColum<<endl;   
            }
            else{
                movementFlag=play(moveRow,moveColum,moveDirection,board);
                if(movementFlag!=1){
                    cout<<"Wrong input"<<endl;
                }
                else{
                    gameFinishControl= gameControl(board,boardRow(boardType),boardColum(boardType));
                    if(gameFinishControl== 1){ // The loop stops 
                        cout<<"game is finish"<<endl;
                        printBoard(board,boardRow(boardType),boardColum(boardType));
                        score =scoreCalculate(board);
                        cout<<"Game Score: "<<score<<endl;
                        break;
                    }   
                }
            }
        }
        else{
            cout<<"Wrong input"<<endl;
        }
        
        
        
        
    }
}
int scoreCalculate(vector<vector<CellState>> & board){ // Score Calculete fun return score
    int i=0,k=0,scoreCounter=0;
    for(i=0;i<board.size();i++){
        for(k=0;k<board[0].size();k++){
            if(board[i][k]==CellState::peg){
                scoreCounter++;
            }
        }
    }
    return scoreCounter;
}
int gameControl(vector<vector<CellState>> & board,int row,int colum){ // fun Checking if the game is over
    int i=0,k=0;
    for(i=0;i<row;i++){ // vertical control
        for(k=0;k<(colum-2);k++){
            if(board[i][k] == CellState::peg && board[i][k+1] == CellState::peg && board[i][k+2] == CellState::dot){
                //cout<<"1) i: "<<i<<"k: "<<k<<endl;
                return -1;
            }
            else if(board[i][k] == CellState::dot && board[i][k+1] == CellState::peg && board[i][k+2] == CellState::peg){
                //out<<"2) i: "<<i<<"k: "<<k<<endl;
                return -1;
            }
        }
    } // horizantal kontrol
    for(k=0;k<colum;k++){
        for(i=0;i<(row-2);i++){
            if(board[i][k] == CellState::peg && board[i+1][k] == CellState::peg && board[i+2][k] == CellState::dot){
                //cout<<"3) i: "<<i<<"k: "<<k<<endl;
                return -1;
            }
            else if(board[i][k] == CellState::dot && board[i+1][k] == CellState::peg && board[i+2][k] == CellState::peg){
                //cout<<"4) i: "<<i<<"k: "<<k<<endl;
                return -1;
            }
        }
    }
    return 1;
}
int play(int moveRow,int moveColum,int moveDirection,vector<vector<CellState>> & board){ // change seg and remove seg
    if(moveDirection == Direction::left && (moveColum-2) >=0){
        if(board[moveRow][moveColum] == CellState::peg){
            if( board[moveRow][moveColum-1] == CellState::peg){
                if( board[moveRow][moveColum-2]== CellState::dot){
                    board[moveRow][moveColum-2] = CellState::peg;
                    board[moveRow][moveColum-1] = CellState::dot;
                    board[moveRow][moveColum] = CellState::dot;
                    return 1;
                }
            }
        }
    }
    else if(moveDirection == Direction::right && (moveColum+2) < board.size()){
        if(board[moveRow][moveColum] == CellState::peg){
            if( board[moveRow][moveColum+1] == CellState::peg){
                if( board[moveRow][moveColum+2]== CellState::dot){
                    board[moveRow][moveColum+2] = CellState::peg;
                    board[moveRow][moveColum+1] = CellState::dot;
                    board[moveRow][moveColum] = CellState::dot;
                    return 1;
                }
            }
        }
    }
    else if(moveDirection == Direction::up && (moveRow-2) >=0){
        if(board[moveRow][moveColum] == CellState::peg){
            if( board[moveRow-1][moveColum] == CellState::peg){
                if( board[moveRow-2][moveColum]== CellState::dot){
                    board[moveRow-2][moveColum] = CellState::peg;
                    board[moveRow-1][moveColum] = CellState::dot;
                    board[moveRow][moveColum] = CellState::dot;
                    return 1;
                }
            }
        }
    }
    else if(moveDirection == Direction::down && (moveRow +2) < board.size()){
        if(board[moveRow][moveColum] == CellState::peg){
            if( board[moveRow+1][moveColum] == CellState::peg){
                if( board[moveRow+2][moveColum]== CellState::dot){
                    board[moveRow+2][moveColum] = CellState::peg;
                    board[moveRow+1][moveColum] = CellState::dot;
                    board[moveRow][moveColum] = CellState::dot;
                    return 1;
                }
            }
        }
    }
    return -1;    
}
int getDirection(string input){ // turn input string to int
    if(input[3] == 'L'       ||  input[3] == 'l'){
        return Direction::left;
    }
    else if(input[3] == 'R'  ||  input[3] == 'r'){
        return Direction::right;
    }
    else if(input[3] == 'U'  ||  input[3] == 'u'){
        return Direction::up;
    }
    else if(input[3] == 'D'  ||  input[3] == 'd'){
        return Direction::down;
    }
    else{
        return -1;

    } 
        }
int parseInt(string input){ //player commend turn string to int 
    if(input[1] >= '0' && input[1] <='9'){
        return input[1] - 49;
    }
    else{
        return -1;
    }
}
int charToInt(string input){//player commend turn char to int  
    if(input[0] == 'A'      || input[0] == 'a'){
        return 0;
    }
    else if(input[0] == 'B' || input[0] == 'b'){
        return 1;
    }
    else if(input[0] == 'C' || input[0] == 'c'){
        return 2;
    }
    else if(input[0] == 'D' || input[0] == 'd'){
        return 3;
    }
    else if(input[0] == 'E' || input[0] =='e'){
        return 4;
    }
    else if(input[0] == 'F' || input[0] =='f'){
        return 5;
    }
    else if(input[0] == 'G' || input[0] =='g'){
        return 6;
    }
    else if(input[0] == 'H' || input[0] =='h'){
        return 7;
    }
    else if(input[0] == 'I' || input[0] =='i'){
        return 8;
    }
    else if(input[0] == 'J' || input[0] =='j'){
        return 9;
    }
    else{
        return -1;
    }
}
int boardRow(int boardType){ // board row return
    if(boardType == BoardType::circle){
        return CIRCLE_BOARD_ROW;
    }
    else if(boardType == BoardType::plus){
        return PLUS_BOARD_ROW;
    }
    else if(boardType == BoardType::shortPlus){
        return SHORTPLUS_BOARD_ROW;
    }
    else if(boardType == BoardType::smallPlus){
        return SMALLPLUS_BOARD_ROW;
    }
    else if(boardType == BoardType::square){
        return SQUARE_BOARD_ROW;
    }
    else if(boardType == BoardType::triangle){
        return TRIANGLE_BOARD_ROW;
    }
    else{
        return -1;
    }
}
int boardColum(int boardType){ // board colım return
    if(boardType == BoardType::circle){
        return CIRCLE_BOARD_COLUM;
    }
    else if(boardType == BoardType::plus){
        return PLUS_BOARD_COLUM;
    }
    else if(boardType == BoardType::shortPlus){
        return SHORTPLUS_BOARD_COLUM;
    }
    else if(boardType == BoardType::smallPlus){
        return SMALLPLUS_BOARD_COLUM;
    }
    else if(boardType == BoardType::square){
        return SQUARE_BOARD_COLUM;
    }
    else if(boardType == BoardType::triangle){
        return TRIANGLE_BOARD_COLUM;
    }
    else{
        return -1;
    }
}

int gameTypeFun(){ // User select Game type 
    int gameType;
    
    cout<<"Select Game Type"<<endl;
    cout<<"1-)Player Game"<<endl;
    cout<<"2-)Computer Game"<<endl;
    cout<<"3-)EXIT"<<endl;
    while(true){
        cin>>gameType;
        if(gameType ==1){
            return 1;
        }
        else if(gameType==2){
            return 2;
        }
        else if(gameType == 3){
            exit(1);
        }
        else{
            cout<<"Wrong option. Please again Select game type"<<endl;
        }
    }
}
int selectBoard(){ // User select Board Type
    int boardType;
    
    
    while(true){
        cout<<"Select Board type (1--6)"<<endl;
        
        cin>>boardType;
        if(boardType > 0 && boardType < 7){
            return boardType;
        }
        else{
            cout<<"wrong choice"<<endl;
        }
    }
    
    
}

void startGame(int boardType,vector<vector<CellState>> &board){
    
    initBoard(boardType, board);
}

void initBoard(int boardType,vector<vector<CellState>> & board){ // prepared according to the type of board
    
    if(boardType==BoardType::circle){
        
        createBoard(board,CIRCLE_BOARD_ROW,CIRCLE_BOARD_COLUM);
        drawCircle(board);
        //printBoard(board,CIRCLE_BOARD_ROW,CIRCLE_BOARD_COLUM);
        
    }
    else if(boardType == BoardType::plus){
        createBoard(board,PLUS_BOARD_ROW,PLUS_BOARD_COLUM);
        drawPlusBoard(board);
        //printBoard(board,PLUS_BOARD_ROW,PLUS_BOARD_COLUM);
    }
    else if(boardType == BoardType::shortPlus){
        createBoard(board,SHORTPLUS_BOARD_ROW,SHORTPLUS_BOARD_COLUM);
        drawShortPlusBoard(board);
        //printBoard(board,SHORTPLUS_BOARD_ROW,SHORTPLUS_BOARD_COLUM);
    }
    else if(boardType == BoardType::smallPlus){
        createBoard(board,SMALLPLUS_BOARD_ROW,SMALLPLUS_BOARD_COLUM);
        drawSmallPlusBoard(board);
        //printBoard(board,SMALLPLUS_BOARD_ROW,SMALLPLUS_BOARD_COLUM);
    }
    else if(boardType == BoardType::square){
        createBoard(board,SQUARE_BOARD_ROW,SQUARE_BOARD_ROW);
        drawSquareBoard(board);
        //printBoard(board,SQUARE_BOARD_ROW,SQUARE_BOARD_COLUM);
    }
    else if(boardType == BoardType::triangle){
        createBoard(board,TRIANGLE_BOARD_ROW,TRIANGLE_BOARD_COLUM);
        drawTriangelBoard(board);
        //printBoard(board,TRIANGLE_BOARD_ROW,TRIANGLE_BOARD_COLUM);
        //printTriangle(board,TRIANGLE_BOARD_ROW,TRIANGLE_BOARD_COLUM);
        
    }
    
}
void createBoard(vector<vector<CellState>> & board,int colum,int row ){ // prepare board
    int i=0;
    vector<CellState> tmp;
    for(i=0;i<colum;i++){
        tmp.push_back(CellState::empty);
    }
    for(i=0;i<row;i++){
        board.push_back(tmp);
    }
}
void printBoard(vector<vector<CellState>> & board,int row,int colum){ // print board 
    int i=0,k=0;
    char letter= 'a';
    cout<<"             ";
    
    for(i=0;i<row;i++){
        cout<<static_cast<char> (letter+i) <<" ";
    }
    cout<<endl;
    for(i=0;i<row;i++){
        cout<<"           "<<i+1<<" ";
        for(k=0;k<colum;k++){
            if(board[i][k] == CellState::peg){
                cout<<"P ";
            }
            else if(board[i][k] == CellState::dot){
                cout<<". ";
            }
            else if(board[i][k] == CellState::empty){
                cout<<"  ";
            }
        }
        cout<<endl;
        
    }
}
void printTriangle(vector<vector<CellState>> & board,int row,int colum){ // print only sixth board
    int i=0,k=0;
    char letter= 'a';
    cout<<"                ";
    
    for(i=0;i<row;i++){
        cout<<static_cast<char> (letter+i) <<" ";
    }
    cout<<endl;
    for(i=0;i<row;i++){
        
        for(int j=0;j<(row-i);j++)
            cout<<" ";
        cout<<"       "<<i+1<<"  ";
        for(k=0;k<colum;k++){
            if(board[i][k] == CellState::peg){
                cout<<"P ";
            }
            else if(board[i][k] == CellState::dot){
                cout<<". ";
            }
            else if(board[i][k] == CellState::empty){
                cout<<"  ";
            }
        }
        cout<<endl;
        
    }
    
}
void drawCircle(vector<vector<CellState>> & board){ // fill vector circle board  (1)
    int i=0,k=0,lineNumber=3;
    for(i=0; i < 7 ; i++){
    
       for(k=0;k<7;k++){
            if(i==0){
            if(k>1 && k< 5 ){
                board[i][k]= CellState::peg;
             }
             else{
                board[i][k]= CellState::empty;
            }     
        }
        else if(i == 1){
            if(k>0 && k< 6 ){
                board[i][k]= CellState::peg;
            }
             else{
                board[i][k]= CellState::empty;
            }    
        }
        else if(i>1 && i <5){
            
                if(i==2 && k == 3){
                    board[i][k]= CellState::dot;
                }
                else{
                    board[i][k]= CellState::peg;
                } 
                
            
        }
        else if(i==5){
            if(k>0 && k< 6 ){
                board[i][k]= CellState::peg;
            }
            else{
                board[i][k]= CellState::empty;
            } 
   
        }
        else if(i ==6){
           if(k>1 && k< 5 ){
                board[i][k]= CellState::peg;
            }
            else{
                board[i][k]= CellState::empty;
            } 
        }
       }
        
    }
    
    
}
void drawPlusBoard(vector<vector<CellState>> & board){ // fill vector Plus board (2)
    int i=0,k=0;
    for(i=0;i<9 ;i++){
        for(k=0;k<9;k++){
            if(i<3 && k>2 && k<6){
                board[i][k]= CellState::peg;
            }
            else if(i>2  && i<6){
                if(i==4 && k==4){
                    board[i][k]= CellState::dot;
                }
                else{
                    board[i][k]= CellState::peg;
                }

                
            }
            else if(i>5 && k>2 && k<6){
                board[i][k]= CellState::peg;
            }

            
        }
    }
}
void drawShortPlusBoard(vector<vector<CellState>> & board){// fill vector short plus board (3)
    int i=0, k=0;

    for(i=0;i<SHORTPLUS_BOARD_ROW;i++){
        for(k=0;k<SHORTPLUS_BOARD_ROW;k++){
            if(i<3 && k>1 && k<5 ){
                board[i][k]= CellState::peg;
            }
            else if(i>2 && i<6){
                if(i==4 && k==3){
                    board[i][k]= CellState::dot;
                }
                else{
                    board[i][k]= CellState::peg;
                }
            }
            else if(i >5 && k>1 && k<5  ) {
                board[i][k]= CellState::peg;
            }
        }
    }
}
void drawSmallPlusBoard(vector<vector<CellState>> & board){ // // fill vector small plus board (4)
    int i=0,k=0;
    for(i=0;i<SMALLPLUS_BOARD_ROW ;i++){
        for(k=0;k<SMALLPLUS_BOARD_COLUM;k++){
            if(i<2 && k>1 && k<5){
                board[i][k]= CellState::peg;
            }
            else if(i>1  && i<5){
                if(i==3 && k==3){
                    board[i][k]= CellState::dot;
                }
                else{
                    board[i][k]= CellState::peg;
                }

                
            }
            else if(i>4 && k>1 && k<5){
                board[i][k]= CellState::peg;
            }

            
        }
    }
}
void drawSquareBoard(vector<vector<CellState>> & board){ // fill vector square board (5)
    int i=0, k=0;
    int count=1,startColum=4;
    for(i=0;i< SQUARE_BOARD_ROW;i++){
        
        for(k=0;k<SQUARE_BOARD_COLUM;k++){
            if(i==4 && k==4){
                board[i][k]= CellState::dot;
            }
            else if(k >= startColum && k<startColum +count){
                board[i][k]= CellState::peg;
            }
            
        }
        if(i<4){
            count = count +2;
            startColum = startColum-1;
        }
        else{
            count = count -2;
            startColum = startColum +1;
        }
    }
}
void drawTriangelBoard(vector<vector<CellState>> & board){ // fill vector Triangle board (6)
    int i=0, k=0;
    int count=1,startColum=0;
    for(i=0;i< TRIANGLE_BOARD_ROW;i++){
        
        for(k=0;k<TRIANGLE_BOARD_COLUM;k++){
            if(i==0 && k==0){
                board[i][k]= CellState::dot;
            }
            else if(  k<count){
                board[i][k]= CellState::peg;
            }
            
        }
        
        count = count +1;
        //startColum = startColum-1;
        
        
    }
}
