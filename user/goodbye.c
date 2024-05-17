#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    char* exit_message = "Goodbye World xv6\n";
    exit(0,exit_message);
}