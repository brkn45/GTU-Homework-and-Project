#include "base.h"
using namespace BG2D;
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
int PegSolitaire::totalPegCount = 0; // static member for active game count

//PegSOlitarire constructers for class
PegSolitaire::PegSolitaire() : boardType(1), rowSize(6), columSize(6) {
    initialize();
    totalPegCount = totalPegCount + boardScore();
}
PegSolitaire::PegSolitaire(int pBoardType) : rowSize(6), columSize(6)
{
    if(pBoardType<6 && pBoardType > 0){
        boardType = pBoardType;
    }
    else{
        boardType = BoardType::circle;
    }
    initialize();
    totalPegCount = totalPegCount + boardScore();
}
void BoardGame2D::playVector( vector<BoardGame2D*>  game){
    cout<<"Select game"<<endl;
    int num;
    for(int i=0;i<game.size();i++){
        cout<<"Game: "<< i<<endl;
    }
    cin>>num;
    game[num]->startGame();
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
    initialize();
    totalPegCount = totalPegCount + boardScore();
}

void PegSolitaire::startGame(){
     
    int gameType;
    if(endGame() ==true){ // This function controll game ended
        cout<<"This game ended, You must select another game"<<endl;
        return;
    }
    gameType  = gameTypeFun();
    /*if(boardType==BoardType::triangle){
        printTriangle();
    }
    else{
        print();
    }*/
    
    if(GameType::playerGame  == gameType){
        
        movementPlayer();
    }
    else if(GameType::computerGame == gameType){
        int moveNum =0;
        srand(time(NULL));
        
        do{
            
            cout<<"1-)Play One Movement"<<endl;
            cout<<"2-)Play All Games Auto Movement"<<endl;
            cin>>moveNum;
            cout << "\033[2J";
            cout << "\033[1;1H";
            if(moveNum==1){
                playAuto();
            
            }
            else if(moveNum==2){
                playAutoAll();
                break;
            }
            
        }while(true);
        
    }
    else{
        return;
    }
}
void PegSolitaire::playAuto(){
    int gameStatus=0;
    auto score=0; // auto
    bool gamePlayFlag=false;
    string tmp;
    
    
    
    while(true){
        cout<<"###################################################"<<endl;
        
        gamePlayFlag = endGame();
        if(gamePlayFlag == 1){
            cout<<"Game is End"<<endl;
            score = boardScore();
            cout<<"Your score is "<<score<<endl;
            break;    
        }
        else{
            int flag;
            flag =play();
            if(flag==1)break;
            if(BoardType::triangle == boardType){
                printTriangle();
            }
            else{
                print();
            }
            
        }
        
    }
    print();
}
void PegSolitaire::playAutoAll(){ // Computer game cycle. if game is end, the loops  stops
    int gameStatus=0;
    auto score=0; // auto
    bool gamePlayFlag=false;
    string tmp;
    
    
    if(boardType==BoardType::triangle){
        printTriangle();
    }
    else{
        print();
    }
    while(true){
        cout<<"###################################################"<<endl;
        
        gamePlayFlag = endGame();
        if(gamePlayFlag == 1){
            cout<<"Game is End"<<endl;
            score = boardScore();
            cout<<"Your score is "<<score<<endl;
            break;    
        }
        else{
            
            play();
            
            if(BoardType::triangle == boardType){
                printTriangle();
            }
            else{
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                cout << "\033[2J";
                cout << "\033[1;1H";
                print();
               
            }
            
        }
        
    }
    
}
/*bool PegSolitaire::comparePegGames(PegSolitaire game)const{
    return pegCellNumber() > game.pegCellNumber();
}*/
int PegSolitaire::boardScore(){ // return peg count
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
char PegSolitaire::turnIntToChar(int k){ // fun input colum number return Letter for printComputerMovement function
    return 'A'+k;

}
bool PegSolitaire::playUser(string & input){
    int moveRow,moveColum,moveDirection,movementFlag=0,gameFinishControl=0;
    auto score=0;
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
            gameFinishControl= endGame();
            if(gameFinishControl== 1){ // The loop stops 
                cout<<"game is finish"<<endl;
                print();
                score = boardScore();
                cout<<"Game Score: "<<score<<endl;
                return true;
            }   
        }
    }
    return false;
}
void PegSolitaire::movementPlayer(){ // Player Game Fun, There is game cycle here
    int moveRow,moveColum,moveDirection,movementFlag=0,gameFinishControl=0;
    auto score=0;
    string input;
    while(true){ // Player game cycle
        if(BoardType::triangle == boardType){
                cout << "\033[2J";
                cout << "\033[1;1H";
                printTriangle();
                cout<<"You have to think of board as a parallelogram. You think to Colum as cross. ou cannot move from left diagonal";
                cout<<"Horizontal movements are normal. Exemple Movement Commend \"A3-U\" "<<endl;
            }
            else{
                cout << "\033[2J";
                cout << "\033[1;1H";
                print();
            }
        cout<<"Select Movement "<< "You can save and load file. Example [save file.txt]. Write [exit]  for return Menu"<<endl;
        cin>>input;
        if(input.size() == 4 && input[2] == '-'){ // input commend controll
            if(playUser(input)) break; 
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
bool PegSolitaire::endGame(){ // fun Checking if the game is over
    int i=0,k=0;
    for(i=0;i<board.size();i++){ // vertical control
        for(k=0;k<(board[i].size()-2);k++){
            if(board[i][k].getCellState() == CellState::peg && board[i][k+1].getCellState()  == CellState::peg && board[i][k+2].getCellState()  == CellState::dot){
                //cout<<"1) i: "<<i<<"k: "<<k<<endl;
                return false;
            }
            else if(board[i][k].getCellState()  == CellState::dot && board[i][k+1].getCellState()  == CellState::peg && board[i][k+2].getCellState()  == CellState::peg){
                //out<<"2) i: "<<i<<"k: "<<k<<endl;
                return false;
            }
        }
    } // horizantal kontrol
    for(k=0;k<board[0].size();k++){
        for(i=0;i<(board.size()-2);i++){
            if(board[i][k].getCellState() == CellState::peg && board[i+1][k].getCellState() == CellState::peg && board[i+2][k].getCellState() == CellState::dot){
                //cout<<"3) i: "<<i<<"k: "<<k<<endl;
                return false;
            }
            else if(board[i][k].getCellState() == CellState::dot && board[i+1][k].getCellState() == CellState::peg && board[i+2][k].getCellState() == CellState::peg){
                //cout<<"4) i: "<<i<<"k: "<<k<<endl;
                return false;
            }
        }
    }
    return true;
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
int PegSolitaire::getDirection(string input){ // turn input string to int
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
int PegSolitaire::parseInt(string input){ //player commend turn string to int 
    if(input[1] >= '0' && input[1] <='9'){
        return input[1] - 49;
    }
    else{
        return -1;
    }
}
int PegSolitaire::charToInt(string input){//player commend turn char to int  
    if(input[0] >= 'a'){
        return input[0] -97;
    }
    else{
        return input[0]  - 65;
    }
    
}
int PegSolitaire::boardRow(int boardType){ // board row return
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
int PegSolitaire::boardColum(int boardType){ // board colım return
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
void PegSolitaire::initialize(){ // prepared according to the type of board
    
    if(boardType==BoardType::circle){
        
        createBoard();
        drawCircle();
        //print(board,CIRCLE_BOARD_ROW,CIRCLE_BOARD_COLUM);
        
    }
    else if(boardType == BoardType::plus){
        createBoard();
        drawPlusBoard();
        //print(board,PLUS_BOARD_ROW,PLUS_BOARD_COLUM);
    }
    else if(boardType == BoardType::shortPlus){
        createBoard();
        drawShortPlusBoard();
        //print(board,SHORTPLUS_BOARD_ROW,SHORTPLUS_BOARD_COLUM);
    }
    else if(boardType == BoardType::smallPlus){
        createBoard();
        drawSmallPlusBoard();
        //print(board,SMALLPLUS_BOARD_ROW,SMALLPLUS_BOARD_COLUM);
    }
    else if(boardType == BoardType::square){
        createBoard();
        drawSquareBoard();
        //print(board,SQUARE_BOARD_ROW,SQUARE_BOARD_COLUM);
    }
    else if(boardType == BoardType::triangle){
        createBoard();
        drawTriangelBoard();
        //print(board,TRIANGLE_BOARD_ROW,TRIANGLE_BOARD_COLUM);
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
void PegSolitaire::print()const{ // print board 
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
//###################################################################

int EightPuzzle::turn=0;
int EightPuzzle::move=0;
EightPuzzle::EightPuzzle(): height(3), lenght(3){

}
int EightPuzzle::getMoves(){
	turn++;
	return turn;
}

void EightPuzzle::print()const{
    int i=0, k=0;

    for(i=0;i<height;i++){
        for(k=0;k<lenght;k++){
            if(puzzle[i][k]==lenght*height){
				cout<<"    ";
			} 
			else if(puzzle[i][k]>9)
                cout<<" "<<puzzle[i][k]<<" ";
            else
                cout<<"  "<<puzzle[i][k]<<" ";    
        }
        cout<<endl;
    }
	cout<<endl;
}

/*void EightPuzzle::setsize(int size){
    int i=0;
    cout<<"Please enter height"<<endl;
    cin>>game.height;
    cout<<"Please enter lenght"<<endl;
    cin>>game.lenght;

    game.puzzle=new int *[game.height];
    for(int i = 0; i < game.height; ++i)
      game.puzzle[i] = new int[game.lenght];
    
}*/


void EightPuzzle::initialize(){
	int i=0,k=0;
	srand(time(NULL));
	
	for(i=0;i<height;i++){
		for(k=0;k<lenght;k++){
				puzzle[i][k]=compare();	
	    }
    }
}
int EightPuzzle::compare(){
	int i=0,k=0,num=0;
	srand(time(0));
	num=rand()%(height*lenght+1);
	
	for(i=0;i<height;){
		for(k=0;k<lenght;){
			if(puzzle[i][k]==num){
				num=rand()%(lenght*height+1); // big number
				i=0;
				k=0;
			}
            else{
				k++;
			}

		}
		i++;
	}	
	return num;
}



bool EightPuzzle::playUser(string &key){
	char r='r',l='l',u='u',d='d',i='i',v='v',s='s',e='e', a='a',t='t',o='o';
	int flag=0,way=0;
	
	
	
	if(r==key[0]){
		flag=right_move();
		if(flag==1){
			cout<<"dont move enter diffrent way"<<endl;
		}
		else
			EightPuzzle::getMoves();

	}
	else if(l==key[0]){
		flag=left_move();
		if(flag==1){
			cout<<"dont move enter diffrent way"<<endl;
		}
		else
			EightPuzzle::getMoves();
	}
	else if(u==key[0]){
		flag=up_move();
		if(flag==1){
			cout<<"dont move enter diffrent way"<<endl;
		}
		else
			EightPuzzle::getMoves();
	}

	else if(d==key[0]){
		flag=down_move();
		if(flag==1){
			cout<<"dont move enter diffrent way"<<endl;
		}
		else
			EightPuzzle::getMoves();
	}
	else if(s==key[0]){
		playAuto();
	}
	
	else if(t==key[0]){
		PrintReport();
	}
	else if(o==key[0]){
		writeToFile();
	}
	else if(e==key[0]){
		readFromFile();
	}
	else if(i==key[0]){
		moveIntelligent();
	}
	else if(v==key[0]){
		while(endGame()!=1){
             std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            cout << "\033[2J";
            cout << "\033[1;1H";
			moveIntelligent();
			print();
		}
	}
	else if(a==key[0]){
		//setsize(game);
		initialize();
	}	
    return false;
}
void EightPuzzle::moveIntelligent(){
	int way[4],i=0,temp=0;

	for(i=0;i<4;i++){
		way[i]=counterFun(i);
	}

	for(i=0;i<4;i++){
		if(way[temp] > way[i]){
			temp=i;
		}
			
	}

	if(0==temp)
		right_move();
	else if(1==temp)
		left_move();
	else if(2==temp)
		up_move();
	else if(3==temp)
		down_move();
	else
		cout<<"your coding has bug"<<endl;	
	
	stage[move]=temp;
	move++;

	if(move==3){
		move=0;
		
		if(stage[0]==stage[2] || stage[1]==stage[3])
			another_move();
	}			

}
void EightPuzzle::another_move(){
	int temp=0;
		temp=rand()%4;
		if(temp==0){
			right_move();
		}
		else if(temp==1){
			left_move();
		}
		else if(temp==2){
			up_move();
		}
		else if(temp==3){
			down_move();
		}
	
}

int EightPuzzle::counterFun(int key){
	int i=0,k=0,diff=0, flag=0;

	
	if(0==key){
		flag=right_move();
		if(flag==1){
			return 9999999;
		}
		else{
			diff=boardScore();
			left_move();
			return diff;
		}
	}
	else if(1==key){
		flag=left_move();
		if(flag==1){
			return 9999999;
				
		}
		else{
			diff=boardScore();
			right_move();
			return diff;
		}
	}
	else if(2==key){
		flag=up_move();
		if(flag==1){
			return 9999999;
			
		}
		else{
			diff=boardScore();
			down_move();
			return diff;
		}
	}

	else if(3==key){
		flag=down_move();
		if(flag==1){
			return 9999999;
			
		}
		else{
			diff=boardScore();
			up_move();
			return diff;
		}
	}
    else{
        return 999999;
    }
}
int EightPuzzle::boardScore(){
	int i=0, k=0,temp_i=0,temp_k=0,mult=0,sum=0,counter=0;

	for(i=0;i<height;i++){
		for(k=0;k<lenght;k++){
			mult=(i+1)*(k+1);
			while(mult!=puzzle[i][k]){
				if(mult >puzzle[i][k]){
					if(mult-puzzle[i][k]>lenght){
						mult=mult-lenght;
					
					}
					else{
						mult=mult-1;
					}
				}
				else if(puzzle[i][k] >mult){
					if(puzzle[i][k] -mult >lenght){
						mult=mult+lenght;
					}
					else{
						mult++;
					}
				}

			counter++;
			}
		}
	}
	return counter;
}


void EightPuzzle::PrintReport(){
	cout<<"turn:"<<turn<<endl;
}
int EightPuzzle::down_move(){
	int i=0,pow=0,k=0,y=0,x=0;

	for(i=0;i<lenght;i++){
		if(puzzle[height-1][i]==height*lenght){
			return 1;
		}
	}

	for(i=0;i<height;i++){
		for(k=0;k<lenght;k++){
			if(puzzle[i][k]==height*lenght){
				y=i;
				x=k;
			}
		}	
	}
	i=y;
	k=x;
	
	//cout<<"number"<<puzzle[i][k]<<"i:"<<i<<" k:"<<k <<endl;

	puzzle[i][k]=puzzle[i+1][k];
	puzzle[i+1][k]=height*lenght;
	return 0;
}
int EightPuzzle::up_move(){
	int i=0,k=0,y=0,x=0;

	
		
		for(k=0;k<lenght;k++){
			if(puzzle[0][k]==height*lenght)
				return 1;
		}
		
		
	
	for(i=0;i<height;i++){
		for(k=0;k<lenght;k++){
			if(puzzle[i][k]==height*lenght){
				y=i;
				x=k;
			}
		}
	}
	i=y;
	k=x;
	//cout<<"number"<<puzzle[i][k]<<"i:"<<i<<" k:"<<k <<endl;

	puzzle[i][k]=puzzle[i-1][k];
	puzzle[i-1][k]=height*lenght;

	return 0;

}
int EightPuzzle::left_move(){
	int i=0,k=0,y=0,x=0;

	
		for(i=0;i<height;i++){
			if(puzzle[i][0]==lenght*height)
				return 1;
		}
	
	
	for(i=0;i<height;i++){
		for(k=0;k<lenght;k++){
			if(puzzle[i][k]==height*lenght){
				y=i;
				x=k;
			}
		}
		
	}
	i=y;
	k=x;

	puzzle[i][k]=puzzle[i][k-1];
	puzzle[i][k-1]=height*lenght;
	return 0;
}
int EightPuzzle::right_move(){
	int i=0,k=0,y=0,x=0;
	for(i=0;i<height;i++){
		if(puzzle[i][lenght-1]==lenght*height)
			return 1;
	}

	for(i=0;i<height;i++){
		for(k=0;k<lenght;k++){
			if(puzzle[i][k]==lenght*height){
				//cout<<"break"<<endl;
				y=i;
				x=k;
			}
		}
	}
	i=y;
	k=x;
	//cout<<"number:"<<puzzle[i][k]<<"i:"<<i<<" "<<"k:"<<k <<endl;

	puzzle[i][k]=puzzle[i][k+1];
	puzzle[i][k+1]=height*lenght;
	return 0;
}

void EightPuzzle::playAuto(){
   int temp=0,flag=0;
    while(flag!=1){
		temp=rand()%4;
		if(temp==0){
			flag=right_move();
		}
		else if(temp==1){
			flag=left_move();
		}
		else if(temp==2){
			flag=up_move();
		}
		else if(temp==3){
			flag=down_move();
		}
		
		
	}
    print();
}
void EightPuzzle::playAutoAll(){
	int i,temp=0;
	bool flag;
	while(flag!=1){
		temp=rand()%4;
		if(temp==0){
			right_move();
		}
		else if(temp==1){
			left_move();
		}
		else if(temp==2){
			up_move();
		}
		else if(temp==3){
			down_move();
		}
		print();
		flag=endGame();
	}
}

void  EightPuzzle::writeToFile(){
	ofstream file;
	string name;
	int i=0,k=0;
	cout<<"please enter file name"<<endl;
	cin>>name;
	file.open(name);


	for(i=0;i<height;i++){
		for(k=0;k<lenght;k++){

			file<<" "<<puzzle[i][k]<<" ";
		}
		file<<endl;
	}
	file.close();
}
void EightPuzzle::readFromFile(){
	ifstream file;
	string name;
	int i=0,k=0;
	cout<< "Please enter file name"<<endl;
	cin>>name;
	file.open(name);

	for(i=0;i<height;i++){
		for(k=0;k<lenght;k++){
			file>>puzzle[i][k];
		}
	}

	
}
bool EightPuzzle::endGame(){
	int i=0,k=0,counter=1;

	for(i=0;i<height;i++){
		for(k=0;k<lenght;k++){
			if(puzzle[i][k] != counter)
				return 0;	
		}
	}
	return 1;
}
void EightPuzzle::startGame(){
    bool flag=0;
    string key;
   initialize();
    
    while(flag!=1){
        cout<<"Prints a report:             t"<<endl;
        cout<<"Saves the current board:     e"<<endl;
        cout<<"Loads the current board:     o"<<endl;
        cout<<"Left move:                   l"<<endl;
        cout<<"Right move:                  r"<<endl;
        cout<<"Up move:                     u"<<endl;
        cout<<"Down move:                   d"<<endl;
        cout<<"Solve all BoardGame:         v"<<endl;
        cout<<"Inteligent one move:         i"<<endl;
        cout<<"Shuffle:                     s"<<endl;
        
        print();
        cin>>key;
        playUser(key);
        getMoves();
        flag=endGame();
        cout << "\033[2J";
        cout << "\033[1;1H";
    }    
    
}

//--------------------------------------------------------------------
Klotski::Klotski(){
    row =5;
    colum =5;
}
void Klotski::initialize(){
    

    board[0][0] =1;
    board[0][1] =10;
    board[0][2] =10;
    board[0][3] =2; 

    board[1][0] =1;
    board[1][1] =10;
    board[1][2] =10;
    board[1][3] =2;

    board[2][0] =3;
    board[2][1] =4;
    board[2][2] =4;
    board[2][3] =5;

   

    board[3][0] =3;
    board[3][1] =6;
    board[3][2] =7;
    board[3][3] =5;
    
    board[4][0] =8;
    board[4][1] =0;
    board[4][2] =0;
    board[4][3] =9;


    
}

void Klotski::print()const{

    int i=0,k=0;
    cout<<" ______________"<<endl;
    for(i=0;i<5;i++){
        cout<<"| ";
        for(k=0;k<4;k++){
            
            if(board[i][k]<10){
                cout<<0<<board[i][k]<<" ";

            }
            else{
                cout<<board[i][k]<<" ";
            }
            
        }
        cout<<"|"<<endl;
    }
    cout<<"|____     ____|"<<endl;
}

void Klotski::movement(){
    
    cout<<"Enter Movement(example 9l)"<<endl;
    cin>>inputMovement;
    
    inputParse();
    playUser(inputMovement);

    
}
bool Klotski::playUser(string & key){
    
    if(blockNum == 9 || blockNum == 6 || blockNum == 7 || blockNum == 8){
        
        findCordinate(blockNum);
        return replaceOneBlock();
    }
    else if(blockNum == 1 || blockNum ==2 || blockNum == 3 || blockNum == 5){
        findCordinate(blockNum);
        return replaceTwoBlockH();
    }
    else if( blockNum == 4){
        findCordinate(blockNum);
        return replaceTwoBlockV();
    }
    else if(blockNum == 10){
        findCordinate(blockNum);
        return replaceFourBlock();
    }
    else{
        return false;
    }
}
bool Klotski::replaceFourBlock(){
    if(Direction::left == direction){
        if(y >0 && board[x][y-1] ==0 && board[x+1][y-1] == 0){
            board[x][y-1] = blockNum;
            board[x+1][y-1] = blockNum;
            board[x][y+1] =0;
            board[x+1][y+1] =0;
            return true;
        }
    }
    else if(Direction::right == direction){
        if( y< 2 && board[x][y+2] ==0 && board[x+1][y+2] == 0){
            board[x][y+2] = blockNum;
            board[x+1][y+2] = blockNum;
            board[x][y] = 0;
            board[x+1][y] =0;
            return true;
        }
    }
    else if(Direction::down == direction){
        if(x<3 && board[x+2][y]==0 && board[x+2][y+1] == 0){
            board[x+2][y] = blockNum;
            board[x+2][y+1] = blockNum;
            board[x][y] =0;
            board[x][y+1] =0;
            return true;
        }
    }
    else if(Direction::up == direction){
        if(x >0 && board[x-1][y] == 0 && board[x-1][y+1] == 0){
            board[x-1][y] =blockNum;
            board[x-1][y+1] = blockNum;
            board[x+2][y] =0;
            board[x+2][y+1] =0;
            return true;
        } 
    }
    return false;
    
}
bool Klotski::replaceTwoBlockV(){
    if(Direction::left == direction){
        if(y >0 && board[x][y-1] == 0){
            board[x][y-1] = blockNum;
            board[x][y+1] =0;
            return true;
        }
    }
    else if(Direction::right == direction){
        
        if(y <3 && board[x][y+2] == 0){
            board[x][y+2] = blockNum;
            board[x][y] =0;
            return true;
        }
    }
    return false;
}
bool Klotski::replaceTwoBlockH(){
    if(Direction::left == direction){
        if(y >0 && board[x][y-1] ==0 && board[x+1][y-1] == 0 ){
            board[x][y-1] = blockNum;
            board[x+1][y-1] = blockNum;
            board[x][y] =0;
            board[x+1][y] =0;
            return true;
        }
    }
    else if(Direction::right == direction){
        if(y <3 && board[x][y+1] ==0 && board[x+1][y+1] == 0){
            board[x][y+1] = blockNum;
            board[x+1][y+1] = blockNum;
            board[x][y] =0;
            board[x+1][y] =0;
            return true; 
        }
    }
    else if(Direction::down == direction){
        if(x <4 && board[x+2][y] == 0){
            board[x+2][y] =blockNum;
            board[x][y] = 0;
            return true;
        }
        
    }
    else if(Direction::up == direction){
        if(x >0 && board[x-1][y]==0){
            board[x-1][y] =blockNum;
            board[x+1][y] =0;
            return true;
        }
    }
    return false;
}
bool Klotski::replaceOneBlock(){
    if(Direction::left == direction){
       
        if( y > 0 && board[x][y-1]==0 ){
            
            board[x][y-1] = blockNum;
            board[x][y] =0;
            
            return true; 
        }
    }
    else if(Direction::right == direction){
        if( y < 3 && board[x][y+1]==0 ){
            
            board[x][y+1] = blockNum;
            board[x][y] =0;
            
            return true; 
        }
    }
    else if(Direction::down == direction){
        if( x < 4 && board[x+1][y] == 0 ){
            board[x+1][y] = blockNum;
            board[x][y] = 0;
            return true;
        }
    }
    else if( Direction::up == direction){
        if(x >0 && board[x-1][y] == 0){
            board[x-1][y] = blockNum;
            board[x][y] = 0;
            return false;
        }
    }
    return false;
}
void Klotski::findCordinate(int num){
    int i,k;
    
    for(i=0;i<5;i++){
        for(k=0;k<4;k++){
            if(board[i][k] == num){
                x=i;
                y=k;
                return;
            }
            
        }
    }
}
bool Klotski::endGame(){
    if(board[4][1]==10 && board[4][2]==10 && board[3][1]==10 && board[3][2] == 10){
        return true;
    }
    return false;
}
void Klotski::inputParse(){

    cout<<inputMovement<<endl;
    
    if(inputMovement[0] == '1' && inputMovement[1] =='0'){ 
        blockNum =10;
        if(inputMovement[2]=='L' || inputMovement[2]=='l' ){
            direction = Direction::left;
        }
        else if(inputMovement[2]=='R' || inputMovement[2]=='r'){
            direction = Direction::right;
        }
        else if(inputMovement[2] == 'U' || inputMovement[2]=='u'){
            direction = Direction::up;
        }
        else if(inputMovement[2] == 'D' || inputMovement[2] == 'd'){
            direction = Direction::down;
        }
        else{
            cerr<<"wrong input"<<endl;
        }
    }
    else if(inputMovement[0] >= '1' && inputMovement[0] <='9'){
        blockNum =  inputMovement[0] - 48;
        if(inputMovement[1]=='L' || inputMovement[1]=='l' ){
            direction = Direction::left;
        }
        else if(inputMovement[1]=='R' || inputMovement[1]=='r'){
            direction = Direction::right;
        }
        else if(inputMovement[1] == 'U' || inputMovement[1]=='u'){
            direction = Direction::up;
        }
        else if(inputMovement[1] == 'D' || inputMovement[1] == 'd'){
            direction = Direction::down;
        }
        else{
            cerr<<"wrong input"<<endl;
        }  
    }
    else{
        
    }    

    
    
      

}
void Klotski::startGame(){
    int option;
    initialize();
    
    while(!endGame()){
        print();
        cout<<"1-)manual game"<<endl;
        cout<<"2-)Play Auto one Turn"<<endl;
        cout<<"3-)Play Auto All Turn"<<endl;
        cin>>option;
        if(option ==1){
            movement();  
        }
        else if(option ==2){
            playAuto();
        }
        else if(option == 3){
            playAutoAll();
        }
        cout << "\033[2J";
        cout << "\033[1;1H";
    }

    
    
}
void Klotski::playAuto(){
    blockNum =0;
    string input;
    srand(time(NULL));
    do{
        blockNum=rand()%10 +1; 
        direction = rand()%4+1;
        
    }while(!playUser(input));
        

}
void Klotski::playAutoAll(){
    
    while(!endGame()){
        playAuto();
        print();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        cout << "\033[2J";
        cout << "\033[1;1H";
        
    }
}
int Klotski::boardScore(){
    findCordinate(10);
    return 5-x;
}