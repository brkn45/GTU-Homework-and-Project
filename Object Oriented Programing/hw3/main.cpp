#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
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
/*!!! Hocam playGame() fonksiyonu içerisinde board tipi seçtirmedim. Ödev bildiriminde Constructer parametresi 
    olsun yazılıydı, Bende bu sebeble bir daha playGame fonksiyonunda board tipini sormadım */
class PegSolitaire{
    public:
        class Cell{
            public:
                Cell(): row(0), colum(0) , cellState(CellState::empty) {}
                Cell(int pRow,int pColum) : row(pRow), colum(pColum), cellState(CellState::empty){}
                Cell(int pRow,int pColum,CellState pCellStatte) : row(pRow), colum(pColum), cellState(pCellStatte){}
                inline void setRow(int pRow){row=pRow;} // helper function to access private member
                inline int getrow(){return row;}        // helper function to access private member
                inline void setColum(int pColum){colum=pColum;} // helper function to access private member
                inline int getColum()const {return colum;}      // helper function to access private member
                inline void setCellState(CellState pCellState){cellState =pCellState; } // helper function to access private member
                inline CellState getCellState()const{return cellState;} // helper function to access private member
            private:
                int row;
                int colum;
                CellState cellState; 
        };
        PegSolitaire(); // non-parameter constructer
        PegSolitaire(int pBoardType);
        PegSolitaire(int boardType,int pSize); // constructer
        
        void setBoardType(int pBoardType){boardType = pBoardType;} // helper function to access private member
        int getBoardType()const {return boardType;} // helper function to access private member
        void saveFile(string filename)const;   // Save game default paremeter
        void loadGame(string filename);        // read file and build new board
        int pegCellNumber()const;              // Peg count 
        int emptyCellNumber()const;            // Empty cell
        int outOfPegNumber()const;             // out peg number
        void printBoard()const;   // print board all board excluding sixth board
        int play(); // computer game
        int play(int moveRow,int moveColum,int moveDirection); // player game
        int playGame(); // computer automaticly move game function
        int computerMovementRow();  // helper function for computer game
        int computerMovementColum(); // helper function for computer game
        int isGameEnded();           // Game control function for ended
        void printTriangle()const;  // print triangle fun
        int computerMovement(); // computer movement
        void movementPlayer();    // player movement
        void startGame();           //startGame function
        void initBoard();       // init board
        static int getPegCount(){return totalPegCount;}  // return all peg count
        int gameTypeFun();                              // ask user for game type, computer or user
        inline int getRowSize()const {return rowSize;}  // helper fuction to access private data member
        inline void setRowSize(int pRowSize){rowSize = pRowSize;} // helper fuction to access private data member
        inline int getColumSize()const{return columSize;} // helper fuction to access private data member
        inline void setColumSize(int pColumSize){columSize = pColumSize;} // helper fuction to access private data member
        bool comparePegGames(PegSolitaire game)const; // compare 2 games peg number
        void printComputerMovement(int row,int colum,int direction); // printComputer Movement
        
    private:
        int boardType;
        int rowSize;
        int columSize;
        static int totalPegCount;
        vector<vector<Cell>> board;
        string filename;
                                                              // ask user for board type
        void createBoard();                      // create vector board 
        void drawCircle();                       // draw first board 
        void drawPlusBoard();                   // draw second board 
        void drawSmallPlusBoard();              // draw third board
        void drawShortPlusBoard();              // draw fourth board 
        void drawSquareBoard();                 // draw fifth board
        void drawTriangelBoard();               // draw sixth board 

    
};
// My helper function 
int boardRow(int boardType);    // fun parameter are board type (1-6) and return row size
int boardColum(int boardType);  // fun parameter are board type (1-6) and return colum size
int charToInt(string input);    // fun parameter are movement input commend and return row number
int parseInt(string input);     // fun parameter are movement input commend return colum number
int getDirection(string input); // fun parameter are movement input commend return direction number
int selectBoard();
char turnIntToChar(int k); // Computer movement 
int BoardSize(int boardType);

int PegSolitaire::totalPegCount = 0; // static member for active game count

