//Author: 
//sameeksha celine-1207764528
//mounica kothi -1207551588

/* Requirement: 
Method 1:
Each thread is an infinite loop, and has a critical section using a mutex semaphore.
The thread gets into the CS, prints values of global and local variables (like proj1), sleeps and exists the CS. 
Then it prints a message and sleeps and then repeats.

Method 2:
Write a producer consumer solution, using the code given in class (see notes). 
Run 2 producers and 2 consumers. 
You will have to work out some details.
 If you choose to do this you really should do method 1 first.
  Also, doing this will make it easier for you to do project 4. */

#include "sem.h"
#define SIZE 5
#include "stdio.h"
int in = 0;
int out = 0;
int g = 0;
int buffer[SIZE];
struct Sem *s;
struct Sem *sp;
struct Sem *sv;
void op();
void initbuffer();
void method1();
void method2();
void producer1(); 
void producer2();
void consumer1();
void consumer2();

//Methods

void method1() {
    
    int l = 0; //local variable to loop1
    
    if (1) printf("Started Thread number\n");
    
    while (1) {
        P(s);
        printf("Thread numbers::\tl: %d\tg: %d\n", l, g);
        g++;
        l++;
        sleep(1);
        V(s);
    }
    
    return;
}

void method2() {
    
    int l = 0; //local variable to loop2
    
    if (1) printf("Started Thread Multiples of 2\n");
    
    while (1) {
        P(s);
        printf("Thread multiples of 2::\tl: %d\tg: %d\n", l*2, g);
        g++;
        l++;
        sleep(1);
        V(s);
    }
    
    return;
}



// Producer and Consumer

void producer1() {
	while (1) {
		P(sp);
		buffer[in] = 1;	
		in = (in + 1) % SIZE;	
		op("Producer 1");
		V(sv);
	}

	return;
}



void producer2() {
	while (1) {
		P(sp);
		buffer[in] = 1;	
		in = (in) % SIZE;	
		op("Producer 2");
		V(sv);
	}

	return;
}


void consumer1() {
	while (1) {
		P(sv);
		buffer[out] = 0;	
		out = (out + 1) % SIZE;	
		op("Consumer 1");
		V(sp);
	}

	return;
}



void consumer2() {
	while (1) {
		P(sv);
		buffer[out] = 0;	
		out = (out + 1) % SIZE;	
		op("Consumer 2");
		V(sp);
	}

	return;
}



//output print fn
void op(char *fn) {
	printf("%s\t\n \tBUFFER: 1: %d\t2: %d\t3: %d\t4: %d\t5: %d\n", fn, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
	sleep(1);

	return;
}


//initializing buffer
void initbuffer() {
	int i;
	for (i = 0; i < SIZE; i++) {
		buffer[i] = 0;
	}

	return;
}


/*Method 1 
int main() {

    s = (struct Sem*) malloc(sizeof(struct Sem));
	RunQ = (struct Q*) malloc(sizeof(struct Q)); //declaring global RunQ

	initSem(s, 1);          //initializing semaphore
	initQ(RunQ);            //initializing global RunQ
	start_thread(method1);   //starting threads
	start_thread(method2);
	run(); 

	return 0;
}
*/

// Method 2
int main() {

	sp = (struct Sem*) malloc(sizeof(struct Sem));
	sv = (struct Sem*) malloc(sizeof(struct Sem));//declaring semaphore
	RunQ = (struct Q*) malloc(sizeof(struct Q)); //declaring RunQ
	initQ(RunQ);
	initSem(sp, SIZE); // initialize sp= SIZE
	initSem(sv, 0); //initialize sv=0
	initbuffer();
	start_thread(consumer1);//starting threads
	start_thread(consumer2);
	start_thread(producer1);
	start_thread(producer2);
	run();
	return 0;
}