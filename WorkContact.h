#pragma once
#include "Contact.h"
class WorkContact : public Contact
{
public:
	WorkContact(string _name = "", string _phone = "", int _type = 0)
		: Contact(_name, _phone, "Dong Nghiep")
	{
		SetRelation(_type);
	}

	~WorkContact() {}
};

