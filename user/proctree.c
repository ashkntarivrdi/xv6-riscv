#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/process_data.h"

#define MAX_PROCS 64

void display_process_tree(struct process_data* proc_list[], int parent_ids[MAX_PROCS], int total_procs, int idx, int level) {
    if (parent_ids[idx] == -1) return;

    struct process_data* proc = proc_list[idx];

    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("└─ pid: %d, name: %s, state: %d, heap size: %d, parent id: %d, nice value: %d\n",
           proc->pid, proc->name, proc->state, proc->heap_size, proc->parent_id, proc->nice_value);

    for (int j = idx; j < total_procs; j++) {
        if (parent_ids[j] == proc->pid) {
            display_process_tree(proc_list, parent_ids, total_procs, j, level + 1);
            parent_ids[j] = -1; // Mark as visited
        }
    }
}

int main(int argc, char *argv[]) {   
    struct process_data temp_proc;
    struct process_data *procs[MAX_PROCS];
    int parent_ids[MAX_PROCS];
    uint64 result;
    int current_pid = 0;
    int proc_count = 0;
    // nice(2);
    while (1) {
        memset(&temp_proc, 0, sizeof(struct process_data));
        result = nextproc(current_pid, &temp_proc);
        
        if (result != 0 || current_pid >= MAX_PROCS) break;

        struct process_data *new_proc = malloc(sizeof(struct process_data));
        if (new_proc == 0) {
            printf("Error: Memory allocation failed\n");
            break;
        }
        *new_proc = temp_proc;
        parent_ids[proc_count] = new_proc->parent_id;
        procs[proc_count++] = new_proc;
        current_pid = temp_proc.pid;
    }

    for (int i = 0; i < proc_count; i++) {
        display_process_tree(procs, parent_ids, proc_count, i, 0);
    }
    return 0;
}
