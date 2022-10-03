// system program to read date form os and print it
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // Format: Mon Oct  3 11:28:53 IST 2022
    char *day;
    switch (tm.tm_wday)
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
    char *month;
    switch (tm.tm_mon)
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
    printf("%s %s %2d %02d:%02d:%02d %s %d\n", day, month, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_zone, tm.tm_year + 1900);
    return 0;
}