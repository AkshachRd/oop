#pragma once
#include <istream>
#include <ostream>

const int MIN_DAY = 1;
const int MIN_MONTH = 1;
const int MAX_MONTH = 12;
const int MIN_YEAR = 1970;
const int MAX_YEAR = 9999;
const int QUANTITY_DAYS_LEAP_YEAR = 366;
const int QUANTITY_DAYS_YEAR = 365;
const int QUANTITY_MONTH = 12;
const int WEEKDAY_MIN_DAY = 4;
const int QUANTITY_WEEKDAY = 7;

// Месяц
enum class Month
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL,
	MAY, JUNE, JULY, AUGUST, SEPTEMBER,
	OCTOBER, NOVEMBER, DECEMBER
};

// День недели
enum class WeekDay
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY
};

// Дата в формате день-месяц-год. Год в диапазоне от 1970 до 9999
class CDate
{
public:
	// инициализируем дату заданными днем, месяцем и годом.
	// примечание: год >= 1970
	CDate(unsigned day, Month month, unsigned year);

	// инициализируем дату количеством дней, прошедших после 1 января 1970 года
	// например, 2 = 3 января 1970, 32 = 2 февраля 1970 года и т.д.
	CDate(unsigned timestamp = 0);

	// возвращает день месяца (от 1 до 31)
	unsigned GetDay() const;

	// возвращает месяц
	Month GetMonth() const;

	// возвращает год
	unsigned GetYear() const;

	// возвращает день недели
	WeekDay GetWeekDay() const;

	// возвращает информацию о корректности хранимой даты.
	// Например, после вызова CDate date(99, static_cast<Month>(99), 10983);
	// или после:
	//	CDate date(1, January, 1970); --date;
	// метод date.IsValid() должен вернуть false;
	bool IsValid() const;

	// Переводит дату на следующий день
	CDate& operator++();     // префиксная форма
	CDate operator++(int);   // постфиксная форма

	// Переводит дату на предыдущий день
	CDate& operator--();     // префиксная форма
	CDate operator--(int);   // постфиксная форма

	// Прибавляет к дате заданное целое количество дней
	CDate operator+(unsigned days) const;

	// Вычитает из даты заданное количество дней или находит разность двух дат в днях
	CDate operator-(unsigned days) const;
	unsigned operator-(const CDate& other) const;

	// Прибавляет к дате заданное целое количество дней
	CDate& operator+=(unsigned days);

	// Вычитает из даты заданное количество дней
	CDate& operator-=(unsigned days);

	// Оператор вывода даты в поток вывода в формате ДД.ММ.ГГГГ
	friend std::ostream& operator<<(std::ostream& os, const CDate& date);

	// Оператор ввода времени из потока ввода в формате ДД.ММ.ГГГГ
	friend std::istream& operator>>(std::istream& is, CDate& date);

	// Проверка двух дат на равенство
	bool operator==(const CDate& other) const;

	// Проверка двух дат на строгое и несртогое неравенства
	std::strong_ordering operator<=>(const CDate& other) const;
private:
	int m_days;

	// Возвращает количество дней в заданном месяце и году
	static unsigned GetDaysInMonth(Month month, unsigned year);

	// Проверяет, является ли год високосным
	static bool IsLeapYear(unsigned year);

	// Проверяет, является ли дата допустимой
	bool CheckValidity(unsigned day, Month month, unsigned year) const;

	// Преобразует дату в количество дней после 1 января 1970 года
	unsigned DateToTimestamp(unsigned day, Month month, unsigned year) const;

	// Преобразует количество дней после 1 января 1970 года в дату
	void TimestampToDate(unsigned timestamp, unsigned& day, Month& month, unsigned& year) const;
};
