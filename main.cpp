#include "ContactManager.h"
#include "SortContact.h"
#include "DisplayContactManager.h"
#include <iostream>

using namespace std;

int main()
{
	ContactManager manager("danh_ba.csv");
	manager.LoadFromFile();

	vector<vector<Contact*>> lstDESC = manager.GetListContacts();
	SortContact_DESC(lstDESC);
	DisplayListContact(lstDESC);

	vector<vector<Contact*>> lstASC = manager.GetListContacts();
	DisplayListContact(lstASC);

	bool isMerged = false;
	manager.MergeFromFile("merge.csv", isMerged, true);
	lstASC = manager.GetListContacts();
	DisplayListContact(lstASC);

	lstDESC.clear();
	lstASC.clear();

	return 0;
}