#pragma once
#include <array>

static const std::array<int, 13> DaysToMonth365 = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
static const std::array<int, 13> DaysToMonth366 = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

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
private:
	bool IsLeapYear(unsigned year);
	unsigned DateToTicks(unsigned day, Month month, unsigned year);

	bool m_isValid;
	unsigned m_timestamp;
};
