// system program to read date form os and print it
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int flag_r = 0;
    int flag_u = 0;
    int timeFromEpoch = 0;
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "-ru") == 0 || strcmp(argv[i], "-ur") == 0)
            {
                flag_r = 1;
                if (i + 1 < argc)
                {
                    timeFromEpoch = atoi(argv[i + 1]);
                }
                else
                {
                    printf("date: 'r' needs an integer argument.\n");
                    printf("Try 'date --help' for more information.\n");
                    exit(1);
                }
            }
            if (strcmp(argv[i], "-u") == 0 || strcmp(argv[i], "-ur") == 0 || strcmp(argv[i], "-ru") == 0)
            {
                flag_u = 1;
            }
        }
    }
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // Format: Mon Oct  3 11:28:53 IST 2022
    int dayConsidered = tm.tm_wday;
    int monthConsidered = tm.tm_mon;
    if (flag_r == 1)
    {
        // time from epoch
        t = timeFromEpoch;
        tm = *localtime(&t);
        dayConsidered = tm.tm_wday;
        monthConsidered = tm.tm_mon;
    }
    if (flag_u == 1)
    {
        // convert time to UTC
        tm = *gmtime(&t);
        dayConsidered = tm.tm_wday;
        monthConsidered = tm.tm_mon;
    }
    char *day;
    char *month;
    switch (dayConsidered)
    {
    case 0:
        day = "Sun";
        break;
    case 1:
        day = "Mon";
        break;
    case 2:
        day = "Tue";
        break;
    case 3:
        day = "Wed";
        break;
    case 4:
        day = "Thu";
        break;
    case 5:
        day = "Fri";
        break;
    case 6:
        day = "Sat";
        break;
    }
    switch (monthConsidered)
    {
    case 0:
        month = "Jan";
        break;
    case 1:
        month = "Feb";
        break;
    case 2:
        month = "Mar";
        break;
    case 3:
        month = "Apr";
        break;
    case 4:
        month = "May";
        break;
    case 5:
        month = "Jun";
        break;
    case 6:
        month = "Jul";
        break;
    case 7:
        month = "Aug";
        break;
    case 8:
        month = "Sep";
        break;
    case 9:
        month = "Oct";
        break;
    case 10:
        month = "Nov";
        break;
    case 11:
        month = "Dec";
        break;
    }
    if (flag_u == 1)
    {
        printf("%s %s %2d %02d:%02d:%02d UTC %d\n", day, month, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_year + 1900);
    }
    else
    {
        printf("%s %s %2d %02d:%02d:%02d %s %d\n", day, month, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_zone, tm.tm_year + 1900);
    }
    return 0;
}