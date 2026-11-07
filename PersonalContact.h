#pragma once
#include "Contact.h"
class PersonalContact : public Contact
{
private:
	int Type = 0;
public:
	PersonalContact(string _name = "", string _phone = "", int _type = 0)
		: Contact(_name, _phone, "Ca Nhan")
	{
		SetRelation(_type);
	}

	~PersonalContact() {}
};

