#include "ContactManager.h"
#include <iostream>

using namespace std;

int main()
{
	ContactManager manager("danh_ba.csv");
	manager.InitContactManage();
	manager.LoadFromFile();
	vector<vector<Contact*>> lstASC = manager.GetListContacts();
	DisplayListContact(lstASC);
	return 0;
}