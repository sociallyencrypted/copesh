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
    int flag_r = 0;
    int flag_d = 0;
    if (argc > 2)
    {
        if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "-rd") == 0 || strcmp(argv[1], "-fd") == 0)
        {
            flag_r = 1;
        }
        if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "-dr") == 0 || strcmp(argv[1], "-rd") == 0)
        {
            flag_d = 1;
        }
    }
    // remove directory given as last argument of argv
    char *currentDirectory = getcwd(NULL, 0);
    char *dirName = argv[argc - 1];
    char *path = (char *)malloc(strlen(currentDirectory) + strlen(dirName) + 2);
    strcpy(path, currentDirectory);
    strcat(path, "/");
    strcat(path, dirName);
    if (flag_r == 1)
    {
        // recursively delete all directories
        // use remove for files and rmdir for directories
        DIR *dir = opendir(path);
        struct dirent *entry = readdir(dir);
        while (entry != NULL)
        {
            if (entry->d_type == DT_DIR)
            {
                // directory
                char *newPath = (char *)malloc(strlen(path) + strlen(entry->d_name) + 2);
                strcpy(newPath, path);
                strcat(newPath, "/");
                strcat(newPath, entry->d_name);
                rmdir(newPath);
            }
            else
            {
                // file
                char *newPath = (char *)malloc(strlen(path) + strlen(entry->d_name) + 2);
                strcpy(newPath, path);
                strcat(newPath, "/");
                strcat(newPath, entry->d_name);
                remove(newPath);
            }
            entry = readdir(dir);
        }
        rmdir(path);
    }
    else if (flag_d == 1)
    {
        // delete directory only if empty
        rmdir(path);
    }
    else
    {
        remove(path);
    }
}