#pragma once
#include <string>
#include <ostream>

using namespace std;

class RelationContact
{
private:
	int TypeRelation;
	string RelationName;
	static int Max;
public:
	RelationContact(int _type = 0, string _name = "");

	~RelationContact();

	void SetTypeRelation(int _type);
	void SetRelationName(string _name);

	int GetTypeRelation() const;
	string GetRelationName() const;

	static int GetMax();

	static void SetMax(int _max);

	bool operator==(const RelationContact& relation);

	//Ham hien thi thong tin lien lac
	friend ostream& operator<<(ostream& os, const RelationContact& re);
};

