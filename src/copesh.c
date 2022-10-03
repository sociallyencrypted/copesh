#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

// global variables

void shell_run_pthread(char *command)
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, system, command);
    pthread_join(thread_id, NULL);
}

void shell_run(char *command)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        // child process
        if (execl(command, command, NULL) == -1)
        {
            perror("copesh");
        }
        exit(0);
    }
    else if (pid < 0)
    {
        // error forking
        perror("copesh");
    }
    else
    {
        // parent process
        // wait for child to terminate
        wait(NULL);
    }
}

int main(int argc, char **argv)
{
    char *username = getenv("USER");
    printf("Logged in as %s\n", username);
    char *currentDirectory = getcwd(NULL, 0);
    printf("copesh v1.0.0\n");
    printf("Type 'help' for a list of commands\n");
    char *commands[10] = {"exit", "help", "pwd", "cd", "echo", "ls", "cat", "date", "rm", "mkdir"};
    while (1)
    {
        printf("$%s -> %s ", username, currentDirectory);
        char input[100];
        scanf("%[^\n]%*c", input);
        // if input not in commands, raise error
        if (strcmp(input, "exit") == 0)
        {
            printf("Session ended\n");
            return 0;
        }
        else if (strcmp(input, "help") == 0)
        {
            printf("copesh v1.0.0\n");
            printf("List of commands:\n");
            for (int i = 0; i < 10; i++)
            {
                printf("%s\n", commands[i]);
            }
        }
        else if (strcmp(input, "pwd") == 0)
        {
            printf("%s\n", currentDirectory);
        }
        else if (strcmp(input, "date") == 0)
        {
            shell_run_pthread("./date");
        }
        else if (strcmp(input, "ls") == 0)
        {
            shell_run("./ls");
        }
        else if (strcmp(input, "mkdir") == 0)
        {
            shell_run_pthread("./mkdir");
        }
        else
        {
            printf("Error: Command not found\n");
        }
    }
}
