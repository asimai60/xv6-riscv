#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    char *s = "Hello, World xv6\n";
    write(1, s, strlen(s));
    exit(0,0);
}