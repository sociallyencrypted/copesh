#include <stdio.h>

#include <stdlib.h>

#include <string.h>

int main(int argc, char **argv)
{
    int flag_n = 0;
    int flag_s = 0;
    if (argc > 2)
    {
        if (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "-ns") == 0 || strcmp(argv[1], "-sn") == 0)
        {
            flag_n = 1;
        }
        if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "-sn") == 0 || strcmp(argv[1], "-ns") == 0)
        {
            flag_s = 1;
        }
    }
    FILE *file = fopen(argv[argc - 1], "r");
    if (file == NULL)
    {
        printf("Error opening file %s", argv[1]);
        exit(1);
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int lineCount = 1;
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
    return 0;
}