#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "mymalloc.h"

#define MEMLENGTH 512

static char memory[MEMLENGTH];

typedef struct Node{
    size_t size;
    struct Node* next;
    bool isFree;
    char data[1];
} Node;

static Node* base = (Node*) memory;

void* mymalloc(size_t size, char* file, int line){
    if (base->size == 0)
        init();
    Node* curr = base;
    while (curr){
        if (curr->isFree && curr->size >= size){
            curr->isFree = false;
            if (curr->size > sizeof(Node) + size){
                Node* temp = (Node*) (curr->data + size);
                temp->isFree = true;
                temp->size = curr->size - size - sizeof(Node);
                temp->next = curr->next;
                curr->size = size;
                curr->next = temp;
            }
            return curr->data;
        }
        curr = curr->next;
    }
    fprintf(stderr, "Error in %s at line %d: Out of memory.\n", file, line);
    return NULL;

}

void myfree(void* ptr, char* file, int line){
    if (!ptr){
        fprintf(stderr, "Error in %s at line %d: Out of memory.\n", file, line);
        return;
    }
    Node* n = (Node*) ((char*) ptr - offsetof(Node, data));
    if (n->isFree) {
        fprintf(stderr, "Error in %s at line %d: Double free detected.\n", file, line);
        return;
    }
    n->isFree = true;
}

void init(){
    base->isFree = true;
    base->size = MEMLENGTH - sizeof(Node);
    base->next = NULL;
}
