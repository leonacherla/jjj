#ifndef THREADS_H
#define THREADS_H
#include "q.h"

struct Q *RunQ; //RunQ global header pointer

void start_thread(void (*function)(void)) {
	TCB_t *n = newItem();            //allocating TCB via malloc from "q.h"
	void *S = (void *) malloc(8192); //allocating a stack (via malloc) of a certain size (choose 8192)
	init_TCB(n, function, S, 8192);  //call init_TCB with appropriate arguments
	addQ(RunQ, n);                   //calling addQ to add this TCB into the “RunQ” which is a global header pointer

	return;
}

void run() {
    ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(RunQ->first->context));
	return;
}

void yield() {
	ucontext_t p, q;
	getcontext(&p);
	RunQ->first->context = p; //before rotateQ
    rotateQ(RunQ);            //rotating the run Q;
	q = RunQ->first->context; //after rotateQ
    swapcontext(&p, &q);      //swaping the context, from previous thread to the thread pointed to by RunQ


	return;
}

#endif
