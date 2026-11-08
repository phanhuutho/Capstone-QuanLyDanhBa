#pragma once
#include "Contact.h"
#include "RelationContact.h"
#include "Date.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

class ContactManager
{
private:
    vector<Contact*> ListContacts; // Mang dong con tro lop Contact
    string Filename;
    vector<RelationContact*> ListRelations; // Mang dong con tro lop RelationContact
public:
    ContactManager() {};

    ~ContactManager() {
        for (Contact* contact : ListContacts) 
            delete contact;
        for (RelationContact* relation : ListRelations)
            delete relation;

        ClearAll();
    }

    void ClearAll() 
    {
        ListContacts.clear();
        ListRelations.clear();
    }

    Contact FindByPhone(string phone) const
    {
        for (const auto& c : ListContacts) {
            if (c->GetPhone().find(phone) != string::npos) {
                return *c;
            }
        }
    }

    Contact FindByName(string name) const
    {
        for (const auto& c : ListContacts) {
            if (c->GetName().find(name) != string::npos) {
                return *c;
            }
        }
    }

    void DisplayListContact()
    {
        cout << left
            << setw(10) << "[STT]"
            << setw(15) << "| [Quan He]"
            << setw(20) << "| [Ten]"
            << setw(15) << "| [SDT]"
            << setw(15) << "| [Ngay Sinh]"
            << setw(25) << "| [Ghi Chu]"
            << endl;
        cout << string(100, '-') << endl;

        for (size_t i = 0; i < ListContacts.size(); i++) {
            cout << left
                << setw(10) << (i + 1)
                << setw(15) << "| " + ListContacts[i]->GetNameRelation()
                << setw(20) << "| " + ListContacts[i]->GetName()
                << setw(15) << "| " + ListContacts[i]->GetPhone()
                << setw(15) << "| " + ListContacts[i]->GetBirthday().DateToString()
                << setw(25) << "| " + ListContacts[i]->GetNote()
                << endl;
        }
        cout << string(100, '-') << endl;
    }



    //Huu Tho -------------------------------------------
    ContactManager(string _filename) : Filename(_filename) { LoadFromFile(); }

    void LoadFromFile() {
        ifstream file(Filename);
        if (!file.is_open()) return;

        ClearAll();

        string line, relation, name, phone, strBirth, note;
        Date birth;
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, relation, '|');
            getline(ss, name, '|');
            getline(ss, phone, '|');
            getline(ss, strBirth, '|');
            getline(ss, note, '|');

            birth.FromString(strBirth);

            int type = 0;

            if (ListRelations.size() == 0)
            {
                type = 1;
                ListRelations.push_back(new RelationContact(1, relation));
            }
            else
            {
                bool chkExistRelation = false;
                for (RelationContact* re : ListRelations)
                {
                    if (re->GetRelationName() == relation)
                    {
                        type = re->GetTypeRelation();
                        chkExistRelation = true;
                        break;
                    }
                }

                if (!chkExistRelation)
                {
                    type = ListRelations.size() + 1;
                    ListRelations.push_back(new RelationContact(ListRelations.size() + 1, relation));
                }
            }

            bool found = false;
            for (Contact* c : ListContacts) {
                if (c->GetName().find(name) != string::npos) {
                    found = true;
                    if (c->GetBirthday().IsEmpty())
                    {
                        c->SetBirthday(birth);
                    }
                    if (c->GetNote().empty())
                    {
                        c->SetNote(note);
                    }
                }
            }
            if (!found)
            {
                ListContacts.push_back(new Contact(name, phone, relation, type, birth, note));
            }
        }
        file.close();
    }

    void MergeFromFile(string _filename, bool _overwrite = false)
    {
        ifstream file(_filename);
        if (!file.is_open()) return;
        string line, type, name, phone, strBirth, note;
        Date birth;

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, type, ',');
            getline(ss, name, ',');
            getline(ss, phone, ',');
            getline(ss, strBirth, ',');
            getline(ss, note, ',');

            birth.FromString(strBirth);

            for (Contact* contact : ListContacts)
            {

            }
        }
        file.close();
    }
    //---------------------------------------------------



    //Quang Huy -----------------------------------------

    //---------------------------------------------------



    //Thien Son -----------------------------------------

    //---------------------------------------------------



    //Tung Quang ----------------------------------------

    //---------------------------------------------------
};

