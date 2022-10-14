#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/wait.h>

#include <pthread.h>
// global variables

void shell_run_pthread(char *command, char *args[10])
{
    // printf("\nRunning through shell_run_pthread...\n");
    pthread_t thread_id;
    char *commandWithArgs = malloc(100);
    strcpy(commandWithArgs, command);
    for (int i = 1; i < 10; i++)
    {
        if (args[i] != NULL)
        {
            strcat(commandWithArgs, " ");
            strcat(commandWithArgs, args[i]);
        }
        else
        {
            break;
        }
    }
    pthread_create(&thread_id, NULL, (void *)system, commandWithArgs);
    pthread_join(thread_id, NULL);
}

void shell_run(char *command, char *args[10])
{
    // printf("\nRunning through shell_run...\n");
    pid_t pid = fork();
    if (pid == 0)
    {
        if (execv(command, args) == -1)
        {
            perror("copesh");
        }
        exit(0);
    }
    else if (pid < 0)
    {
        perror("copesh");
    }
    else
    {
        wait(NULL);
    }
}

int main(int argc, char **argv)
{
    char *username = getenv("USER");
    printf("Logged in as %s\n", username);
    char *permaPath = getcwd(NULL, 0);
    char *homeDirectory = getenv("HOME");
    strcspn(homeDirectory, "\n");
    chdir(homeDirectory);
    char *currentDirectory = homeDirectory;
    printf("copesh v1.0.0\n");
    printf("Type 'help' for a list of commands\n");
    char *commands[10] = {
        "exit",
        "help",
        "pwd",
        "cd",
        "echo",
        "ls",
        "cat",
        "date",
        "rm",
        "mkdir"};
    while (1)
    {
        if (strcmp(currentDirectory, homeDirectory)==0){
            printf("$%s -> ~ ", username);
        }
        else{
            char* dirName = strrchr(currentDirectory, '/')+1;
            printf("$%s -> %s ", username, dirName);
        }
        char *command = malloc(100 * sizeof(char));
        scanf("%[^\n]%*c", command);

        char *arguments[100];
        int i = 0;
        char *token = strtok(command, " ");
        while (token != NULL)
        {
            arguments[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        arguments[i] = NULL;
        int pthreadFlag = 0;
        int commandSize = strlen(arguments[0]);
        if (arguments[0][commandSize - 2] == '&' && arguments[0][commandSize - 1] == 't')
        {
            pthreadFlag = 1;
            arguments[0][commandSize - 2] = '\0';
            arguments[0][commandSize - 1] = '\0';
        }
        int valid = 0;
        for (int j = 0; j < 10; j++)
        {
            if (strcmp(arguments[0], commands[j]) == 0)
            {
                valid = 1;
                break;
            }
        }
        if (valid == 0)
        {
            printf("Invalid command\n");
            continue;
        }

        if (strcmp(arguments[0], "exit") == 0)
        {
            printf("Session ended\n");
            exit(0);
        }
        else if (strcmp(arguments[0], "help") == 0)
        {
            printf("copesh v1.0.0\n");
            printf("List of commands:\n");
            for (int i = 0; i < 10; i++)
            {
                printf("%s\n", commands[i]);
            }
            printf("For help related to each command, type <command> --help\n");
        }
        else if (strcmp(arguments[0], "pwd") == 0)
        {
            char flagSymb = 'L';
            for (int i=1; i<100; i++){
                if (arguments[i] == NULL){
                    break;
                }
                else if (strcmp(arguments[i], "--help")==0){
                    printf("pwd: pwd[-L|-P]\n");
                    printf("Prints the current working directory\n");
                    printf("Options:\n");
                    printf("-L: print the value of $PWD if it names the current working directory\n");
                    printf("-P: print the physical directory, without any symbolic links\n");
                    break;
                }
                else if (strcmp(arguments[i], "-L")==0){
                    flagSymb = 'L';
                }
                else if (strcmp(arguments[i], "-P")==0){
                    flagSymb = 'P';
                }
                else{
                    printf("Invalid option\n");
                    break;
                }
            }
            if (flagSymb == 'L'){
                char* pwd = getenv("PWD");
                printf("%s\n", pwd);
            }
            else if (flagSymb == 'P'){
                char* pwd = getcwd(NULL, 0);
                printf("%s\n", pwd);
            }
        }
        else if (strcmp(arguments[0], "cd") == 0)
        {
            for (int i=1; i<100; i++){
                char flagDotDot = 'L';
                if (arguments[i] == NULL){
                    break;
                }
                else if (strcmp(arguments[i], "--help") == 0){
                    printf("cd: cd [-L|-P][directory]\n");
                    printf("Change the current directory to [directory].\n");
                    printf("If [directory] is not specified, change to the home directory.\n");
                    printf("If [directory] is .., change to the previous directory.\n");
                    printf("Options:");
                    printf("  -L  Handle dot-dot logically.\n");
                    printf("      This is the default behavior.\n");
                    printf("  -P  Handle dot-dot physically.\n");
                    break;
                }
                else if (strcmp(arguments[i], "-L") == 0){
                    flagDotDot = 'L';
                }
                else if (strcmp(arguments[i], "-P") == 0){
                    flagDotDot = 'P';
                }
                else if (strncmp(arguments[i], "~", 1) == 0)
                {
                    char *temp = malloc(100 * sizeof(char));
                    strcpy(temp, homeDirectory);
                    strcat(temp, arguments[i] + 1);
                    strcpy(arguments[i], temp);
                    if (chdir(arguments[i]) == -1)
                    {
                        perror("copesh");
                    }
                    else
                    {
                        currentDirectory = getcwd(NULL, 0);
                    }
                    break;
                }
                else if (strcmp(arguments[i], "..") == 0){
                    if (flagDotDot == 'L'){
                        char* temp = strrchr(currentDirectory, '/');
                        *temp = '\0';
                    }
                    else if (flagDotDot == 'P'){
                        char* temp = strrchr(currentDirectory, '/');
                        *temp = '\0';
                        temp = strrchr(currentDirectory, '/');
                        *temp = '\0';
                    }
                    if (chdir(currentDirectory) == -1){
                        perror("copesh");
                    }
                    else{
                        currentDirectory = getcwd(NULL, 0);
                    }
                    break;
                }
                else{
                    char* path = malloc(100 * sizeof(char));
                    strcpy(path, currentDirectory);
                    strcat(path, "/");
                    strcat(path, arguments[i]);
                    if (chdir(path) == -1){
                        perror("copesh");
                    }
                    else{
                        currentDirectory = getcwd(NULL, 0);

                    }
                    break;
                }
            }
        }
        else if (strcmp(arguments[0], "echo") == 0)
        {
            int flag_n = 0;
            for (int i = 1; i < 100; i++)
            {
                if (arguments[i] == NULL)
                {
                    break;
                }
                else if (strcmp(arguments[i], "--help") == 0){
                    printf("Usage: echo [STRING]...\n");
                    printf("Echo the STRING(s) to standard output.\n");
                    printf("Options:\n");
                    printf("  -n     do not output the trailing newline\n");
                    break;
                }
                else if (strcmp(arguments[i],"-n")==0){
                    flag_n = 1;
                }
                else
                {
                    char *arg = arguments[i];
                    int len = strlen(arg);
                    if (arg[0] == '"' || arg[0]=='\''){
                        arg++;
                        len--;
                    }
                    if (arg[len-1] == '"' || arg[len-1]=='\''){
                        arg[len-1] = '\0';
                    }
                    printf("%s ", arg);
                }
            }
            if (flag_n == 0){
                printf("\n");
            }
        }
        else
        {
            char *commandPath = malloc(1024 * sizeof(char));
            strcpy(commandPath, permaPath);
            strcat(commandPath, "/");
            strcat(commandPath, arguments[0]);
            if (pthreadFlag == 1)
            {
                shell_run_pthread(commandPath, arguments);
            }
            else
            {
                shell_run(commandPath, arguments);
            }
        }
    }
}