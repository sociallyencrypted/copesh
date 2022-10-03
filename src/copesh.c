#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// global variables
char *user;
char currentDirectory[100] = "/home/";

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

char *login()
{
    while (1)
    {
        char username[100];
        printf("Username: ");
        if (fgets(username, 100, stdin) == NULL)
        {
            printf("Error: Username too long");
        }
        else
        {
            strtok(username, "\n");
            return username;
        }
    }
}

int main(int argc, char **argv)
{
    printf("copesh v1.0.0\n");
    printf("Type 'help' for a list of commands\n");
    user = login();
    strcat(currentDirectory, user);
    char *commands[11] = {"exit", "help", "login", "pwd", "cd", "echo", "ls", "cat", "date", "rm", "mkdir"};
    while (1)
    {
        printf("copesh:~ %s$ ", user);
        char input[100];
        scanf("%s", input);
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
            for (int i = 0; i < 11; i++)
            {
                printf("%s\n", commands[i]);
            }
        }
        else if (strcmp(input, "login") == 0)
        {
            getchar(); // remove newline
            user = login();
            strncpy(currentDirectory, "/home/", 7);
            strcat(currentDirectory, user);
        }
        else if (strcmp(input, "pwd") == 0)
        {
            printf("%s\n", currentDirectory);
        }
        else if (strcmp(input, "date") == 0)
        {
            shell_run("date");
        }
        else
        {
            printf("Error: Command not found\n");
        }
    }
}
