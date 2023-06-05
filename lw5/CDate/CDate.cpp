#include "CDate.h"

CDate::CDate(unsigned day, Month month, unsigned year)
{

}

CDate::CDate(unsigned timestamp = 0)
{
	this->m_timestamp = timestamp;
}

bool CDate::IsValid() const
{
	return m_isValid;
}

bool CDate::IsLeapYear(unsigned year)
{
	if ((year < 1) || (year > 9999))
	{
		this->m_isValid = false;
		return false;
	}

	if ((year % 4) != 0)
	{
		return false;
	}

	if ((year % 100) == 0)
	{
		return ((year % 400) == 0);
	}

	return true;
}

unsigned CDate::DateToTicks(unsigned day, Month month, unsigned year)
{
	int monthNum = static_cast<int>(month);

    if (((year >= 1) && (year <= 9999)) && ((monthNum >= 1) && (monthNum <= 12)))
    {
		auto daysToMonth = this->IsLeapYear(year) ? DaysToMonth366 : DaysToMonth365;
        if ((day >= 1) && (day <= (daysToMonth[monthNum] - daysToMonth[monthNum - 1])))
        {
			unsigned previousYear = year - 1;
			unsigned daysInPreviousYears = ((((previousYear * 365) + (previousYear / 4)) - (previousYear / 100)) + (previousYear / 400));

			unsigned totalDays = ((daysInPreviousYears + daysToMonth[monthNum - 1]) + day) - 1;
            return (totalDays * 0xc92a69c000L); // magic MS number
        }
    }

	this->m_isValid = false;
}