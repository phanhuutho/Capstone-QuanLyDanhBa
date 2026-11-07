#pragma once
#include <string>
#include <iostream>
#include "Date.h"

using namespace std;

class Contact
{
private:
    string RelationName;
    int TypeRelation = 0;
protected:
    string Name;
    string Phone;
    string Note;
    Date Birthday;
public:
    // Constructor
    Contact(string _name = "", string _phone = "", string _relation = "") : Name(_name), Phone(_phone), RelationName(_relation) {}
    Contact(string _name = "", string _phone = "", string _relation = "", int _type = 0) : Name(_name), Phone(_phone), RelationName(_relation), TypeRelation(_type){}
    Contact(string _name = "", string _phone = "", string _relation = "", int _type = 0, Date _birth = NULL) : Name(_name), Phone(_phone), RelationName(_relation), TypeRelation(_type), Birthday(_birth){}
    Contact(string _name = "", string _phone = "", string _relation = "", int _type = 0, Date _birth = NULL, string _note = "") : Name(_name), Phone(_phone), RelationName(_relation), TypeRelation(_type), Birthday(_birth), Note(_note){}

    // Destructor
    virtual ~Contact() {}

    // Getters & Setters
    string GetName() const { return Name; }
    void SetName(string _name) { Name = _name; }
    string GetPhone() const { return Phone; }
    void SetPhone(string _phone) { Phone = _phone; }
    string GetNameRelation() const { return RelationName; }
    void SetRelation(int _type) { TypeRelation = _type; }
    string GetNote() const { return Note; }
    void SetNote(string _note) { Note = _note; }
    Date GetBirthday() const { return Birthday; }
    void SetBirthday(Date _birth) { Birthday = _birth; }

    //Ham hien thi thong tin lien lac
    void Display() const
    {
        cout << "[" << GetNameRelation() << "]" << " Ten: " << Name << " | SDT: " << Phone;
        if (!Birthday.IsEmpty())
        {
            cout << " | Ngay Sinh: ";
            Birthday.Print();
        }
        if (!Note.empty())
        {
            cout << " | Ghi Chu: " << Note;
        }
        cout << endl;
    }

    //Ham xuat thong tin lien lac ho tro luu file CSV
    string ToStringCSV() const
    {
        string result = GetNameRelation() + "|" + Name + "|" + Phone;
        if (!Birthday.IsEmpty())
            result = result + "|" + Birthday.DateToString();
        if (!Note.empty())
            result = result + "|" + Note;
        return result;
    }



    //Huu Tho -------------------------------------------

    //---------------------------------------------------



    //Quang Huy -----------------------------------------

    //---------------------------------------------------



    //Thien Son -----------------------------------------

    //---------------------------------------------------



    //Tung Quang ----------------------------------------

    //---------------------------------------------------
};

