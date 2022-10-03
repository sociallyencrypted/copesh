#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char **argv)
{
    int flag_m = 0;
    int perms = 0777;
    int flag_p = 0;
    if (argc > 2)
    {
        if (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "-mp") == 0 || strcmp(argv[1], "-pm") == 0)
        {
            flag_m = 1;
            perms = strtol(argv[2], 0, 8);
        }
        if (strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "-pm") == 0 || strcmp(argv[1], "-mp") == 0)
        {
            flag_p = 1;
        }
    }
    // make a directory given in argv
    char *currentDirectory = getcwd(NULL, 0);
    char *dirName = argv[argc - 1];
    char *path = (char *)malloc(strlen(currentDirectory) + strlen(dirName) + 2);
    strcpy(path, currentDirectory);
    strcat(path, "/");
    strcat(path, dirName);
    if (flag_m == 1)
    {
        mkdir(path, perms);
    }
    else if (flag_p == 1)
    {
        // recursive mkdir
        char *token = strtok(path, "/");
        char *prev = (char *)malloc(1);
        prev[0] = '\0';
        while (token != NULL)
        {
            char *newPath = (char *)malloc(strlen(prev) + strlen(token) + 2);
            strcpy(newPath, prev);
            strcat(newPath, "/");
            strcat(newPath, token);
            mkdir(newPath, perms);
            prev = newPath;
            token = strtok(NULL, "/");
        }
    }
    else
    {
        mkdir(path, perms);
    }
}
