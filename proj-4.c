//Sameeksha Cherla.

#include "sem.h"
#define READER 3
#define WRITER 2


TCB_t *runQ = 0;
Sem *mx = 0;
Sem *readerSemaphore = 0;
Sem *writerSemaphore = 0;
int x = 0;
int readerCount = 0;
int y = 0;
int writerCount = 0;
int value = 1;

void reader();
void reader_start();
void reader_end();

void writer();
void writer_start();
void writer_end();

void main() {
    TCB_t* threads[5];
    mx = malloc(sizeof(Sem));
readerSemaphore = malloc(sizeof(Sem));
writerSemaphore = malloc(sizeof(Sem));
    
    
InitSem(mx, 1);
InitSem(readerSemaphore, 0);
InitSem(writerSemaphore, 0);
InitQ(&RunQ);
    
int iteratorA=0;
    int iteratorB=0;
    int iteratorC=0;
    
	while (iteratorA < READER + WRITER) {	
		if (iteratorB < READER ) {
			puts("Adding reader");
			start_thread(reader);
			iteratorA++; iteratorB++;
		}
		if (iteratorC < WRITER) {
			puts("Adding writer");
			start_thread(writer);
			iteratorB++; iteratorC++;
		}
	}
	puts("runQ content:");
	printQ(RunQ);
	puts("\nstarting threads\n");
	run();
}





void reader() {
while (1 > 0) {
reader_start();
printf("Reader started");
P(mx);
printf("Reader : %d\n", value);
sleep(1);
V(mx);

printf("Reader left");
reader_end();
}
}





void reader_start() {
P(mx);
if (y > 0 || writerCount > 0) {
x++;
V(mx);
P(readerSemaphore);
x--;
}
readerCount++;
if (x > 0) {
V(readerSemaphore);
} else {
V(mx);
}
}


void reader_end() {
P(mx);
readerCount--;
if (readerCount == 0 && y > 0) {
        V(writerSemaphore);
} else {
V(mx);
}
}







void writer() {
while (1 > 0) {
writer_start();
printf("Writer started");
P(mx);
value = 2*value;
sleep(1);
V(mx);

printf("Writer left");
writer_end();
}
}

void writer_start() {
P(mx);
if (readerCount > 0 || writerCount > 0) {
y++;
V(mx);

P(writerSemaphore);
y--;
}
writerCount++;
V(mx);
}


void writer_end() {
P(mx);
writerCount--;
if (x > 0) {
        V(readerSemaphore);
}
else if (y > 0) {
V(writerSemaphore);
}
}
