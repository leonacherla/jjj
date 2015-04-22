#include "sem.h"


struct Q* RunQ;
int global = 0;

Sem* rsem; //<---0
Sem* wsem; //<---0
Sem* mutex; //<---1

int rc = 0; //reader count
int rwc = 0; //reader waiting count
int wwc = 0; //writer waiting count
int wc = 0; //write count
int test[3] = {1,2,3};
int readcount =1;
int writecount =1;

/********************
 * Function Prototypes
 ********************/
void reader();
void writer();

/*************************
 * Function Pointers
************************/
void (*r1)();
void (*r2)();
void (*r3)();
void (*w1)();
void (*w2)();

int main()
{	
	RunQ = newItem();

	mutex = (Sem*)malloc(sizeof(Sem));
	mutex->queue = newItem();
	initSem(mutex, 1);

	rsem = (Sem*)malloc(sizeof(Sem));
	rsem->queue = newItem();
	initSem(rsem,0);

	wsem = (Sem*)malloc(sizeof(Sem));
	wsem->queue = newItem();
	initSem(wsem,0);

	r1 = reader;
	r2 = reader;
	r3 = reader;
	w1 = writer;
	w2 = writer;

	/*************************
	 * Initialize Threads
	 *************************/
	start_thread(r1);
	start_thread(w1);
	start_thread(w2);
	start_thread(r2);
	start_thread(r3);

	run(); //starts the first thread
	return 0;
}

void reader()
{
 printf("----Reader %d: %p\n", readcount, RunQ->first);
 readcount++;
	
 while(1){
	// Reader enter
	P(mutex);	
	if(wwc>0 || wc>0) {
		rwc++;
		V(mutex);
		P(rsem);
		rwc--;
	}
	
	rc++;
	if(rwc>0)
		V(rsem);
	else
		V(mutex);


	//CS - read occurs here
	printf("Reader %p\n", RunQ->first);
	printf("Reading array: %d %d %d\n", test[0], test[1], test[2]);

	// Reader exit
	P(mutex);
	rc--;
	if(rc==0 && wwc>0)
		V(wsem);
	else
		V(mutex);
 }	
}

void writer()
{
 int i;
 printf("----Writer %d: %p\n", writecount, RunQ->first);
 writecount++;

  while(1) {
	// Writer enter
	P(mutex);
	if(rc>0 || wc>0) {
		wwc++;
		V(mutex);
		P(wsem);
		wwc--;
	}
	
	wc++;
	V(mutex);


	//CS - write occurs here
	printf("Writer %p\n", RunQ->first);
	for (i = 0; i < 3; i++) {
		test[i] = test[i] * 4;
	}
	printf("Writing array: %d %d %d\n", test[0], test[1], test[2]);

	// Writer exit
	P(mutex);
	wc--;
	if(rwc>0)
		V(rsem);
	else {
		if(wwc>0)
			V(wsem);
		else
			V(mutex);
	}
 }
}
