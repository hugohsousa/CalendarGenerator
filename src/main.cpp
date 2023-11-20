#include <iostream>
#include <cstring>
#include "calendar.h"

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        std::cerr << "Please provide a valid command!\n./calendarGen help\n";
        return -1;
    }
    if (!std::strcmp(argv[1], "help"))
    {
        std::cout << "Earliest supported year is 1582\nbuild/calenderGen year outputFileName\n";
        return 0;
    }

    // Test if the received parameter is a integer
    for (int i = 0; argv[1][i]; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            std::cerr << "Please provide a valid command!\n./calendarGen help\n";
            return -1;
        }
    }

    // Test if the year is valid
    int year = atoi(argv[1]);

    Calendar c = Calendar(year, argv[2]);
    c.generateCalendarHTML();

    return 0;
}