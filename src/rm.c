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
    char* directoriesToBeRemoved[100];
    int directoryCount = 0;
    int flag_r = 0;
    int flag_d = 0;
    if (argc==1){
        printf("Usage: rm [-r] [-d] [args]\n");
        exit(1);
    }
    if (argc>1)
    {
        for (int i = 1; i < argc; i++){
            if (strcmp(argv[1], "--help")==0){
                printf("rm: rm [-r] [-d] [args]\n");
                printf("Remove files or directories.\n");
                printf("Options:\n");
                printf("  -r\t\tRemove directories and their contents recursively.\n");
                printf("  -d\t\tRemove empty directories.\n");
                exit(0);
            }
            if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "-rd") == 0 || strcmp(argv[i], "-fd") == 0)
            {
                flag_r = 1;
            }
            else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "-dr") == 0 || strcmp(argv[i], "-rd") == 0)
            {
                flag_d = 1;
            }
            else {
                directoriesToBeRemoved[directoryCount] = argv[i];
                directoryCount++;
            }
        }
    }
    // remove directory given as last argument of argv
    char *currentDirectory = getcwd(NULL, 0);
    for (int i=0; i<directoryCount; i++){
        char *dirName = directoriesToBeRemoved[i];
        char *path = (char *)malloc(strlen(currentDirectory) + strlen(dirName) + 2);
        strcpy(path, currentDirectory);
        strcat(path, "/");
        strcat(path, dirName);
        if (flag_r == 1)
        {
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
                    char *newPath = (char *)malloc(strlen(path) + strlen(entry->d_name) + 2);
                    strcpy(newPath, path);
                    strcat(newPath, "/");
                    strcat(newPath, entry->d_name);
                    remove(newPath);
                }
                entry = readdir(dir);
            }
            int status = rmdir(path);
            if (status !=0){
                perror("rmdir");
            }
        }
        else if (flag_d == 1)
        {
            rmdir(path);
        }
        else
        {
            remove(path);
        }
    }
}