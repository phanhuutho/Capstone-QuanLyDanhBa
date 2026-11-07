#pragma once
#include "Contact.h"
class FriendContact : public Contact
{
public:
	FriendContact(string _name = "", string _phone = "", int _type = 0)
		: Contact(_name, _phone, "Ban Be")
	{
		SetRelation(_type);
	}

	~FriendContact() {}
};

