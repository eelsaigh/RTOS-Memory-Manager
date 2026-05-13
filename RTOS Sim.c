#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Block {
    int pid;
    int size;
    bool free;
    struct Block* next;
} Block;

Block* head = NULL;

void init(int size) {
    head = malloc(sizeof(Block));
    head->pid = 0;
    head->size = size;
    head->free = true;
    head->next = NULL;
}

void compact() {
    Block* curr = head;
    while (curr != NULL && curr->next != NULL) {
        if (curr->free && curr->next->free) {
            curr->size += curr->next->size;
            Block* temp = curr->next;
            curr->next = curr->next->next;
            free(temp);
        } else {
            curr = curr->next;
        }
    }
}

bool alloc(int pid, int req) {
    Block* curr = head;
    while (curr != NULL) {
        if (curr->free && curr->size >= req) {
            if (curr->size > req) {
                Block* split = malloc(sizeof(Block));
                split->pid = 0;
                split->size = curr->size - req;
                split->free = true;
                split->next = curr->next;
                
                curr->next = split;
                curr->size = req;
            }
            curr->free = false;
            curr->pid = pid;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void free_mem(int pid) {
    Block* curr = head;
    while (curr != NULL) {
        if (curr->pid == pid && !curr->free) {
            curr->free = true;
            curr->pid = 0;
        }
        curr = curr->next;
    }
    compact();
}

void print_map() {
    Block* curr = head;
    while (curr != NULL) {
        if (curr->free) printf("[F:%d] ", curr->size);
        else printf("[P%d:%d] ", curr->pid, curr->size);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    init(1024);
    
    alloc(1, 200);
    alloc(2, 300);
    alloc(3, 150);
    print_map();

    free_mem(2);
    print_map();

    alloc(4, 250);
    print_map();

    free_mem(1);
    free_mem(3);
    free_mem(4);
    print_map();

    return 0;
}