/**
 * @file Scheduler_interface.h
 * @brief Interface header for Cooperative Task Scheduler.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef MCAL_SCHEDULER_SCHEDULER_INTERFACE_H_
#define MCAL_SCHEDULER_SCHEDULER_INTERFACE_H_

/**
 * @brief Creates and registers a new task into the scheduler array.
 * @param[in] Priority Priority/Index of the task (0 to NO_OF_TASKS - 1).
 * @param[in] Periodictey Task execution periodicity in terms of scheduler ticks.
 * @param[in] Fptr Pointer to the function representing task payload.
 * @return void
 */
void Tasks_creation(u8 Priority, u16 Periodictey, void (*Fptr)(void));

/**
 * @brief Evaluates dynamic task timing and executes ready tasks.
 * @return void
 */
void Scheduler(void);

/**
 * @brief Dynamically updates the execution periodicity of an existing task.
 * @param[in] Priority Priority/Index of target task.
 * @param[in] Periodictey New periodicity value in scheduler ticks.
 * @return void
 */
void Scheduler_Update_Periodictey(u8 Priority, u32 Periodictey);

/**
 * @brief Timer ISR Callback to increment tick counters and run the scheduler engine.
 * @return void
 */
void Scheduler_ISR(void);

#endif /* MCAL_SCHEDULER_SCHEDULER_INTERFACE_H_ */