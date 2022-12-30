#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == 0) {
        // This is the child process.
        printf("Child process starting...\n");
        sleep(5);
        printf("Child process finished.\n");
        return 0;
    } else {
        // This is the parent process.
        printf("Parent process waiting for child to finish...\n");
        // wait(&status);
        waitpid(child_pid, &status, 0);
        printf("Child process finished with status %d.\n", status);
        return 0;
    }
}
