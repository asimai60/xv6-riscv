#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "stdbool.h"

bool checkifprime(int num);

int main(int argc, char const *argv[])
{   
    int num_checkers;
    bool finish = false;
    if (argc < 2)
        {
            num_checkers = 5;
        }
    else
        {
            num_checkers = atoi(argv[1]);
        }
    
    while (!finish)
    {
        int cd1, cd2;
        cd1 = channelcreate();
        cd2 = channelcreate();
        if (cd1 < 0 || cd2 < 0)
        {
            printf("Failed to create channel\n");
            exit(1, 0);
        }
        
        for(int i = 0; i < num_checkers; i++)
        {
            if(fork() == 0){
                int num;
                while(channeltake(cd1, &num) != -1)
                {
                    if(checkifprime(num))
                    {
                        if (channelput(cd2, num) == -1)
                        {
                            break;
                        }
                    }
                }
                channeldestroy(cd1);
                printf("C %d \n", getpid());
                exit(0, 0);
            }
        }

        if(fork() == 0)
        {
            int prime;
            for(int i = 0; i < 100; i++)
            {
                if(channeltake(cd2, &prime) != -1)
                {
                    printf("prime %d\n", prime);
                }
            }
            channeldestroy(cd2);
            printf("P %d\n", getpid());
            exit(0, 0);
        }
        
        int n = 2;
        while(channelput(cd1, n) != -1)
        {
            n++;
        }

        while(wait(0, 0) != -1);

        printf("G %d\n", getpid());

        char user_input[3];
        printf("Do you want to continue? (y/n)\n");
        if (read(0, user_input, sizeof(user_input) - 1) > 0) {
            user_input[1] = '\0'; 
            if (user_input[0] == 'n') {
                finish = true;
            }
        }
    }

    exit(0, 0);
}

bool checkifprime(int num)
{
    if (num < 2 || num % 2 == 0)
    {
        return false;
    }
    for (int i = 3; i * i <= num; i += 2)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}
