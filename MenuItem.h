#pragma once
#include <string>

using namespace std;

class MenuItem {
protected:
	string Title;
public:
	MenuItem(string _title) : Title(_title)
	{

	}
	virtual ~MenuItem()
	{

	}

	string getTitle() const { return Title; }

	virtual void DisplayMenu() const = 0;
};

