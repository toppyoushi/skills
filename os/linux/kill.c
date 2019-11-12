#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        pause();
        printf("you can never reach here lol");
    }

    kill(pid, SIGKILL);
    return 0;
}