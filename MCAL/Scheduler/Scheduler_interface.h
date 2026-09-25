#ifndef MCAL_SCHEDULER_SCHEDULER_INTERFACE_H_
#define MCAL_SCHEDULER_SCHEDULER_INTERFACE_H_

void Tasks_creation(u8 Priority, u16 Periodictey, void (*Fptr)());

void Scheduler();
void Scheduler_Update_Periodictey(u8 Priority,u32 Periodictey);
void Scheduler_ISR();

#endif
