#include "base.h"
using namespace BG2D;
int main(void)
{
  /*PegSolitaire tmp(2,8);
  tmp.startGame();*/ 

  /*EightPuzzle tmp2;
  tmp2.startGame();*/

  int i, j, n;
  //BoardGame2D tmp;

  vector<BoardGame2D*> game;
  vector<BoardGame2D> tmp1;
  Klotski *kl1,kl2;
  PegSolitaire *pg1 ,pg2(2,8);
  EightPuzzle *ep1,ep2;
  kl1 = new Klotski();
  pg1 = new PegSolitaire(1,7);
  ep1 = new EightPuzzle();
  
  game.push_back(kl1);
  game.push_back(static_cast<BoardGame2D*> (&kl2));
  game.push_back(pg1);
  game.push_back(static_cast<BoardGame2D*> (&pg2));
  game.push_back(ep1);
  game.push_back(static_cast<BoardGame2D*> (&ep2));
  
  BoardGame2D::playVector(game);
  /*std::cout << "\x1b[38;2;" << 5 * i << ";" << 255 - 10 * i << ";220m" 
             << "ANSI Escape Sequence " << i << std::endl;*/

  /*Klotski kl;
  kl.startGame();   */
   
  return 0;
}
