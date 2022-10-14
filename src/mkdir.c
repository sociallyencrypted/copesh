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
    char* directoriesToBeCreated[100];
    if (argc==1){
        printf("Usage: mkdir [-m mode] [-p] [args]\n");
        exit(1);
    }
    if (argc > 2)
    {
        int directoryCount = 0;
        for (int i = 1; i < argc; i++)
        {
            if (strncmp(argv[i], "-m", 2) == 0 || strncmp(argv[i], "-mp", 3) == 0 || strncmp(argv[i], "-pm", 3) == 0 || strncmp(argv[i], "--mode", 4))
            {
                flag_m = 1;
                //--mode=perms or -mp=perms or -pm=perms
                perms = strtok(argv[i], "=")[1];
                //check if perms is a valid octal number
                if (perms > 777 || perms < 0)
                {
                    printf("mkdir: invalid mode: ‘%s’\n", perms);
                    exit(1);
                }
            }
            else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "-pm") == 0 || strcmp(argv[i], "-mp") == 0)
            {
                flag_p = 1;
            }
            else
            {
                directoriesToBeCreated[directoryCount] = argv[i];
                directoryCount++;
            }
        }
    }
    // make a directory given in argv
    char *currentDirectory = getcwd(NULL, 0);
    char *dirName = directoriesToBeCreated[0];
    char *path = (char *)malloc(strlen(currentDirectory) + strlen(dirName) + 2);
    strcpy(path, currentDirectory);
    strcat(path, "/");
    strcat(path, dirName);
    if (flag_p == 1)
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
            if (mkdir(newPath, perms) == -1)
            {
                perror("mkdir");
                exit(1);
            }
            prev = newPath;
            token = strtok(NULL, "/");
        }
    }
    else
    {
        mkdir(path, perms);
    }
}
