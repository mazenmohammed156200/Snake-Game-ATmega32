#ifndef MCAL_SCHEDULER_SCHEDULER_PRIVATE_H_
#define MCAL_SCHEDULER_SCHEDULER_PRIVATE_H_

typedef struct 
{
    u16 Periodictey;
    void (*Fptr)();
}Task;


#endif
