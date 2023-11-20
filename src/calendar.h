#include <fstream>
#include <string>
#ifndef CALENDARGEN_CALENDAR_H
#define CALENDARGEN_CALENDAR_H

/// @brief Simple HTML calendar generator
class Calendar
{
private:
    /// @brief File Name
    std::string fileName;
    /// @brief Year to be generated
    int year;
    /// @brief Number of years to be generated
    int numberOfYears;
    /// @brief Current day of the week
    int dayOfWeek;
    /// @brief Current week number
    int week;
    /// @brief Current month
    int month;
    /// @brief Write page style
    /// @param f File descriptor
    void writeStyle(std::ofstream &f);
    /// @brief Write month table style
    /// @param f File descriptor
    void writeMonthStyle(std::ofstream &f);
    /// @brief Write month info
    /// @param m Month
    /// @param f File descriptor
    void writeMonthInfo(int m, std::ofstream &f);
    /// @brief Writes week info
    /// @param f File descriptor
    void writeWeekInfo(std::ofstream &f);
    /// @brief  Generates the HTML code for a month
    /// @param nDays Number of days of the month
    /// @param month Month to be generated
    /// @param f File descriptor
    void generateMonthHTML(int nDays, int month, std::ofstream &f);
    /// @brief Generates the HTML code for a year
    /// @param f File descriptor
    void generateYearHTML(std::ofstream &f);

public:
    /// @brief Constructor for calendar
    /// @param y Year given by the user
    /// @param fName File Name given by the user
    Calendar(int y, std::string fName);
    /// @brief Tests if it is a leap year
    /// @param y Year to be tested
    /// @return true if it is a leap false otherwise
    bool isLeapYear(int y);
    /// @brief Calculates the day of the week of a date
    /// @param d Day of the month
    /// @param m Month
    /// @param y Year
    /// @return What is the week day 0-Monday .. 6-Sunday
    int calcDayOfWeek(int d, int m, int y);
    /// @brief Generates the HTML page with the calendar
    void generateCalendarHTML();
};

#endif // CALENDARGEN_CALENDAR_H