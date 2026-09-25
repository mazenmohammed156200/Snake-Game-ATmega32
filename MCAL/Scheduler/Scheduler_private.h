/**
 * @file Scheduler_private.h
 * @brief Private structures and definitions for Cooperative Task Scheduler.
 * @author Mazen Mohammed
 * @author Mohamed Hesham
 * @date September 2026
 */

#ifndef MCAL_SCHEDULER_SCHEDULER_PRIVATE_H_
#define MCAL_SCHEDULER_SCHEDULER_PRIVATE_H_

/**
 * @struct Task
 * @brief Structure defining task attributes.
 */
typedef struct 
{
    u16 Periodictey;    /**< Execution periodicity in tick units */
    void (*Fptr)(void); /**< Pointer to task handler function */
} Task;

#endif /* MCAL_SCHEDULER_SCHEDULER_PRIVATE_H_ */