#include "CDate.h"

CDate::CDate(unsigned day, Month month, unsigned year)
{
    m_days = DateToTimestamp(day, month, year);
}

CDate::CDate(unsigned timestamp)
{
    m_days = timestamp;
}

unsigned CDate::GetDay() const
{
    unsigned day, year;
    Month month;
    TimestampToDate(m_days, day, month, year);
    return day;
}

Month CDate::GetMonth() const
{
    unsigned day, year;
    Month month;
    TimestampToDate(m_days, day, month, year);
    return month;
}

unsigned CDate::GetYear() const
{
    unsigned day, year;
    Month month;
    TimestampToDate(m_days, day, month, year);
    return year;
}

WeekDay CDate::GetWeekDay() const
{
    if (!IsValid())
    {
        return WeekDay::SUNDAY; // Недопустимая дата
    }

    int weekDay = WEEKDAY_MIN_DAY + m_days % QUANTITY_WEEKDAY;
    return static_cast<WeekDay>(weekDay % QUANTITY_WEEKDAY);
}

bool CDate::IsValid() const
{
    unsigned day, year;
    Month month;
    TimestampToDate(m_days, day, month, year);
    return CheckValidity(day, month, year);
}

CDate& CDate::operator++()
{
    if (IsValid())
    {
        ++m_days;
    }
    return *this;
}

CDate CDate::operator++(int)
{
    CDate temp = *this;
    ++(*this);
    return temp;
}

CDate& CDate::operator--()
{
    if (IsValid())
    {
        --m_days;
    }
    return *this;
}

CDate CDate::operator--(int)
{
    CDate temp = *this;
    --(*this);
    return temp;
}

CDate CDate::operator+(unsigned days) const
{
    CDate result(*this);
    if (IsValid())
    {
        result.m_days += days;
    }
    return result;
}

CDate CDate::operator-(unsigned days) const
{
    CDate result(*this);
    if (IsValid())
    {
        result.m_days -= days;
    }
    return result;
}

unsigned CDate::operator-(const CDate& other) const
{
    if (!IsValid() || !other.IsValid())
    {
        return 0;
    }

    return m_days - other.m_days;
}

CDate& CDate::operator+=(unsigned days)
{
    if (IsValid())
    {
        m_days += days;
    }
    return *this;
}

CDate& CDate::operator-=(unsigned days)
{
    if (IsValid())
    {
        m_days -= days;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const CDate& date)
{
    if (date.IsValid())
    {
        os << date.GetDay() << '.' << static_cast<int>(date.GetMonth()) << '.' << date.GetYear();
    }
    else
    {
        os << "INVALID";
    }
    return os;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
    unsigned day, year;
    int monthValue;
    char dot1, dot2;
    is >> day >> dot1 >> monthValue >> dot2 >> year;

    if (!is || dot1 != '.' || dot2 != '.')
    {
        date = CDate(0);  // Устанавливаем недопустимую дату
        return is;
    }

    Month month;
    switch (monthValue)
    {
    case 1:  month = Month::JANUARY;    break;
    case 2:  month = Month::FEBRUARY;   break;
    case 3:  month = Month::MARCH;      break;
    case 4:  month = Month::APRIL;      break;
    case 5:  month = Month::MAY;        break;
    case 6:  month = Month::JUNE;       break;
    case 7:  month = Month::JULY;       break;
    case 8:  month = Month::AUGUST;     break;
    case 9:  month = Month::SEPTEMBER;  break;
    case 10: month = Month::OCTOBER;    break;
    case 11: month = Month::NOVEMBER;   break;
    case 12: month = Month::DECEMBER;   break;
    default:
        date = CDate(0);  // Устанавливаем недопустимую дату
        return is;
    }

    if (!date.CheckValidity(day, month, year))
    {
        date = CDate(0);  // Устанавливаем недопустимую дату
    }
    else
    {
        date = CDate(day, month, year);
    }

    return is;
}

bool CDate::operator==(const CDate& other) const
{
    return m_days == other.m_days;
}

std::strong_ordering CDate::operator<=>(const CDate& other) const
{
    return m_days <=> other.m_days;
}

unsigned CDate::GetDaysInMonth(Month month, unsigned year)
{
    switch (month)
    {
    case Month::JANUARY:
    case Month::MARCH:
    case Month::MAY:
    case Month::JULY:
    case Month::AUGUST:
    case Month::OCTOBER:
    case Month::DECEMBER:
        return 31;
    case Month::APRIL:
    case Month::JUNE:
    case Month::SEPTEMBER:
    case Month::NOVEMBER:
        return 30;
    case Month::FEBRUARY:
        return IsLeapYear(year) ? 29 : 28;
    default:
        return 0;  // Недопустимый месяц
    }
}

bool CDate::IsLeapYear(unsigned year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool CDate::CheckValidity(unsigned day, Month month, unsigned year) const
{
    if (year < MIN_YEAR || year > MAX_YEAR)
    {
        return false;
    }

    if (static_cast<int>(month) < MIN_MONTH || static_cast<int>(month) > MAX_MONTH)
    {
        return false;
    }

    unsigned daysInMonth = GetDaysInMonth(month, year);
    if (day < MIN_DAY || day > daysInMonth)
    {
        return false;
    }

    return true;
}

unsigned CDate::DateToTimestamp(unsigned day, Month month, unsigned year) const
{
    unsigned timestamp = 0;

    for (unsigned y = MIN_YEAR; y < year; ++y)
    {
        timestamp += IsLeapYear(y) ? QUANTITY_DAYS_LEAP_YEAR : QUANTITY_DAYS_YEAR;
    }

    for (int m = MIN_MONTH; m < static_cast<int>(month); ++m)
    {
        timestamp += GetDaysInMonth(static_cast<Month>(m), year);
    }

    timestamp += day - 1;

    return timestamp;
}

void CDate::TimestampToDate(unsigned timestamp, unsigned& day, Month& month, unsigned& year) const
{
    unsigned y = MIN_YEAR;
    unsigned days = 1 + timestamp;

    int quantityDays = IsLeapYear(y) ? QUANTITY_DAYS_LEAP_YEAR : QUANTITY_DAYS_YEAR;
    while (days > quantityDays)
    {
        days -= quantityDays;
        ++y;
        quantityDays = IsLeapYear(y) ? QUANTITY_DAYS_LEAP_YEAR : QUANTITY_DAYS_YEAR;
    }

    unsigned m = MIN_MONTH;
    while (days > GetDaysInMonth(static_cast<Month>(m), y))
    {
        days -= GetDaysInMonth(static_cast<Month>(m), y);
        ++m;
    }

    day = days;
    month = static_cast<Month>(m);
    year = y;
}