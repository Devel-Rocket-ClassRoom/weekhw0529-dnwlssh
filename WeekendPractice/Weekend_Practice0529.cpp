#include <iostream>
#include <stdio.h>
#include <string>
#include "Weekend_Practice0529.h"

using namespace std;

void Homework01_Run()
{
	int Year = 0, Month = 0, Date = 0;
	printf("연도 입력 : ");
	cin >> Year >> Month >> Date;

	int YearVal = CheckYearDate(Year);

	int MonthDateVal = CheckExtraDate(Year, Month, Date);
	int TotlaDateVal = YearVal + MonthDateVal;

	CheckWeekDay(TotlaDateVal);
}

int CheckYearDate(int year)
{
	int LeapYearCount = 0;
	for (int i = 1; i < year - 1; i++)
	{
		if (IsLeapYear(i))
		{
			LeapYearCount++;	// 1년부터 year년까지의 윤년 횟수
		}
	}
	int Passedyears = year - 1;
	int AverageYearDate = (Passedyears - LeapYearCount) * 365;
	int LeapYearDate = (LeapYearCount * 366);
	int TotalYearDate = AverageYearDate + LeapYearDate;
	return TotalYearDate;
}

bool IsLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int CheckExtraDate(int year, int month, int date)
{
	int TotalmonthDate = 0;
	for (int i = 1; i < month; i++)
	{
		switch (i) {
		case Jan:
		case Mar:
		case May:
		case Jul:
		case Aug:
		case Oct:
		case Dec:
			TotalmonthDate += 31;
			break;
		case Feb:
			TotalmonthDate += IsLeapYear(year) ? 29 : 28;
			break;
		default:
			TotalmonthDate += 30;
			break;
		}
	}
	int MonthAndDate = TotalmonthDate + date;
	return MonthAndDate;
}

void CheckWeekDay(int TotalDate)
{
	int WeekDayVal = TotalDate % 7;

	switch (WeekDayVal)
	{
	case 0:
		printf("일요일\n");
		break;
	case 1:
		printf("월요일\n");
		break;
	case 2:
		printf("화요일\n");
		break;
	case 3:
		printf("수요일\n");
		break;
	case 4:
		printf("목요일\n");
		break;
	case 5:
		printf("금요일\n");
		break;
	case 6:
		printf("토요일\n");
		break;
	default:
		break;

	}
}

