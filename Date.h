#pragma once
#include <iostream>
#include <sstream>
#include <ctime>
using namespace std;

class Date
{
private:
	int Day;
	int Month;
	int Year;

	//Kiem tra nam nhuan
	bool IsLeapYear() const
	{
		return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
	}

	// Ngay cuoi cung cua thang
	int LastDayOfMonth() const
	{
		if (Month > 0 && Month <= 12 && Year > 0)
		{
			if (Month == 2) {
				if (IsLeapYear())
					return 29;
				else
					return 28;
			}
			else if (Month == 4 || Month == 6 || Month == 9 || Month == 11)
			{
				return 30;
			}
			else
			{
				return 31;
			}
		}
		else
		{
			return 0;
		}
	}

public:
	//Constructor
	Date(int _day = 0, int _month = 0, int _year = 0) : Day(_day), Month(_month), Year(_year) {};

	//destructor
	~Date() {} ;

	//Getters
	int GetDay() const { return Day; }
	int GetMonth() const { return Month; }
	int GetYear() const { return Year; }

	// Kiem tra Date hop le
	bool IsValidDate() const
	{
		if (Month < 1 || Month > 12)
			return false;
		if (Day < 1 || Day > LastDayOfMonth())
			return false;
		if (Year < 1)
			return false;
		return true;
	}

	// Xuat Date dinh dang day/month/year
	void Print() const
	{
		cout << Day << "/" << Month << "/" << Year;
	}

	string DateToString() const
	{
		return to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year);
	}

	bool IsEmpty() const {
		return (Day == 0 && Month == 0 && Year == 0);
	}

	void FromString(const string& str)
	{
		char slash;
		stringstream ss(str);

		ss >> Day >> slash >> Month >> slash >> Year;
	}

	istream& operator>>(istream& in) {
		string str;
		getline(in, str);

		char slash;
		stringstream ss(str);
		ss >> Day >> slash >> Month >> slash >> Year;

		return in;
	}

	bool operator<(const Date& d)
	{
		if (Year < d.Year)
			return true;
		else
		{
			if (Year == d.Year)
			{
				if (Month < d.Month)
					return true;
				else
				{
					if (Month == d.Month) {
						if (Day < d.Day)
							return true;
					}
				}
			}
		}
		return false;
	}

	bool operator==(const Date& d)
	{
		return Year == d.Year && Month == d.Month && Day == d.Day;
	}

	bool operator>(const Date& d)
	{
		return !(*this < d) && !(*this == d);
	}

	/*int CountDayToBirthday() const
	{
		time_t now = time(nullptr);
		tm today = *localtime(&now);

		tm birthday = {};
		birthday.tm_mday = Day;
		birthday.tm_mon = Month - 1;
		birthday.tm_year = today.tm_year;

		time_t birthTime = mktime(&birthday);

		if (difftime(birthTime, now) < 0)
		{
			birthday.tm_year++;
			birthTime = mktime(&birthday);
		}

		double seconds = difftime(birthTime, now);

		return static_cast<int>(seconds / (60 * 60 * 24));
	}*/
};