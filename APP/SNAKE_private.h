
#ifndef APP_SNAKE_GAME_PRIVATE_H_
#define APP_SNAKE_GAME_PRIVATE_H_
#include "SNAKE_interface.h"

#define MAX_TIME_WAIT	500
void Snake_Draw(Snake *S);
u8 Snake_CheckWallCollision(Snake *S, u8 Direction);
u8 Snake_CheckSelfCollision(Snake *S, u8 Direction);
void Snake_Move(Snake *S, u8 Direction);

u8 SNAKE_IsPositionOccupied(Snake *S, u8 Row, u8 Col);








#endif
