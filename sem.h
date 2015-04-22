//Author: 
//sameeksha celine-1207764528
//mounica kothi -1207551588



/*Requirement:
Implement the following: (in a file called sem.h)

Semaphore data structure: A value field and a queue of TCBs.

InitSem(semaphore, value): Initializes the value field with the specified value.

P(semaphore): The P routine decrements the semaphore, and if the value is less than zero then blocks the process in the queue associated with the semaphore.

V(semaphore): The V routine increments the semaphore, and if the value is 0 or negative, then takes a PCB out of the semaphore queue and puts it into the run queue. 
Note: The V routine also "yields" to the next runnable process. */


#ifndef SEM_H
#define SEM_H
#include "threads.h"
#include "stdio.h"

typedef struct Sem { 
	struct Q *queue;
	int count;		
} Sem;


void initSem(Sem*, int);
void P(Sem*);
void V(Sem*);

void initSem(Sem *s, int count) { // InitSem(semaphore, value): Initializes the value field with the specified value.
	s->queue = (struct Q*) malloc(sizeof(struct Q));
	initQ(s->queue); 
	s->count = count; //initializes value field with specified value
	return;
}


void P(Sem *s) { // P(semaphore): The P routine decrements the semaphore, and if the value is less than zero then blocks the process in the queue associated with the semaphore.
	struct TCB_t *t; 
	s->count--; // decrement semaphore
	if (s->count < 0) { //if value less than 0
		t = delQ(RunQ); // block process in queue associated with semaphore
		addQ(s->queue, t);
		swapcontext(&(t->context), &(RunQ->first->context));
	}
	return;
}


void V(Sem *s) { // V(semaphore): The V routine increments the semaphore, and if the value is 0 or negative, then takes a PCB out of the semaphore queue and puts it into the run queue. 
//Note: The V routine also "yields" to the next runnable process.
	struct TCB_t *t; 
	s->count++;
	if (s->count <= 0) { //if value <=0
		t = delQ(s->queue); //takes PCB out of semaphore queue
		addQ(RunQ, t);// adds it to RunQ
	}
	yield(); //yields to the next runnable process
	return;
}
#endif