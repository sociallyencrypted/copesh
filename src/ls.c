#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

void printDirectoryFiles(int flag_a, int flag_R, char *currentDirectory, char* originalDirectory)
{
    DIR *dir = opendir(currentDirectory);
    struct dirent *entry;
    char **subdirectories = malloc(1*sizeof(char *));
    subdirectories[0] = NULL;
    while ((entry = readdir(dir)) != NULL)
    {
        if (flag_a == 0)
        {
            if (strncmp(entry->d_name, ".", 1) == 0)
            {
                continue;
            }
        }
        printf("%s ", entry->d_name);
        if (flag_R == 1 && entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && entry->d_name != NULL)
        {
            // add all subdirectories to the char* list subdirectories
            // then call printDirectoryFiles on each subdirectory
            int i = 0;
            while (subdirectories[i] != NULL)
            {
                i++;
            }
            subdirectories = realloc(subdirectories, (i+2)*sizeof(char *));
            subdirectories[i] = malloc(100);
            strcpy(subdirectories[i], currentDirectory);
            strcat(subdirectories[i], "/");
            strcat(subdirectories[i], entry->d_name);
            subdirectories[i+1] = NULL;
        }
    }
    printf("\n");
    // print the subdirs
    if (flag_R == 1){
        printf("\n");
        int i = 0;
        while (subdirectories[i] != NULL)
        {
            // print relative path to originalDirectory
            char *relativePath = malloc((strlen(subdirectories[i])+1)*sizeof(char));
            strcpy(relativePath, subdirectories[i]);
            int j = strlen(originalDirectory)+1;
            while (relativePath[j] != '\0')
            {
                printf("%c", relativePath[j]);
                j++;
            }
            printf(":\n");
            printDirectoryFiles(flag_a, flag_R, subdirectories[i], originalDirectory);
            i++;
        }
    }
    closedir(dir);
}

int main(int argc, char **argv)
{
    int directoryCount = 0;
    int flag_a = 0;
    int flag_R = 0;
    char *directoriesToBeListed[100];
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "-aR") == 0 || strcmp(argv[i], "-Ra") == 0)
            {
                flag_a = 1;
            }
            if (strcmp(argv[i], "-R") == 0 || strcmp(argv[i], "-Ra") == 0 || strcmp(argv[i], "-aR") == 0)
            {
                flag_R = 1;
            }
            else
            {
                directoriesToBeListed[directoryCount] = argv[i];
                directoryCount++;
                if (directoryCount == 100)
                {
                    printf("Too many directories to list. Please list no more than 100 directories.\n");
                }
            }
        }
    }
    char *currentDirectory = getcwd(NULL, 0);
    char *originalDirectory = getcwd(NULL, 0);
    if (directoryCount == 0){
        printDirectoryFiles(flag_a, flag_R, currentDirectory, originalDirectory);
    }
    else
    {
        for (int i = 0; i < directoryCount; i++)
        {
            strcat(currentDirectory, "/");
            strcat(currentDirectory, directoriesToBeListed[i]);
            printf("%s:\n", directoriesToBeListed[i]);
            printDirectoryFiles(flag_a, flag_R, currentDirectory, originalDirectory);
            currentDirectory = getcwd(NULL, 0);
        }
    }
    return 0;
}