//PegSOlitarire constructers for class
PegSolitaire::PegSolitaire() : boardType(1), rowSize(6), columSize(6) {
    initBoard();
    totalPegCount = totalPegCount + pegCellNumber();
}
PegSolitaire::PegSolitaire(int pBoardType) : rowSize(6), columSize(6)
{
    if(pBoardType<6 && pBoardType > 0){
        boardType = pBoardType;
    }
    else{
        boardType = BoardType::circle;
    }
    initBoard();
    totalPegCount = totalPegCount + pegCellNumber();
}
PegSolitaire::PegSolitaire(int pBoardType,int pSize) {
    if(pBoardType<7 && pBoardType > 0){
        boardType = pBoardType;
    }
    else{
        boardType = BoardType::circle;
    }
    if(pSize>5){
        rowSize   = pSize;
        columSize = pSize;
    }
    else{
        rowSize = 6;
        columSize =6;

    }
    initBoard();
    totalPegCount = totalPegCount + pegCellNumber();
}
int main(){ // user sellect board and game type
    int boardType,boardSize,selection;
    string tmp,filename;
    vector<PegSolitaire> allGames;
    
    
    for(int i=0;i<6;i++){  // start active six game
        boardSize = boardColum(i+1);
        allGames.push_back(PegSolitaire(i+1,boardSize));
    }
    
    while(true){
        cout<<"Welcome PegSolitaire Game"<<endl<<endl;
    cout<<"1-)New Game"<<endl;
    cout<<"2-)Load Game"<<endl;
    cout<<"3-)Live Game"<<endl;
    cout<<"4-)Total Peg Count"<<endl;
    cout<<"5-)Compare Game"<<endl;
    cout<<"6-)Exit"<<endl;
    cin>>selection;
    switch (selection){
        case 1:
            boardType = selectBoard();    
            boardSize = boardColum(boardType);
            allGames.push_back(PegSolitaire(boardType,boardSize));
            allGames[allGames.size()-1].startGame();
            
            
            break;
        case 2:
            
            cout<<"Enter Filename. Example [laod file.txt]"<<endl;
            cin>>tmp;
            cin>>filename;
            allGames.push_back(PegSolitaire());
            allGames[allGames.size()-1].loadGame(filename);
            allGames[allGames.size()-1].startGame();
            
            break;
        case 3:
            cout<<"Active Game Count: "<<allGames.size()<<endl<<endl;
            for(int i=0;i<allGames.size();i++){
                cout<<"Game "<<i+1<<endl;
                if(allGames[i].getBoardType() == 6){
                    allGames[i].printTriangle();
                }
                else{
                      allGames[i].printBoard(); 
                }
              
                
                
            }
            cout<<"Select the board you want to play"<<endl;
            cin>>selection;
            allGames[selection-1].startGame();
            break;
        
        case 4:
            cout<<"Active Game Count:"<<allGames[0].getPegCount()<<endl;
            break;
        case 5:
            cout<<"Compare game. Select 2 game"<<endl;
            for(int i=0;i<allGames.size();i++){
                cout<<"Game "<<i+1<<endl;
                if(allGames[i].getBoardType() == 6){
                    allGames[i].printTriangle();
                }
                else{
                      allGames[i].printBoard(); 
                } 
            }
            cout<<"Please Select 2 Game"<<endl;
            int board1,board2;
            cin>>board1;
            cin>>board2;
            if(allGames[board1].comparePegGames(board2)){
                cout<<"Board1 > Board2 true"<<endl;
            }
            else{
                cout<<"Board1 < Board2 "<<endl;
            }
            break;
        case 6:
            exit(1); 
            break;
        default:
            cout<<"Wrong Selection"<<endl;
        }
    }
}
void PegSolitaire::startGame(){
    
    int gameType;
    if(isGameEnded() ==1){ // This function controll game ended
        cout<<"This game ended, You must select another game"<<endl;
        return;
    }
    gameType  = gameTypeFun();
    
    if(GameType::playerGame  == gameType){
        
        movementPlayer();
    }
    else if(GameType::computerGame == gameType){
        srand(time(NULL));
        playGame();
    }
    else{
        return;
    }
}

