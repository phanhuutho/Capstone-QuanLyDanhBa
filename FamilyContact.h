#pragma once
#include "Contact.h"
class FamilyContact : public Contact
{
public:
	FamilyContact(string _name = "", string _phone = "", int _type = 0)
		: Contact(_name, _phone, "Gia Dinh")
	{
		SetRelation(_type);
	}

	~FamilyContact() {}
};

