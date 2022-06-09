/*******
* MAIN *
********/

#include <ncurses.h>
#include <stdlib.h>

/* Structs */
typedef struct Player
{
  int xPos;
  int yPos;
  int hp;
  
} Player;

/* Functions */
int screenSetUp();
int mapSetUp();
Player * playerSetup();

/* main */
int main () {

  int ch;
  Player * user;
  
  screenSetUp();

  mapSetUp();
  
  user = playerSetup();

  while ((ch = getch()) != 'q')
    {
      
    }
  
  endwin();
  
  return 0;
}
 

int screenSetUp()
{
  initscr();
  noecho();
  refresh();

  return 0;
}

int mapSetUp()
{
  mvprintw(13, 13, " ------");
  mvprintw(14, 13, "|......|");
  mvprintw(15, 13, " ------") ;
}

Player * playerSetup()
{
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));

  newPlayer->xPos = 14;
  newPlayer->yPos = 14;
  newPlayer->hp = 5;

  mvprintw(newPlayer->yPos, newPlayer->xPos, "@");
    
  return newPlayer;

}







