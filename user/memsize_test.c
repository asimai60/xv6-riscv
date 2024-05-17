#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    uint64 before = memsize();
    printf("Memory size before: %d\n", before);
    char *bytes = (char *)malloc(20000);
    if (bytes == 0) {
        printf("malloc failed\n");
        exit(1,0);
    }
    uint64 after = memsize();
    printf("Memory size after: %d\n", after);
    free(bytes);
    uint64 after_free = memsize();
    printf("Memory size after free: %d\n", after_free);
    exit(0,0);
}