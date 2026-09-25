/**
 * @file Scheduler_program.c
 * @brief Implementation of Cooperative Task Scheduler for ATmega32 embedded systems.
 * @details Handles task creation, periodicity updates, tick management, and dispatcher logic.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#include "../../lib/STD.h"
#include "../../lib/BIT_MATH.h"
#include "../Scheduler/Scheduler_config.h"
#include "../Scheduler/Scheduler_interface.h"
#include "../Scheduler/Scheduler_private.h"

/** @brief Array storing all registered task structures indexed by priority. */
static Task Arr[NO_OF_TASKS];

/** @brief Counter tracking absolute system timer ticks elapsed. */
static u32 Tick_Counts = 0;

/**
 * @brief Assigns a task pointer and periodicity to a specific priority slot.
 * @param[in] Priority Task array index serving as priority level.
 * @param[in] Periodictey Execution periodicity (interval between runs in ticks).
 * @param[in] Fptr Pointer to task function handler.
 * @return void
 */
void Tasks_creation(u8 Priority, u16 Periodictey, void (*Fptr)(void))
{
    if (Priority < NO_OF_TASKS)
    {
        Arr[Priority].Periodictey = Periodictey;
        Arr[Priority].Fptr = Fptr;
    }
}

/**
 * @brief Checks for tasks ready to execute based on system tick count modulus.
 * @return void
 */
void Scheduler(void)
{
    u8 i;
    for (i = 0; i < NO_OF_TASKS; i++)
    {
        if (Arr[i].Fptr != 0 && Arr[i].Periodictey != 0)
        {
            if (Tick_Counts % Arr[i].Periodictey == 0)
            {
                Arr[i].Fptr();
            }
        }
    }
}

/**
 * @brief Timer ISR handler invoked on every hardware timer tick interrupt.
 * @return void
 */
void Scheduler_ISR(void)
{
    Tick_Counts++;
    Scheduler();
}

/**
 * @brief Modifies execution periodicity for a specific registered task at runtime.
 * @param[in] Priority Target task priority index.
 * @param[in] Periodictey New periodicity value in tick units.
 * @return void
 */
void Scheduler_Update_Periodictey(u8 Priority, u32 Periodictey)
{
    if (Priority < NO_OF_TASKS)
    {
        Arr[Priority].Periodictey = (u16)Periodictey;
    }
}