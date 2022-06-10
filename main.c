//////////
// MAIN //
//////////

#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

/* Structs */
typedef struct Entity
{
  int yPos;
  int xPos;
  char eCh;
  
} Entity;

/* Functions */
bool tileWalkable(int y, int x);
int screenSetUp();
int mapSetUp();
int handleInput(int input, Entity * player);
int entityMove();
Entity * entitySetup(int y, int x, char ch);


/* main */
int main () {

  int ch;
  Entity * player;

  setlocale(LC_ALL, "");
  
  screenSetUp();

  mapSetUp();
  
  player = entitySetup(14, 14, '@');

  entityMove(player->yPos, player->xPos, player);
  
  while ((ch = tolower(getch())) != 'q')
    {
      handleInput(ch, player); 
    }
   
  endwin();
  
  return 0;
}
 

int screenSetUp()
{
  initscr();
  noecho();
  curs_set(0); 
  refresh();

  return 0;
}

int mapSetUp()
{
  mvprintw(13, 13, "┌─────────────┐");
  mvprintw(15, 13, "│             │");
  mvprintw(16, 13, "│             │");
  mvprintw(17, 13, "│             │");
  mvprintw(18, 13, "│             │");
  mvprintw(19, 13, "│             │");
  mvprintw(14, 13, "│             │");
  mvprintw(20, 13, "└─────────────┘");

  return 0;
}

Entity * entitySetup(int y, int x, char ch)
{
  Entity * newEntity;
  newEntity = malloc(sizeof(Entity));

  newEntity->xPos = x;
  newEntity->yPos = y;
  newEntity->eCh = ch;
    
  return newEntity;

}

int handleInput(int input, Entity * player)
{
  switch (input)
    {
      /* MOVE */
    case 'a':
      entityMove(player->yPos, player->xPos - 1, player);
      break;
      
    case 'w':
      entityMove(player->yPos - 1, player->xPos, player);
      break;
      
    case 'd':
      entityMove(player->yPos, player->xPos + 1, player);
      break;
      
    case 's':
      entityMove(player->yPos + 1, player->xPos, player);
      break;
      
    default:
      break;
      
    }
  
  return 0;
}

int entityMove(int y, int x, Entity * entity)
{
  if (tileWalkable(y, x)) 
    {  mvprintw(entity->yPos, entity->xPos, " ");
      
      entity->yPos = y;
      entity->xPos = x;
      
      mvprintw(entity->yPos, entity->xPos, "%c", entity->eCh);

      return 0;
    }

  // Tile not walkable
  return 1;
}

bool tileWalkable(int y, int x)
{
  return (mvinch(y, x) == ' ');
}

