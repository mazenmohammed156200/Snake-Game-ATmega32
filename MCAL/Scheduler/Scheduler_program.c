#include "../../lib/STD.h"
#include "../../lib/BIT_MATH.h"
#include "../Scheduler/Scheduler_config.h"
#include "../Scheduler/Scheduler_interface.h"
#include "../Scheduler/Scheduler_private.h"

Task Arr[NO_OF_TASKS];

static u32 Tick_Counts = 0;
void Tasks_creation(u8 Priority, u16 Periodictey, void (*Fptr)())
{
    Arr[Priority].Periodictey = Periodictey;
    Arr[Priority].Fptr = Fptr;
}

void Scheduler()
{
    u8 i;
    for (i = 0; i < NO_OF_TASKS; i++)
    {
        if (Tick_Counts % Arr[i].Periodictey == 0)
        {
            Arr[i].Fptr();
        }
    }
}

void Scheduler_ISR()
{
    Tick_Counts++;
    Scheduler();
}
void Scheduler_Update_Periodictey(u8 Priority,u32 Periodictey){
	if(Priority<NO_OF_TASKS){
		  Arr[Priority].Periodictey = Periodictey;
	}
}
