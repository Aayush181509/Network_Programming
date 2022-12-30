//    The following function suspends the calling process using &waitpid.
//    until a child process ends.

// #define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    pid_t pid;
    pid_t pd;

    time_t t;
    int status;
    pid = fork();
    if (pid < 0)
        perror("fork() error");
    else if (pid == 0)
    {
        printf("Child id in child process = %d and Its parents is %d\n", getpid(), getppid());
        sleep(5);
        exit(1);
    }
    else
        do
        {
            // printf('WNOHANG = %d', (int)WNOHANG);
            pd = waitpid(pid, &status, WNOHANG);
            if (pd == -1)
                perror("wait() error");
            else if (pd == 0)
            {
                time(&t);
                printf("child is still running at %s", ctime(&t));
                printf("Waiting parent process id = %d\n", getpid());
                sleep(1);
            }
            else if (pd > 0)
            {
                if (WIFEXITED(status))
                {
                    printf("child exited with status of %d\n", WEXITSTATUS(status));
                    printf("Parent id after child exit = %d\n", getpid());
                }
                else
                    puts("child did not exit successfully");
            }
        } while (pd == 0);
    return 0;
}
// waitpid.c
// Displaying waitpid.c.