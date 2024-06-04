#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int affinity = 5;
    if(argc > 1){
        affinity = atoi(argv[1]);
    }

    if(setaffinitymask(affinity) < 0){
        char *msg = "Error setting affinity mask\n";
        write(1,msg,strlen(msg));
        exit(1,0);
    }
    int i = 0;
    for(;;){
        i++;
        if(i % 1000 == 0){
            printf("Process %d is running\n", getpid());
            sleep(1);
        }
    }

    char *msg = "affinity_test is done running\n";
    exit(0, msg);
}