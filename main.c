//////////
// MAIN //
//////////

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

/* Structs */
typedef struct Position {
  int y;
  int x;
} Position;

typedef struct Room
{
  Position position;
  int height;
  int width;

  Position doors[4];
  // Entity ** entities;
} Room;

typedef struct Entity
{
  char ch;
  Position position;
  
} Entity;

/* Functions */
bool tileWalkable(int y, int x);
int screenSetUp();
int handleInput(int input, Entity * player);
int entityMove(int y, int x, Entity * entity);
Room ** mapSetUp();
Entity * entitySetup(int y, int x, char ch);

/* Room Functions */
Room * createRoom(int y, int x, int height, int width);
int drawRoom(Room * room);

/* main */
int main () {
  
  int ch;
  Entity * player;

  srand(time(NULL));

  setlocale(LC_ALL, "");
  
  screenSetUp();

  mapSetUp();
  
  player = entitySetup(14, 14, '@');

  entityMove(player->position.y, player->position.x, player);
  
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

Room ** mapSetUp()
{
  Room ** rooms;
  rooms = malloc(sizeof(Room)*6);
  rooms[0] = createRoom(13, 13, 5, 9);
  rooms[1] = createRoom(3, 20, 5, 9);
  drawRoom(rooms[0]);
  
  return rooms;
}

Entity * entitySetup(int y, int x, char ch)
{
  Entity * newEntity;
  newEntity = malloc(sizeof(Entity));

  newEntity->position.x = x;
  newEntity->position.y = y;
  newEntity->ch = ch;
    
  return newEntity;

}

Room * createRoom(int y, int x, int height, int width)
{
  Room * newRoom;
  newRoom = malloc(sizeof(Room));
  newRoom->position.x = x;
  newRoom->position.y = y;
  newRoom->height = height;
  newRoom->width = width;


  // Top Door
  newRoom->doors[0].x = x + (rand() % (width - 1)) + 1;
  newRoom->doors[0].y = y;

  srand((unsigned) rand());
  
  // Bottom Door
  newRoom->doors[1].x = x + (rand() % (width - 1)) + 1;
  newRoom->doors[1].y = y + height;  

  srand((unsigned) rand());

  // Left Door
  newRoom->doors[2].y = y +(rand() % (height - 1)) + 1;
  newRoom->doors[2].x = x;  

  srand((unsigned) rand());
  
  // Right Door
  newRoom->doors[3].y = y + (rand() % (height - 1)) + 1;
  newRoom->doors[3].x = x + width;  

  drawRoom(newRoom);
  
  return newRoom;
  
}

int drawRoom(Room * room)
{
  int x;
  int y;
  
  // Top and Bottom Walls
  for (x = room->position.x; x <= room->position.x + room->width; x++)
    {
      if (x == room->position.x)
	{
	  mvprintw(room->position.y, x, "┌");
	  mvprintw(room->position.y + room->height, x, "└");
	} else if (x == (room->position.x + room->width))
	{
	  mvprintw(room->position.y, x, "┐");
	  mvprintw(room->position.y + room->height, x, "┘");
	} else
	{
	  mvprintw(room->position.y, x, "─");
	  mvprintw(room->position.y + room->height, x, "─");
	}
    }

  // Left and Right Walls
  for (y = room->position.y + 1; y < room->position.y + room->height; y++)
    {
      mvprintw(y, room->position.x, "│");
      mvprintw(y, room->position.x + room->width, "│");
    }

  // Doors (temp)
  mvprintw(room->doors[0].y, room->doors[0].x, "═");
  mvprintw(room->doors[1].y, room->doors[1].x, "═");
  mvprintw(room->doors[2].y, room->doors[2].x, "║"); 
  mvprintw(room->doors[3].y, room->doors[3].x, "║");

  return 0;
}

int handleInput(int input, Entity * player)
{
  switch (input)
    {
      /* MOVE */
    case 'a':
      entityMove(player->position.y, player->position.x - 1, player);
      break;
      
    case 'w':
      entityMove(player->position.y - 1, player->position.x, player);
      break;
      
    case 'd':
      entityMove(player->position.y, player->position.x + 1, player);
      break;
      
    case 's':
      entityMove(player->position.y + 1, player->position.x, player);
      break;
      
    default:
      break;
      
    }
  
  return 0;
}

int entityMove(int y, int x, Entity * entity)
{
  if (tileWalkable(y, x)) 
    {  mvprintw(entity->position.y, entity->position.x, " ");
      
      entity->position.y = y;
      entity->position.x = x;
      
      mvprintw(entity->position.y, entity->position.x, "%c", entity->ch);

      return 0;
    }

  // Tile not walkable
  return 1;
}

bool tileWalkable(int y, int x)
{
  return (mvinch(y, x) == ' ');
}

