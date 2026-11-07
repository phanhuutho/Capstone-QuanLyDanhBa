#include "ContactManager.h"
#include <iostream>

using namespace std;

int main()
{
	ContactManager manager("danh_ba.csv");
	manager.LoadFromFile();
	manager.DisplayListContact();
	return 0;
}