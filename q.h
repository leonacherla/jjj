#ifndef Q_H
#define Q_H

#include <stdlib.h>
#include <unistd.h>
#include "TCB.h"


typedef struct Q {
    struct TCB_t *first;
} Q;

void initQ(struct Q*);
void addQ(struct Q*, struct TCB_t*);
void rotateQ(struct Q*);
struct TCB_t* delQ(struct Q*);
struct TCB_t* newItem();	


void initQ(struct Q *t) {
    t->first = NULL;
    return;
}

void addQ(struct Q *t, struct TCB_t *item) {
    
    if (t->first != NULL) {
        if (t->first->next != NULL) {
            item->prev = t->first->prev;
            item->next = t->first;
            t->first->prev->next = item;
            t->first->prev = item;
        } else {
            t->first->next = item;
            t->first->prev = item;
            item->next = t->first;
            item->prev = t->first;
        
        }
    } else {
        t->first = item;
        item->prev = NULL;
        item->next = NULL;
    }
    
    return;
}
void rotateQ(struct Q *t) {
    addQ(t, delQ(t));
    return;
}

struct TCB_t* delQ(struct Q *t) {
    struct TCB_t *item = t->first;
    
    if (t->first != NULL) {
        if (t->first->next != NULL) {
            t->first->prev->next = t->first->next;
            t->first->next->prev = t->first->prev;
            t->first = t->first->next;
        } else {
            t->first = NULL;
        }
    }
    
    return item;
}

struct TCB_t* newItem() {
    struct TCB_t *item = (struct TCB_t*) malloc(sizeof(struct TCB_t));
    
    if (!item) {
        item->prev = NULL;
        item->next = NULL; 
    }
    
    return item;
}

#endif
