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

	vector<RelationContact*> lstRelation = manager.GetListRelations();
	DisplayListRelation(lstRelation);

	manager.DeleteRelation(3);
	lstRelation = manager.GetListRelations();
	DisplayListRelation(lstRelation);

	int type;
	manager.CreditRelation("Relation Add", type);
	lstRelation = manager.GetListRelations();
	DisplayListRelation(lstRelation);

	lstDESC.clear();
	lstASC.clear();
	lstRelation.clear();

	return 0;
}