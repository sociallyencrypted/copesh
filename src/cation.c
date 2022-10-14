#include <stdio.h>

#include <stdlib.h>

#include <string.h>

int main(int argc, char **argv)
{
    char* filesToBeCatIoned[100];
    int filecount = 0;
    int flag_n = 0;
    int flag_s = 0;
    if (argc == 1){
        printf("Usage: cation [-n] [-s] [args]\n");
        exit(1);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "--help")==0){
                printf("cat: cat [-n] [-s] [args]\n");
                printf("Catenate files and print on the standard output.\n");
                printf("Options:\n");
                printf("  -n\t\tNumber all output lines.\n");
                printf("  -s\t\tSuppress repeated empty output lines.\n");
                exit(0);
            }
            if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-ns") == 0 || strcmp(argv[i], "-sn") == 0)
            {
                flag_n = 1;
            }
            if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "-sn") == 0 || strcmp(argv[i], "-ns") == 0)
            {
                flag_s = 1;
            }
            else
            {
                filesToBeCatIoned[filecount] = argv[i];
                filecount++;
                if (filecount==100){
                    printf("cat: too many arguments\n");
                    exit(1);
                }
            }
        }
    }
    int lineCount = 1;
    for (int i=0; i<filecount; i++){
        FILE *file = fopen(filesToBeCatIoned[i], "r");
        if (file == NULL)
        {
            break;
        }
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        while ((read = getline(&line, &len, file)) != -1)
        {
            if (flag_s == 1)
            {
                if (strcmp(line, "\n") == 0)
                {
                    continue;
                }
            }
            if (flag_n == 1)
            {
                printf("%d ", lineCount);
            }
            printf("%s", line);
            lineCount++;
        }
        fclose(file);
        if (line)
        {
            free(line);
        }
        printf("\n");
        }
    return 0;
}