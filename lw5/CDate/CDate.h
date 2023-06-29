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

// �����
enum class Month
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL,
	MAY, JUNE, JULY, AUGUST, SEPTEMBER,
	OCTOBER, NOVEMBER, DECEMBER
};

// ���� ������
enum class WeekDay
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY
};

// ���� � ������� ����-�����-���. ��� � ��������� �� 1970 �� 9999
class CDate
{
public:
	// �������������� ���� ��������� ����, ������� � �����.
	// ����������: ��� >= 1970
	CDate(unsigned day, Month month, unsigned year);

	// �������������� ���� ����������� ����, ��������� ����� 1 ������ 1970 ����
	// ��������, 2 = 3 ������ 1970, 32 = 2 ������� 1970 ���� � �.�.
	CDate(unsigned timestamp = 0);

	// ���������� ���� ������ (�� 1 �� 31)
	unsigned GetDay() const;

	// ���������� �����
	Month GetMonth() const;

	// ���������� ���
	unsigned GetYear() const;

	// ���������� ���� ������
	WeekDay GetWeekDay() const;

	// ���������� ���������� � ������������ �������� ����.
	// ��������, ����� ������ CDate date(99, static_cast<Month>(99), 10983);
	// ��� �����:
	//	CDate date(1, January, 1970); --date;
	// ����� date.IsValid() ������ ������� false;
	bool IsValid() const;

	// ��������� ���� �� ��������� ����
	CDate& operator++();     // ���������� �����
	CDate operator++(int);   // ����������� �����

	// ��������� ���� �� ���������� ����
	CDate& operator--();     // ���������� �����
	CDate operator--(int);   // ����������� �����

	// ���������� � ���� �������� ����� ���������� ����
	CDate operator+(unsigned days) const;

	// �������� �� ���� �������� ���������� ���� ��� ������� �������� ���� ��� � ����
	CDate operator-(unsigned days) const;
	unsigned operator-(const CDate& other) const;

	// ���������� � ���� �������� ����� ���������� ����
	CDate& operator+=(unsigned days);

	// �������� �� ���� �������� ���������� ����
	CDate& operator-=(unsigned days);

	// �������� ������ ���� � ����� ������ � ������� ��.��.����
	friend std::ostream& operator<<(std::ostream& os, const CDate& date);

	// �������� ����� ������� �� ������ ����� � ������� ��.��.����
	friend std::istream& operator>>(std::istream& is, CDate& date);

	// �������� ���� ��� �� ���������
	bool operator==(const CDate& other) const;

	// �������� ���� ��� �� ������� � ��������� �����������
	std::strong_ordering operator<=>(const CDate& other) const;
private:
	int m_days;

	// ���������� ���������� ���� � �������� ������ � ����
	static unsigned GetDaysInMonth(Month month, unsigned year);

	// ���������, �������� �� ��� ����������
	static bool IsLeapYear(unsigned year);

	// ���������, �������� �� ���� ����������
	bool CheckValidity(unsigned day, Month month, unsigned year) const;

	// ����������� ���� � ���������� ���� ����� 1 ������ 1970 ����
	unsigned DateToTimestamp(unsigned day, Month month, unsigned year) const;

	// ����������� ���������� ���� ����� 1 ������ 1970 ���� � ����
	void TimestampToDate(unsigned timestamp, unsigned& day, Month& month, unsigned& year) const;
};
