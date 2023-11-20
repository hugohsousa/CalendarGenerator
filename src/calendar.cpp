#include <iostream>
#include <cmath>
#include "calendar.h"
#include <fstream>
#include <string>

bool Calendar::isLeapYear(int y)
{
    // Check is y is a leap year
    return (y % 4 == 0) ? ((y % 100 == 0 && y % 400 != 0) ? false : true) : false;
}

int Calendar::calcDayOfWeek(int d, int m, int y)
{
    // m = Month (1-March .. 12- February)
    // If January or February y = y-1
    if (m == 11 || m == 12)
        y--;
    // Last two digits of the year
    int D = abs(y) % 100;
    // First two digits of the year
    int C = y / 100;

    // Calculate weekday
    int w = abs(d + floor((13 * m - 1) / 5) + D + floor(D / 4) + floor(C / 4) - 2 * C);
    int to_return;
    if (w > 0 && w < 7)
        to_return = 7 - w;
    else
        to_return = w % 7;

    // Adjust to 0-Monday .. 6-Sunday
    return (to_return == 0) ? 6 : to_return - 1;
}

Calendar::Calendar(int y, std::string fName)
{
    // Test if input is valid
    if (y < 1582)
    {
        std::cerr << "Please provide a valid year!\n";
        exit(1);
    }
    if (fName == "")
    {
        std::cerr << "Please provide a valid file name!\n";
    }
    // Output file name
    fileName = fName + ".HTML";
    // Generate config for the calendar
    // 1582 - Starts in October (Prior year not supported)
    if (y == 1582 || y == 1583)
    {
        month = 9;
        dayOfWeek = 4;
        week = 41;
        year = 1582;
        if (y == 1582)
            numberOfYears = 2;
        else
            numberOfYears = 3;
    }
    else
    {
        month = 0;
        dayOfWeek = calcDayOfWeek(1, 11, y - 1);
        if (dayOfWeek != 0)
            week = 52;
        else
            week = 1;
        year = y - 1;
        numberOfYears = 3;
    }
}

void Calendar::writeStyle(std::ofstream &f)
{
    // Write style for the HTML page
    f << "<!DOCTYPE html><html><head>";
    f << "<title>Calendar " << year + numberOfYears - 2 << "</title>";
    f << "<style>* {box-sizing: border-box;}";
    f << ".row {margin-left:-5px;margin-right:-5px;}";
    f << ".column {float:left;padding:5px;}";
    f << ".row::after{content:\"\";clear:both;display:table;}";
    f << ".grey{background-color: rgba(231, 231, 230, 255);}";
    f << ".yellow{background-color: rgba(255, 254, 205, 255);}";
    f << ".orange{background-color: rgba(254, 204, 152, 255);}";
    f << ".white{background-color: rgba(255, 255, 255, 255);}";
    f << "table{font-family:arial,sans-serif;border-collapse:collapse;}";
    f << "td,th{border:1px solid #000000;text-align:center;padding:6px;}";
    f << "</style></head><body>";
}

void Calendar::writeMonthStyle(std::ofstream &f)
{
    // write style for the month table
    f << "<table><colgroup>";
    f << "<col class=\"grey\"/>";
    f << "<col class=\"white\" span=\"5\"/>";
    f << "<col class=\"yellow\"/>";
    f << "<col class=\"orange\"/>";
    f << "</colgroup><thead>";
}

void Calendar::writeMonthInfo(int m, std::ofstream &f)
{
    // Write month column with name and proper style
    std::string m_info = "<tr><th style=\"background-color:#CDFECC\" colspan=\"8\">";
    switch (m)
    {
    case 0:
        m_info += "January</th>";
        break;
    case 1:
        m_info += "February</th>";
        break;
    case 2:
        m_info += "March</th>";
        break;
    case 3:
        m_info += "April</th>";
        break;
    case 4:
        m_info += "May</th>";
        break;
    case 5:
        m_info += "June</th>";
        break;
    case 6:
        m_info += "July</th>";
        break;
    case 7:
        m_info += "August</th>";
        break;
    case 8:
        m_info += "September</th>";
        break;
    case 9:
        m_info += "October</th>";
        break;
    case 10:
        m_info += "November</th>";
        break;
    case 11:
        m_info += "December</th>";
        break;
    default:
        std::cerr << "Not a valid month!";
        exit(1);
    }
    f << m_info << "</tr>";
}

void Calendar::writeWeekInfo(std::ofstream &f)
{
    // Add wk and week days columns
    f << "<tr>";
    f << "<th>Wk</th>";
    f << "<th style=\"background-color:#E7E7E6\">Mo</th>";
    f << "<th style=\"background-color:#E7E7E6\">Tu</th>";
    f << "<th style=\"background-color:#E7E7E6\">We</th>";
    f << "<th style=\"background-color:#E7E7E6\">Th</th>";
    f << "<th style=\"background-color:#E7E7E6\">Fr</th>";
    f << "<th>Sa</th>";
    f << "<th>Su</th>";
    f << "</tr></thead><tbody>";
}

void Calendar::generateMonthHTML(int nDays, int month, std::ofstream &f)
{
    // Write style for the month
    writeMonthStyle(f);
    writeMonthInfo(month, f);
    writeWeekInfo(f);

    // Variables to help generate the month
    int d = 1;
    if (year == 1582 && month == 9)
        d = 15;
    int temp = 0;

    // Generate blank spaces to fill first week
    while (temp < dayOfWeek)
    {
        // If monday generate new line
        if (temp == 0)
            f << "<tr><td>" << week << "</td>";

        // Add blank day
        f << "<td></td>";
        temp++;
    }

    // Generate days
    while (d <= nDays)
    {
        // If monday generate new line
        if (dayOfWeek == 0)
            f << "<tr><td>" << week << "</td>";

        // Add day
        f << "<td>" << d++ << "</td>";

        // If sunday change week
        if (dayOfWeek == 6)
        {
            f << "</tr>";
            dayOfWeek = 0;
            if (week == 52)
                week = 0;
            week++;
        }
        else
            dayOfWeek++;
    }

    temp = dayOfWeek;
    // Generate blank spaces to fill last week
    while (temp > 0 && temp < 7)
    {
        f << "<td></td>";
        if (temp == 6)
            f << "</tr>";
        temp++;
    }

    // Close tags
    f << "</tbody></table>";
}

void Calendar::generateYearHTML(std::ofstream &f)
{
    // Write year
    f << "<h1 style=text-align:center;>Calendar " << year << "</h1>";
    // Array with number of days per month
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year))
        days[1] = 29;

    f << "<div class=\"row\">";
    // Generate months
    while (month < 12)
    {
        if (month == 6)
        {
            f << "</div><div class=\"row\">";
        }
        f << "<div class=\"column\">";
        generateMonthHTML(days[month], month, f);
        f << "</div>";
        month++;
    }
    // Close tags
    f << "</div>";
}

void Calendar::generateCalendarHTML()
{
    // Create/Open file to write
    std::ofstream f(fileName);

    // Write tags and style
    writeStyle(f);

    // Generate years
    for (int i = 0; i < numberOfYears; i++)
    {
        generateYearHTML(f);
        year++;
        month = 0;
    }

    // Close tags
    f << "</body></html>";
}