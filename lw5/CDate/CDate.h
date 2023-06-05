#pragma once
#include <array>

static const std::array<int, 13> DaysToMonth365 = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
static const std::array<int, 13> DaysToMonth366 = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

// ћес€ц
enum class Month
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL,
	MAY, JUNE, JULY, AUGUST, SEPTEMBER,
	OCTOBER, NOVEMBER, DECEMBER
};

// ƒень недели
enum class WeekDay
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY
};

// ƒата в формате день-мес€ц-год. √од в диапазоне от 1970 до 9999
class CDate
{
public:
	// инициализируем дату заданными днем, мес€цем и годом.
	// примечание: год >= 1970
	CDate(unsigned day, Month month, unsigned year);

	// инициализируем дату количеством дней, прошедших после 1 €нвар€ 1970 года
	// например, 2 = 3 €нвар€ 1970, 32 = 2 феврал€ 1970 года и т.д.
	CDate(unsigned timestamp = 0);

	// возвращает день мес€ца (от 1 до 31)
	unsigned GetDay() const;

	// возвращает мес€ц
	Month GetMonth() const;

	// возвращает год
	unsigned GetYear() const;

	// возвращает день недели
	WeekDay GetWeekDay() const;

	// возвращает информацию о корректности хранимой даты.
	// Ќапример, после вызова CDate date(99, static_cast<Month>(99), 10983);
	// или после:
	//	CDate date(1, January, 1970); --date;
	// метод date.IsValid() должен вернуть false;
	bool IsValid() const;
private:
	bool IsLeapYear(unsigned year);
	unsigned DateToTicks(unsigned day, Month month, unsigned year);

	bool m_isValid;
	unsigned m_timestamp;
};
