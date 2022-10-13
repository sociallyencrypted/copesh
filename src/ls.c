#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

void printDirectoryFiles(int flag_a, int flag_R, char *currentDirectory)
{
    DIR **subdirs = subdirs = (DIR **)malloc(1 * sizeof(DIR *));
    DIR *dir = opendir(currentDirectory);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (flag_a == 0)
        {
            if (strncmp(entry->d_name, ".", 1) == 0)
            {
                continue;
            }
        }
        printf("%s ", entry->
        d_name);
        if (flag_R == 1 && entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".git") != 0)
        {
            printf("\n%s :\n", entry->d_name);
            char buffer[1024];
            printDirectoryFiles(flag_a, flag_R, realpath(entry->d_name, buffer));
        }
    }
    printf("\n");
    closedir(dir);
}

int main(int argc, char **argv)
{
    int flag_a = 0;
    int flag_R = 0;
    if (argc > 1)
    {
        if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "-aR") == 0 || strcmp(argv[1], "-Ra") == 0)
        {
            flag_a = 1;
        }
        if (strcmp(argv[1], "-R") == 0 || strcmp(argv[1], "-Ra") == 0 || strcmp(argv[1], "-aR") == 0)
        {
            flag_R = 1;
        }
    }
    char *currentDirectory = getcwd(NULL, 0);
    printDirectoryFiles(flag_a, flag_R, currentDirectory);
    return 0;
}
