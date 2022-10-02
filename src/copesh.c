#include <stdio.h>
#include <string.h>

// global variables
char *user;

char *login()
{
    while (1)
    {
        char username[100];
        printf("Username: ");
        if (fgets(username, 100, stdin) == NULL)
        {
            printf("Error: Username too long");
        }
        else
        {
            strtok(username, "\n");
            return username;
        }
    }
}

int main()
{
    printf("copesh v1.0.0\n");
    user = login();
    while (1)
    {
        printf("copesh:~ %s$ ", user);
        char input[100];
        scanf("%s", input);
        if (strcmp(input, "exit") == 0)
        {
            printf("\n");
            return 0;
        }
        else
        {
            printf("In development\n");
        }
    }
}
