//main//
#include "../LIB/STD.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/DOT_MATRIX/DOTMAT_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/TIMER_0/TIMER0_interface.h"
#include "../MCAL/Scheduler/Scheduler_interface.h"
#include "../MCAL/Interrupt/GIE/GIE_interface.h"
#include "../MCAL/USART/USART_config.h"
#include "../MCAL/USART/USART_interface.h"
#include "../HAL/SHIFT_REG/SHIFT_REG_interface.h"
#include "SNAKE_config.h"
#include "SNAKE_interface.h"



Snake S;
u8 CurrentDirection = RIGHT;

u8 GameStarted = 0;


void Task1(){
	DIO_SetPinValue(DIO_PORTC,DIO_PIN7,DIO_HIGH);
  DOTMAT_Refresh();
	DIO_SetPinValue(DIO_PORTC,DIO_PIN7,DIO_LOW);
}

void Task2(){

  if(GameStarted == 0)
      {
          if(DIO_GetPinValue(BUTTONS_PORT, BUTTON_RIGHT) == DIO_LOW)
          {
        	  CurrentDirection = RIGHT;
              GameStarted = 1;
          }
          else if(DIO_GetPinValue(BUTTONS_PORT, BUTTON_DOWN) == DIO_LOW)
          {
        	  CurrentDirection = DOWN;
              GameStarted = 1;
          }
          else if(DIO_GetPinValue(BUTTONS_PORT, BUTTON_UP) == DIO_LOW)
          {
        	  CurrentDirection = UP;
              GameStarted = 1;
          }
          else if(USART_Is_Read())
          {
        	  u8 Key = USART_ReceiveChar();
        	  if(Key == 's')
        		  {
        		  	  CurrentDirection = DOWN;
        		  	  GameStarted = 1;
        		  }
        	  else if(Key == 'd')
				  {
					  CurrentDirection = RIGHT;
					  GameStarted = 1;
				  }
        	  else if(Key == 'w')
				  {
					  CurrentDirection = UP;
					  GameStarted = 1;
				  }
          }
      }

  else
  {
	  CurrentDirection = Snake_GetDirection(&CurrentDirection);
	  CurrentDirection = Get_Direction_USART(&CurrentDirection);
  }

}


void Task3(){

  switch(GameStarted)
      {
          case 1:
              if (SNAKE_CheckNextPosition(&S, CurrentDirection) == 1)
              {
                  // Game Over
                  Snake_Init(&S);
                  CurrentDirection = RIGHT;
                  Snake_Draw(&S);
                  GameStarted = 0;
              }
              else
              {
                  Snake_Update(&S, CurrentDirection);
              }
              break;
      }

}


int main(void){

DIO_SetPinDirection(DIO_PORTC,DIO_PIN7,DIO_OUTPUT);
	USART_Init(Asynch_Mode,One_SB, Disable_Parity, Data_Mode_8);
	TIMER0_Init();
	ADC_Init();
	Timer0_SetPrescaler(TIMER0_PRESCALER_64);
	DOTMAT_Init();
	Snake_Init(&S);
	Bottons_Init();

	Set_Call_Back_CTC(Scheduler_ISR);
	Timer0_SetCompareValue(125);
	Timer0_COMP0_Interrupt_Enable(1);
	GIE_Enable();
	DOTMAT_Clear();
	Snake_Draw(&S);

	Tasks_creation(0, 3,Task1);
	Tasks_creation(1, 40,Task2);
    Tasks_creation(2, 100,Task3);


    while (1){

    }


return 0;
}




