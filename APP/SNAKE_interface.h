
#ifndef APP_SNAKE_GAME_INTERFACE_H_
#define APP_SNAKE_GAME_INTERFACE_H_

typedef enum{
    UP,
    DOWN,
    RIGHT,
    LEFT
}Direction;

typedef struct{
    u8 Row;
    u8 Col;
}Point;

typedef struct
{
    Point Body[MAX_SNAKE_LENGTH];
    u8 Length;
    Point Food;
} Snake;


void Snake_Init(Snake *S);
void Bottons_Init();
u8 Snake_GetDirection(u8 *CurrentDirection);
void Snake_Update(Snake *S, u8 Direction);
 u8 SNAKE_CheckNextPosition(Snake *S, u8 Direction);
 /////////////////////////
 u8 SNAKE_CheckFoodCollision(Snake *S);

 u8 SNAKE_GetRandom8Bit();
 void SNAKE_GenerateFood(Snake *S);

 void SNAKE_Grow(Snake *S);

 u8 Get_Direction_USART(u8 *CurrentDirection);

#endif
