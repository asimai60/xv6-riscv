#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{
    int cd = channelcreate();
    if (cd < 0)
    {
        printf("Failed to create channel\n");
        exit(1, 0);
    }
    write(1, "Channel created\n", 17);
    if (fork() == 0)
    {
        if (channelput(cd, 42) < 0)
        {
            char *exitmsg ="Failed to put data in channel\n";
            exit(1, exitmsg);
        }
        if(channelput(cd, 43) < 0) // Sleeps until cleared
        {
            char *exitmsg ="Failed to put data in channel\n";
            exit(1, exitmsg);
        }
        sleep(3);
        if(channeldestroy(cd) < 0)
        {
            char *exitmsg ="Failed to destroy channel\n";
            exit(1, exitmsg);
        }
    }
    else
    {
        int data;
        if (channeltake(cd, &data) < 0)
        { // 42
            char *exitmsg ="Failed to take data\n";
            exit(1, exitmsg);
        }
        write(1, "Data received: \n", 17);
        printf("%d\n", data);
        if (channeltake(cd, &data) < 0)
        { // 43
            char *exitmsg ="Failed to take data\n";
            exit(1, exitmsg);
        }
        write(1, "Data received: \n", 17);
        printf("%d\n", data);
        if (channeltake(cd, &data) < 0)
        {
            char *exitmsg ="Failed to take data\n";
            exit(1, exitmsg);
        }
    }
    char *exitmsg ="program finished\n";
    exit(0, exitmsg);
}