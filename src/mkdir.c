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
    int directoryCount = 0;
    int flag_m = 0;
    int perms = 0777;
    int flag_p = 0;
    char* directoriesToBeCreated[100];
    if (argc==1){
        printf("Usage: mkdir [-m mode] [-p] [args]\n");
        exit(1);
    }
    if (argc==2){
        if (strcmp(argv[1],"-p")==0 || strcmp(argv[1],"-m")==0 || strcmp(argv[1],"-mp")==0 || strcmp(argv[1],"-pm")==0){
            printf("Usage: mkdir [-m mode] [-p] [args]\n");
            exit(1);
        }
        else{
            if (mkdir(argv[1],perms)==-1){
                perror("mkdir");
                exit(1);
            }
            exit(0);
        }
    }
    if (argc > 2)
    {
        for (int i = 1; i < argc; i++)
        {
            if (strncmp(argv[i], "-m", 2) == 0 || strncmp(argv[i], "-mp", 3) == 0 || strncmp(argv[i], "-pm", 3) == 0 || strncmp(argv[i], "--mode", 6) == 0)
            {
                flag_m = 1;
                //--mode=perms or -mp=perms or -pm=perms
                char * sperms = strchr(argv[i], '=') + 1;
                perms = strtol(sperms, NULL, 8);
                //check if perms is a valid octal number
                if (perms > 0777 || perms < 00)
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
                if (directoryCount==100){
                    printf("mkdir: too many arguments\n");
                    exit(1);
                }
            }
        }
    }
    // make a directory given in argv
    char *currentDirectory = getcwd(NULL, 0);
    for (int i=0; i<directoryCount;i++){
        if (directoriesToBeCreated[i]==NULL){
            break;
        }
        char *dirName = directoriesToBeCreated[i];
        if (flag_p == 1)
        {
            //create all directories in the path
            char* path = malloc(strlen(currentDirectory) + strlen(dirName) + 2);
            strcpy(path, currentDirectory);
            strcat(path, "/");
            char *toBeAdded = strtok(dirName, "/");
            while (toBeAdded != NULL)
            {
                strcat(path, toBeAdded);
                if (mkdir(path, perms) == -1)
                {
                    printf("mkdir: cannot create directory ‘%s’: File exists\n", path);
                    exit(1);
                }
                strcat(path, "/");
                toBeAdded = strtok(NULL, "/");
            }
        }
        else
        {
            printf("%s\n", dirName);
            printf("%d\n", perms);
            if (mkdir(dirName, perms) == -1)
            {
                perror("mkdir");
                exit(1);
            }
        }
    }
}
