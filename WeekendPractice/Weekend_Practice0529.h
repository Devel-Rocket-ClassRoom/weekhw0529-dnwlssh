#pragma once

void Homework01_Run();

/// <summary>
/// 1년부터 입력연도 사이의 일수를 구하는 함수
/// </summary>
//// <param name="year">입력 연도</param>
// /// <returns>1년부터 입력년까지의 총 일수</returns>
int CheckYearDate(int year);
enum MonthName
{
	Jan = 1,
	Feb,
	Mar,
	Apr,
	May,
	Jun,
	Jul,
	Aug,
	Sep,
	Oct,
	Nov,
	Dec
};

bool IsLeapYear(int year);

/// <summary>
/// 입력 연도의 1월 1일부터 입력 월일까지의 일수를 구하는 함수
/// </summary>
/// <param name="month">입력한 월</param>
/// <param name="date">입력한 일</param>
/// <returns>1월 1일 부터 입력한 월일까지의 일수 총합</returns>
int CheckExtraDate(int year, int month, int date);

void CheckWeekDay(int TotalDate);