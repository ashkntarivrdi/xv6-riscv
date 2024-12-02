#include "procstate.h"

struct process_data {
    int pid;
    int parent_id;
    int heap_size;
    enum procstate state;
    char name[16];
};