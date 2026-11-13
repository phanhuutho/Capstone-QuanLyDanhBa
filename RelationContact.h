#pragma once
#include <string>

using namespace std;

class RelationContact
{
private:
	int TypeRelation;
	string RelationName;
	int count = 0;
public:
	RelationContact(int _type = 0, string _name = "") : TypeRelation(_type), RelationName(_name) { count++; }

	~RelationContact() { count--; }

	void SetTypeRelation(int _type) { TypeRelation = _type; }
	void SetRelationName(string _name) { RelationName = _name; }

	int GetTypeRelation() const { return TypeRelation; }
	string GetRelationName() const { return RelationName; }

	int GetCount() { return count; }

	bool operator==(const RelationContact& relation)
	{
		return TypeRelation == relation.TypeRelation && RelationName == relation.RelationName;
	}

	//Ham hien thi thong tin lien lac
	void Display() const
	{
		cout << GetTypeRelation() << ":" << "[" << GetRelationName() << "]";
		cout << endl;
	}
};

