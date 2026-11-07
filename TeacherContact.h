#pragma once
#include "Contact.h"
class TeacherContact : public Contact
{
public:
	TeacherContact(string _name = "", string _phone = "", int _type = 0)
		: Contact(_name, _phone, "Giao Vien")
	{
		SetRelation(_type);
	}

	~TeacherContact() {}
};


