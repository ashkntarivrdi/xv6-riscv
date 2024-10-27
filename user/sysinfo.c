#include "kernel/types.h"
#include "user/user.h"
#include "kernel/sysinfo_data.h"

int
main(int argc, char *argv[])
{
    struct sysinfo_data information;

    if(sysinfo(&information) == 0) {
        printf("Free Memory: %d Bytes\n", information.free_memory);
        printf("Running Processes: %d\n", information.running_processes);
    }
    else
        printf("Failed to fetch system information\n");

    exit(0);
}
