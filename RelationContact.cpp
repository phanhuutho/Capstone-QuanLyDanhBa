#include "RelationContact.h"

int RelationContact::Max = 0;

RelationContact::RelationContact(int _type, string _name) : TypeRelation(_type), RelationName(_name) 
{ 
	Max++; 
}

RelationContact::~RelationContact() 
{ 
}

void RelationContact::SetTypeRelation(int _type) 
{ 
	TypeRelation = _type; 
}
void RelationContact::SetRelationName(string _name) 
{ 
	RelationName = _name; 
}

int RelationContact::GetTypeRelation() const 
{ 
	return TypeRelation; 
}

int RelationContact::GetMax()
{
	return Max;
}

void RelationContact::SetMax(int _max)
{
	Max = _max;
}

string RelationContact::GetRelationName() const 
{ 
	return RelationName; 
}

bool RelationContact::operator==(const RelationContact& relation)
{
	return TypeRelation == relation.TypeRelation && RelationName == relation.RelationName;
}

//Ham hien thi thong tin lien lac
ostream& operator<<(ostream& os, const RelationContact& re)
{
	os << re.GetTypeRelation() << ":" << "[" << re.GetRelationName() << "]";
	os << endl;

	return os;
}