int PegSolitaire::playGame(){ // Computer game cycle. if game is end, the loops  stops
    int gamePlayFlag=0,gameStatus=0;
    auto score=0; // auto
    string tmp;
    
    
    if(boardType==BoardType::triangle){
        printTriangle();
    }
    else{
        printBoard();
    }
    while(true){
        cout<<"###################################################"<<endl;
        
        gamePlayFlag = isGameEnded();
        if(gamePlayFlag == 1){
            cout<<"Game is End"<<endl;
            score = pegCellNumber();
            cout<<"Your score is "<<score<<endl;
            break;    
        }
        else{
            play();
            if(BoardType::triangle == boardType){
                printTriangle();
            }
            else{
                printBoard();
            }
            
        }
        
    }
    return 1;
}
bool PegSolitaire::comparePegGames(PegSolitaire game)const{
    return pegCellNumber() > game.pegCellNumber();
}
int PegSolitaire::pegCellNumber()const{ // return peg count
    int i=0,k=0, pegCount=0;

    for(i=0;i<board.size();i++){
        for(k=0;k<board[0].size();k++ ){
            if(board[i][k].getCellState() == CellState::peg){
                pegCount++;
            }
        }
    }
    return pegCount;
}
int PegSolitaire::emptyCellNumber()const{ // return empty cell
    int i=0,k=0, emptyCellCount=0;

    for(i=0;i<board.size();i++){
        for(k=0;k< board[i].size();k++ ){
            if(board[i][k].getCellState() == CellState::empty){
                emptyCellCount++;
            }
        }
    }
    return emptyCellCount;
}
int PegSolitaire::outOfPegNumber()const{ // return out of cell peg
    int i=0,k=0, emptyCellCount=0;

    for(i=0;i<board.size();i++){
        for(k=0;k<board[i].size();k++ ){
            if(board[i][k].getCellState() == CellState::empty){
                emptyCellCount++;
            }
        }
    }
    return emptyCellCount-1;
}
int PegSolitaire::play(){ // computer move random movement
    int i=0,k=0,row,colum;
    
    int flag=0;
       // Initialization, should only be called once.
    int r = rand()%2;
    if(r==0){
        if(flag==0){
            flag = computerMovementRow();
        }
        if(flag== -1){
            flag = computerMovementColum();
        }
        
        
    }
    else if(r==1){
        if(flag==0){
            flag = computerMovementColum();
        }
        if(flag== -1){
            flag = computerMovementRow();
        }
        
        
    }
    if(flag == 1){
        return 1;
    }
    return -1;
}
int PegSolitaire::computerMovementRow(){ // Computer move horizental
    int i=0,k=0;
    for(i=0;i<board.size();i++){
        for(k=0;k<(board[i].size() -2);k++){
            if(board[i][k].getCellState() == CellState::peg && board[i][k+1].getCellState() == CellState::peg && board[i][k+2].getCellState() == CellState::dot){
                play(i,k,Direction::right);
                printComputerMovement(i,k,Direction::right);
                return 1;
            }
            else if(board[i][k].getCellState() == CellState::dot && board[i][k+1].getCellState() == CellState::peg && board[i][k+2].getCellState() == CellState::peg){
                play(i,k+2,Direction::left);
                printComputerMovement(i,k+2,Direction::left);
                return 1;
            }
        }
    }
    return -1;
}
int PegSolitaire::computerMovementColum(){ // computer move vertical
    int i=0,k=0;
    for(k=0;k<board[0].size();k++){
        for(i=0;i<(board.size()-2);i++){
            if(board[i][k].getCellState() == CellState::peg && board[i+1][k].getCellState() == CellState::peg && board[i+2][k].getCellState() == CellState::dot){
                play(i,k,Direction::down);
                printComputerMovement(i,k,Direction::down);
                return 1;
            }
            else if(board[i][k].getCellState() == CellState::dot && board[i+1][k].getCellState() == CellState::peg && board[i+2][k].getCellState() == CellState::peg){
                play(i+2,k,Direction::up);
                printComputerMovement(i+2,k,Direction::up);
                return 1;
            }
        }
    }
    return -1;
}
void PegSolitaire::printComputerMovement(int row,int colum,int direction){ // print computer movement commend example "Computer Movement: A3-R"
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
    return 'A'+k;

}
void PegSolitaire::movementPlayer(){ // Player Game Fun, There is game cycle here
    int moveRow,moveColum,moveDirection,movementFlag=0,gameFinishControl=0;
    auto score=0;
    string input;
    while(true){ // Player game cycle
        if(BoardType::triangle == boardType){
                printTriangle();
                cout<<"You have to think of board as a parallelogram. You think to Colum as cross. ou cannot move from left diagonal";
                cout<<"Horizontal movements are normal. Exemple Movement Commend \"A3-U\" "<<endl;
            }
            else{
                printBoard();
            }
        cout<<"Select Movement "<< "You can save and load file. Example [save file.txt]. Write [exit]  for return Menu"<<endl;
        cin>>input;
        if(input.size() == 4 && input[2] == '-'){ // input commend controll
            moveColum     = charToInt(input);
            moveRow       = parseInt(input);
            moveDirection = getDirection(input);
            if(moveColum ==-1 || moveDirection == -1 || moveRow == -1){
                cerr<<"Wrong Input. Input is Board out"<<moveColum<<endl;   
            }
            else{
                movementFlag=play(moveRow,moveColum,moveDirection);
                if(movementFlag!=1){
                    cerr<<"Wrong input"<<endl;
                }
                else{
                    gameFinishControl= isGameEnded();
                    if(gameFinishControl== 1){ // The loop stops 
                        cout<<"game is finish"<<endl;
                        printBoard();
                        score =pegCellNumber();
                        cout<<"Game Score: "<<score<<endl;
                        break;
                    }   
                }
            }
        }
        else if((input[0] == 'E' || input[0] =='e' )&& (input[1] == 'X' || input[1] == 'x') 
                && (input[2] == 'I' || input[2] =='i') && (input[3] == 'T' || input[3] == 't')){
                    return;
        }
        else{
            if((input[0] == 'L' || input[0] == 'l' ) && (input[1] == 'O' || input[1] =='o') 
                && (input[2] == 'A' || input[2] == 'a') && ( input[3] == 'D' || input[3] == 'd') ){
                string filename;
                cin>>filename;
                loadGame(filename);
                
            }
            else if((input[0] == 'S' || input[0] == 's' ) && (input[1] == 'A' || input[1] =='a') 
                && (input[2] == 'V' || input[2] == 'v') && ( input[3] == 'E' || input[3] == 'e') ){
                string filename;
                cin>>filename;
                saveFile(filename);
                
                
            }
            else{
                cout<<"File didnt load or save Wrong input"<<endl;
            }
            
        }
        
        
        
        
    }
}
void PegSolitaire::saveFile(string filename)const{ // save file
    ofstream file;
    int i=0,k=0;
    file.open(filename);
    
    if(file.is_open()){
        //if(gameType == GameType::playerGame){
        file<<board.size()<<" "<<board[1].size()<<" "<<boardType<<endl;
        //}
        for(i=0;i<board.size();i++){
            for(k=0;k<board[i].size();k++){
                file<<static_cast<int> (board[i][k].getCellState())<<" ";
            }
            file<<endl;
        }
    }
    else{
        cout<<"File could not be opened"<<endl;
    }  
    file.close();
}
void PegSolitaire::loadGame(string filename){ // load file
    ifstream file;
    file.open(filename);
    if(file.is_open()){
        
        char endline ='\n',ch;
        int number,i=0,k=0;
        int size=board.size();
        for(i=0;i<size;i++){
            board[i].clear();
        }
        board.clear();
        if(file.is_open()){
            file>>rowSize;
            file>>columSize;
            file>>boardType;
            board.resize(rowSize);
            for(i=0;i<rowSize;i++){
                board[i].resize(columSize);
                for(k=0;k<columSize;k++){
                    file>>number;
                    board[i][k].setCellState(static_cast<CellState> (number));
                }
                
            }
            
        }
        totalPegCount = totalPegCount + getPegCount();
    }
    else{
        cout<<"File could not be opened"<<endl;
    }
    file.close();
       
}
int scoreCalculate(const vector<vector<CellState>> & board){ // Score Calculete fun return score
    int i=0,k=0,scoreCounter=0;
    for(i=0;i<board.size();i++){
        for(k=0;k<board[i].size();k++){
            if(board[i][k]==CellState::peg){
                scoreCounter++;
            }
        }
    }
    return scoreCounter;
}
int PegSolitaire::isGameEnded(){ // fun Checking if the game is over
    int i=0,k=0;
    for(i=0;i<board.size();i++){ // vertical control
        for(k=0;k<(board[i].size()-2);k++){
            if(board[i][k].getCellState() == CellState::peg && board[i][k+1].getCellState()  == CellState::peg && board[i][k+2].getCellState()  == CellState::dot){
                //cout<<"1) i: "<<i<<"k: "<<k<<endl;
                return -1;
            }
            else if(board[i][k].getCellState()  == CellState::dot && board[i][k+1].getCellState()  == CellState::peg && board[i][k+2].getCellState()  == CellState::peg){
                //out<<"2) i: "<<i<<"k: "<<k<<endl;
                return -1;
            }
        }
    } // horizantal kontrol
    for(k=0;k<board[0].size();k++){
        for(i=0;i<(board.size()-2);i++){
            if(board[i][k].getCellState() == CellState::peg && board[i+1][k].getCellState() == CellState::peg && board[i+2][k].getCellState() == CellState::dot){
                //cout<<"3) i: "<<i<<"k: "<<k<<endl;
                return -1;
            }
            else if(board[i][k].getCellState() == CellState::dot && board[i+1][k].getCellState() == CellState::peg && board[i+2][k].getCellState() == CellState::peg){
                //cout<<"4) i: "<<i<<"k: "<<k<<endl;
                return -1;
            }
        }
    }
    return 1;
}
int PegSolitaire::play(int moveRow,int moveColum,int moveDirection){ // change seg and remove seg
    if(moveDirection == Direction::left && (moveColum-2) >=0){
        if(board[moveRow][moveColum].getCellState() == CellState::peg){
            if( board[moveRow][moveColum-1].getCellState() == CellState::peg){
                if( board[moveRow][moveColum-2].getCellState()== CellState::dot){
                    board[moveRow][moveColum-2].setCellState(  CellState::peg);
                    board[moveRow][moveColum-1].setCellState(  CellState::dot);
                    board[moveRow][moveColum].setCellState(  CellState::dot);
                    totalPegCount--; // total peg decrease
                    return 1;
                }
            }
        }
    }
    else if(moveDirection == Direction::right && (moveColum+2) < board[0].size()){
        if(board[moveRow][moveColum].getCellState() == CellState::peg){
            if( board[moveRow][moveColum+1].getCellState() == CellState::peg){
                if( board[moveRow][moveColum+2].getCellState()== CellState::dot){
                    board[moveRow][moveColum+2].setCellState( CellState::peg);
                    board[moveRow][moveColum+1].setCellState( CellState::dot);
                    board[moveRow][moveColum].setCellState( CellState::dot);
                    totalPegCount--; // total peg decrease
                    return 1;
                }
            }
        }
    }
    else if(moveDirection == Direction::up && (moveRow-2) >=0){
        if(board[moveRow][moveColum].getCellState() == CellState::peg){
            if( board[moveRow-1][moveColum].getCellState() == CellState::peg){
                if( board[moveRow-2][moveColum].getCellState()== CellState::dot){
                    board[moveRow-2][moveColum].setCellState(  CellState::peg);
                    board[moveRow-1][moveColum].setCellState(  CellState::dot);
                    board[moveRow][moveColum].setCellState(  CellState::dot);
                    totalPegCount--; // total peg decrease
                    return 1;
                }
            }
        }
    }
    else if(moveDirection == Direction::down && (moveRow +2) < board.size()){
        if(board[moveRow][moveColum].getCellState() == CellState::peg){
            if( board[moveRow+1][moveColum].getCellState() == CellState::peg){
                if( board[moveRow+2][moveColum].getCellState()== CellState::dot){
                    board[moveRow+2][moveColum].setCellState(  CellState::peg);
                    board[moveRow+1][moveColum].setCellState(  CellState::dot);
                    board[moveRow][moveColum].setCellState(  CellState::dot);
                    totalPegCount--; // total peg decrease
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
    if(input[0] >= 'a'){
        return input[0] -97;
    }
    else{
        return input[0]  - 65;
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
int PegSolitaire::gameTypeFun(){ // User select Game type 
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
           return -1;
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
void PegSolitaire::initBoard(){ // prepared according to the type of board
    
    if(boardType==BoardType::circle){
        
        createBoard();
        drawCircle();
        //printBoard(board,CIRCLE_BOARD_ROW,CIRCLE_BOARD_COLUM);
        
    }
    else if(boardType == BoardType::plus){
        createBoard();
        drawPlusBoard();
        //printBoard(board,PLUS_BOARD_ROW,PLUS_BOARD_COLUM);
    }
    else if(boardType == BoardType::shortPlus){
        createBoard();
        drawShortPlusBoard();
        //printBoard(board,SHORTPLUS_BOARD_ROW,SHORTPLUS_BOARD_COLUM);
    }
    else if(boardType == BoardType::smallPlus){
        createBoard();
        drawSmallPlusBoard();
        //printBoard(board,SMALLPLUS_BOARD_ROW,SMALLPLUS_BOARD_COLUM);
    }
    else if(boardType == BoardType::square){
        createBoard();
        drawSquareBoard();
        //printBoard(board,SQUARE_BOARD_ROW,SQUARE_BOARD_COLUM);
    }
    else if(boardType == BoardType::triangle){
        createBoard();
        drawTriangelBoard();
        //printBoard(board,TRIANGLE_BOARD_ROW,TRIANGLE_BOARD_COLUM);
        //printTriangle(board,TRIANGLE_BOARD_ROW,TRIANGLE_BOARD_COLUM);
        
    }
    
}
void PegSolitaire::createBoard(){ // prepare board
    int i=0;
    vector<PegSolitaire::Cell> tmp;
    PegSolitaire::Cell tmpCell;
    for(i=0;i<getColumSize();i++){
        tmpCell.setCellState(CellState::empty);
        tmp.push_back(tmpCell);
        
    }
    for(i=0;i<getRowSize();i++){
        board.push_back(tmp);
    }
}
void PegSolitaire::printBoard()const{ // print board 
    int i=0,k=0;
    char letter= 'a';
    cout<<"             ";
    
    for(i=0;i<board[0].size();i++){
        cout<<static_cast<char> (letter+i) <<" ";
    }
    cout<<endl;
    for(i=0;i<rowSize;i++){
        cout<<"           "<<i+1<<" ";
        for(k=0;k<columSize;k++){
            if(board[i][k].getCellState()  == CellState::peg){
                cout<<"P ";
            }
            else if(board[i][k].getCellState() == CellState::dot){
                cout<<". ";
            }
            else if(board[i][k].getCellState() == CellState::empty){
                cout<<"  ";
            }
        }
        cout<<endl;
        
    }
}
void PegSolitaire::printTriangle()const{ // print only sixth board
    int i=0,k=0;
    char letter= 'a';
    cout<<"                ";
    
    for(i=0;i<board.size();i++){
        cout<<static_cast<char> (letter+i) <<" ";
    }
    cout<<endl;
    for(i=0;i<board.size();i++){
        
        for(int j=0;j<(board.size()-i);j++)
            cout<<" ";
        cout<<"       "<<i+1<<"  ";
        for(k=0;k<board[i].size();k++){
            if(board[i][k].getCellState() == CellState::peg){
                cout<<"P ";
            }
            else if(board[i][k].getCellState() == CellState::dot){
                cout<<". ";
            }
            else if(board[i][k].getCellState() == CellState::empty){
                cout<<"  ";
            }
        }
        cout<<endl;
        
    }
    
}
void PegSolitaire::drawCircle(){ // fill vector circle board  (1)
    int i=0,k=0,lineNumber=3;
    for(i=0; i < getRowSize() ; i++){
    
       for(k=0;k<getColumSize();k++){
            if(i==0){
                if(k>1 && k< 5 ){
                    board[i][k].setCellState(CellState::peg);
                }
                else{
                    board[i][k].setCellState(CellState::empty);
                }     
        }
        else if(i == 1){
            if(k>0 && k< 6 ){
                board[i][k].setCellState(CellState::peg);
            }
             else{
                board[i][k].setCellState(CellState::empty);
            }    
        }
        else if(i>1 && i <5){
            
                if(i==2 && k == 3){
                    board[i][k].setCellState(CellState::dot);
                }
                else{
                    board[i][k].setCellState(CellState::peg);
                } 
                
            
        }
        else if(i==5){
            if(k>0 && k< 6 ){
                board[i][k].setCellState(CellState::peg);
            }
            else{
                board[i][k].setCellState(CellState::empty);
            } 
   
        }
        else if(i ==6){
           if(k>1 && k< 5 ){
                board[i][k].setCellState(CellState::peg);
            }
            else{
                board[i][k].setCellState(CellState::empty);
            } 
        }
       }
        
    }
    
    
}
void PegSolitaire::drawPlusBoard(){ // fill vector Plus board (2)
    int i=0,k=0;
    for(i=0;i<getRowSize() ;i++){
        for(k=0;k<getColumSize();k++){
            if(i<3 && k>2 && k<6){
                board[i][k].setCellState(CellState::peg);
            }
            else if(i>2  && i<6){
                if(i==4 && k==4){
                    board[i][k].setCellState(CellState::dot);
                }
                else{
                    board[i][k].setCellState(CellState::peg);
                }

                
            }
            else if(i>5 && k>2 && k<6){
                board[i][k].setCellState(CellState::peg);
            }

            
        }
    }
}
void PegSolitaire::drawShortPlusBoard(){// fill vector short plus board (3)
    int i=0, k=0;

    for(i=0;i<getRowSize();i++){
        for(k=0;k<getColumSize();k++){
            if(i<3 && k>1 && k<5 ){
                board[i][k].setCellState(CellState::peg);
            }
            else if(i>2 && i<6){
                if(i==4 && k==3){
                    board[i][k].setCellState(CellState::dot);
                }
                else{
                    board[i][k].setCellState(CellState::peg);
                }
            }
            else if(i >5 && k>1 && k<5  ) {
                board[i][k].setCellState(CellState::peg);
            }
        }
    }
}
void PegSolitaire::drawSmallPlusBoard(){ // // fill vector small plus board (4)
    int i=0,k=0;
    for(i=0;i<getRowSize();i++){
        for(k=0;k<getColumSize();k++){
            if(i<2 && k>1 && k<5){
                board[i][k].setCellState(CellState::peg);
            }
            else if(i>1  && i<5){
                if(i==3 && k==3){
                    board[i][k].setCellState(CellState::dot);
                }
                else{
                    board[i][k].setCellState(CellState::peg);
                }

                
            }
            else if(i>4 && k>1 && k<5){
                board[i][k].setCellState(CellState::peg);
            }

            
        }
    }
}
void PegSolitaire::drawSquareBoard(){ // fill vector square board (5)
    int i=0, k=0;
    int count=1,startColum=4;
    for(i=0;i< getRowSize();i++){
        
        for(k=0;k<getColumSize();k++){
            if(i==4 && k==4){
                board[i][k].setCellState(CellState::dot);
            }
            else if(k >= startColum && k<startColum +count){
                board[i][k].setCellState(CellState::peg);
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
void PegSolitaire::drawTriangelBoard(){ // fill vector Triangle board (6)
    int i=0, k=0;
    int count=1,startColum=0;
    for(i=0;i< getRowSize();i++){
        for(k=0;k< getColumSize();k++){
            if(i==0 && k==0){
                board[i][k].setCellState(CellState::dot);
            }
            else if(  k<count){
                board[i][k].setCellState(CellState::peg);
            }
            
        }
        
        count = count +1;
        //startColum = startColum-1;
        
        
    }
}
