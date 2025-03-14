#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#ifndef base
#define base
using namespace std;
// Boards cosnt row and colum size
namespace BG2D{
    class BoardGame2D{
        public:
            virtual bool playUser(string & ) =0;
            //virtual void playUser() final;
            virtual void playAuto() =0;
            virtual void playAutoAll() =0; 
            virtual void print()const =0;
            //friend ostream operator<<(ostream & stream,const BoardGame2D&);
            virtual bool endGame() =0;
            virtual int boardScore()=0;
            virtual void initialize()  =0;
            static void playVector(vector <BoardGame2D*> game);
            virtual void startGame() =0;
        private:
        


    };
    enum GameType  {playerGame=1,computerGame=2};                                 // player type
    enum BoardType {circle=1,plus=2,shortPlus=3,smallPlus=4,square=5,triangle=6}; // board type
    enum class CellState {peg=1,dot=2,empty=3};                                   // Strong enum
    enum Direction{left=1,right=2,up=3,down=4};         
    class PegSolitaire : public BoardGame2D{
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
            ~PegSolitaire(){}
            void setBoardType(int pBoardType){boardType = pBoardType;} // helper function to access private member
            int getBoardType()const {return boardType;} // helper function to access private member
            void saveFile(string filename)const;   // Save game default paremeter
            void loadGame(string filename);        // read file and build new board
            int boardScore();              // Peg count 
            int emptyCellNumber()const;            // Empty cell
            int outOfPegNumber()const;             // out peg number
            void print()const;   // print board all board excluding sixth board
            int play(); // computer game
            int play(int moveRow,int moveColum,int moveDirection); // player game
            void playAutoAll(); // computer automaticly move game function
            void playAuto();
            bool playUser(string & input);
            int computerMovementRow();  // helper function for computer game
            int computerMovementColum(); // helper function for computer game
            bool endGame();           // Game control function for ended
            void printTriangle()const;  // print triangle fun
            int computerMovement(); // computer movement
            void movementPlayer();    // player movement
            void startGame();           //startGame function
            void initialize();       // init board
            static int getPegCount(){return totalPegCount;}  // return all peg count
            int gameTypeFun();                              // ask user for game type, computer or user
            inline int getRowSize()const {return rowSize;}  // helper fuction to access private data member
            inline void setRowSize(int pRowSize){rowSize = pRowSize;} // helper fuction to access private data member
            inline int getColumSize()const{return columSize;} // helper fuction to access private data member
            inline void setColumSize(int pColumSize){columSize = pColumSize;} // helper fuction to access private data member

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
            void drawTriangelBoard(); 
            // My helper function 
            int boardRow(int boardType);    // fun parameter are board type (1-6) and return row size
            int boardColum(int boardType);  // fun parameter are board type (1-6) and return colum size
            int charToInt(string input);    // fun parameter are movement input commend and return row number
            int parseInt(string input);     // fun parameter are movement input commend return colum number
            int getDirection(string input); // fun parameter are movement input commend return direction number
            int selectBoard();
            char turnIntToChar(int k); // Computer movement 
            int BoardSize(int boardType);
    };
    

    class EightPuzzle :public BoardGame2D{
        public:
             EightPuzzle();
        void print()const;
            //void setsize(EightPuzzle &game);
            void initialize();
            int compare();
            bool playUser(string & key);
            int down_move();   
            int left_move();
            int up_move();
            int right_move();
            void PrintReport();
            static int  getMoves();
            void playAuto();
            void playAutoAll();
            void  writeToFile();
            void readFromFile();
            bool endGame();
            void moveIntelligent();
            int boardScore();
            int counterFun(int i);
            void another_move();
            void startGame();
        
        private:
        int puzzle[3][3];
        int height;
        int lenght;
        static int turn;
        static int move;
        int stage[4];
    };

    class Klotski :public BoardGame2D{
        public:
            Klotski();    
            bool playUser(string &);
            void startGame();
        private:
            void initialize();
            void print()const;
            void movement();
            bool endGame();
            
            void inputParse();
            void findCordinate(int num);
            bool replaceOneBlock();
            bool replaceTwoBlockH();
            bool replaceTwoBlockV();
            bool replaceFourBlock();
            void playAuto();
            void playAutoAll();
            int boardScore();
            int direction;
            int blockNum;
            string inputMovement;
            int board[5][4];
            int row;
            int colum;
            int x,y;
    };
}

#endif