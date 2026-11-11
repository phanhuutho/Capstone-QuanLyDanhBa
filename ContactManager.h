#pragma once
#include "Contact.h"
#include "RelationContact.h"
#include "Date.h"
#include "Utilities.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

class ContactManager
{
private:
    vector<vector<Contact*>> ListContacts; // Co 26 vector<Contact>, moi vector<Contact> dai dien cho mot chu cai. co 26 chu cai: a,b,c,d,e,f,...x,y,z va vi tri a tuong duong la 0, z la 25
    string Filename;
    vector<RelationContact*> ListRelations; // Mang dong con tro lop RelationContact

    vector<Contact*> a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;
public:

    void InitContactManage()
    {
        //Init ListContacts voi 26 vector<Contact> 26 chu cai
        ListContacts.push_back(a);
        ListContacts.push_back(b);
        ListContacts.push_back(c);
        ListContacts.push_back(d);
        ListContacts.push_back(e);
        ListContacts.push_back(f);
        ListContacts.push_back(g);
        ListContacts.push_back(h);
        ListContacts.push_back(i);
        ListContacts.push_back(j);
        ListContacts.push_back(k);
        ListContacts.push_back(l);
        ListContacts.push_back(m);
        ListContacts.push_back(n);
        ListContacts.push_back(o);
        ListContacts.push_back(p);
        ListContacts.push_back(q);
        ListContacts.push_back(r);
        ListContacts.push_back(s);
        ListContacts.push_back(t);
        ListContacts.push_back(u);
        ListContacts.push_back(v);
        ListContacts.push_back(w);
        ListContacts.push_back(x);
        ListContacts.push_back(y);
        ListContacts.push_back(z);
    }

    ContactManager() 
    {

    }

    ~ContactManager() 
    {

        ClearAll();
    }

    void ClearAll()
    {
        for (vector<Contact*> vector_c : ListContacts)
        {
            for (Contact* c : vector_c)
                delete c;
            vector_c.clear();
        }

        for (RelationContact* re : ListRelations)
        {
            delete re;
        }
        ListRelations.clear();
    }

    Contact* FindByPhone(string phone, bool& found) const
    {
        found = false;
        for (vector<Contact*> vector_c : ListContacts)
        {
            for (Contact* c : vector_c)
            {
                if (c->GetPhone() == phone)
                {
                    found = true;
                    return c;
                }
            }
        }
        return nullptr;
    }

    Contact* FindByName(string name, bool& found) const
    {
        found = false;
        int idx = FindIndexVectorContactByName(name);
        for (Contact* c : ListContacts[idx]) 
        {
            if (c->GetName() == name) 
            {
                found = true;
                return c;
            }
        }
        return nullptr;
    }

    RelationContact* FindRelationByName(string name, bool& found) const
    {
        found = false;
        for (RelationContact* re : ListRelations) 
        {
            if (re->GetRelationName() == name) 
            {
                found = true;
                return re;
            }
        }
        return nullptr;
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

        int i = 0;
        for (vector<Contact*> vector_c : ListContacts)
        {
            for (Contact* c : vector_c)
            {
                cout << left
                    << setw(10) << (i + 1)
                    << setw(15) << "| " + c->GetNameRelation()
                    << setw(20) << "| " + c->GetName()
                    << setw(15) << "| " + c->GetPhone()
                    << setw(15) << "| " + c->GetBirthday().DateToString()
                    << setw(25) << "| " + c->GetNote()
                    << endl;
                i++;
            }
        }
        cout << string(100, '-') << endl;
    }



    //Huu Tho -------------------------------------------
    ContactManager(string _filename) : Filename(_filename) {}

    void CreditRelation(string _relation, int& type)
    {
        RelationContact* re;
        if (ListRelations.size() == 0)
        {
            type = 1;
            re = new RelationContact(type, _relation);
            ListRelations.push_back(re);
        }
        else
        {
            bool chkExistRelation = false;
            RelationContact* re = FindRelationByName(_relation, chkExistRelation);
            if (chkExistRelation)
            {
                type = re->GetTypeRelation();
            }
            else
            {
                type = ListRelations.size() + 1;
                re = new RelationContact(type, _relation);
                ListRelations.push_back(re);
            }
        }
    }

    void SortContact_ASC()
    {
        for (vector<Contact*> vector_c : ListContacts)
        {
            sort(vector_c.begin(), vector_c.end(), [](const Contact* c1, const Contact* c2) {
                return GetLastName(c1->GetName()) < GetLastName(c2->GetName());
            });
        }
    }

    void SortContact_DESC()
    {
        for (vector<Contact*> vector_c : ListContacts)
        {
            sort(vector_c.begin(), vector_c.end(), [](const Contact* c1, const Contact* c2) {
                return GetLastName(c1->GetName()) > GetLastName(c2->GetName());
            });
        }
    }

    void AddContact(int _type, string _relation, string _name, string _phone, string _birth = "", string _note = "")
    {
        Date birth;
        bool foundByPhone = false;

        Contact* cFoundByPhone = FindByPhone(_phone, foundByPhone);

        if (foundByPhone)
        {
            for (vector<Contact*> vector_c : ListContacts)
            {
                for (Contact* c : vector_c)
                {
                    if (cFoundByPhone->GetPhone() == c->GetPhone())
                    {
                        if (cFoundByPhone->GetBirthday().IsEmpty())
                        {
                            if (_birth != "")
                            {
                                birth.FromString(_birth);
                                c->SetBirthday(birth);
                            }
                        }

                        if (cFoundByPhone->GetNote().empty())
                        {
                            if (_note != "")
                            {
                                c->SetNote(_note);
                            }
                        }

                        break;
                    }
                }
            }
        }
        else
        {
            Contact* c = new Contact(_name, _phone, _relation, _type, birth, _note);
            int idx = FindIndexVectorContactByName(_name);
            ListContacts[idx].push_back(c);

            sort(ListContacts[idx].begin(), ListContacts[idx].end(), [](const Contact* c1, const Contact* c2) {
                return GetLastName(c1->GetName()) < GetLastName(c2->GetName()); // Dung dau < de tang dan, > de giam dan
             });
        }
    }

    void LoadFromFile() {
        ifstream file(Filename);
        if (!file.is_open()) return;

        ClearAll();

        string line, relation, name, phone, strBirth, note;
        Date birth;
        int type = 0; //default type relation = 0 truoc khi doc du lieu file danh ba. moi gia tri cua bien type tuong ung voi 1 relation name
        while (getline(file, line)) { //doc du lieu tung dong va gan du lieu tung dong vao bien chuoi ky tu 'line'
            stringstream ss(line); //tao doi duong ss stringstream de xu ly lay du lieu cua lien lac tu chuoi ky tu 'line' 

            getline(ss, relation, '|'); //tach theo ky tu '|' lan 1 va gan chuoi ky tu duoc tach o ben trai cho bien 'relation'
            getline(ss, name, '|'); //tach theo ky tu '|' lan 1 va gan chuoi ky tu duoc tach o ben trai cho bien 'name'
            getline(ss, phone, '|'); //tach theo ky tu '|' lan 1 va gan chuoi ky tu duoc tach o ben trai cho bien 'phone'
            getline(ss, strBirth, '|'); //tach theo ky tu '|' lan 1 va gan chuoi ky tu duoc tach o ben trai cho bien 'strBirth'
            getline(ss, note, '|'); //tach theo ky tu '|' lan 1 va gan chuoi ky tu duoc tach o ben trai cho bien 'note'

            birth.FromString(strBirth); //dung ham xu ly chuoi ngay thanh kieu du lieu Date

            CreditRelation(relation, type);
            
            AddContact(type, relation, name, phone, strBirth, note);
        }
        file.close();
    }

    void MergeFromFile(string _filename, bool _overwrite = false)
    {
        ifstream file(_filename);
        if (!file.is_open()) return;
        string line, relation, name, phone, strBirth, note;
        Date birth;
        int type = ListRelations.size();
        while (getline(file, line)) {
            stringstream ss(line);

            getline(ss, relation, '|');
            getline(ss, name, '|');
            getline(ss, phone, '|');
            getline(ss, strBirth, '|');
            getline(ss, note, '|');

            birth.FromString(strBirth);

            CreditRelation(relation, type);

            bool foundByPhone = false;

            Contact* cFoundByPhone = FindByPhone(phone, foundByPhone);

            if (foundByPhone)
            { 
                if (_overwrite)
                {
                    for (vector<Contact*> vector_c : ListContacts)
                    {
                        for (Contact* c : vector_c)
                        {
                            if (cFoundByPhone->GetPhone() == c->GetPhone())
                            {
                                int type = ListRelations.size();
                                CreditRelation(relation, type);

                                c->SetName(name);
                                c->SetRelation(type);
                                c->SetRelationName(relation);
                                if (strBirth != "")
                                {
                                    birth.FromString(strBirth);
                                    c->SetBirthday(birth);
                                }
                                if (note != "")
                                {
                                    c->SetNote(note);
                                }
                                break;
                            }
                        }
                    }
                }
                else
                {
                    for (vector<Contact*> vector_c : ListContacts)
                    {
                        for (Contact* c : vector_c)
                        {
                            if (cFoundByPhone->GetPhone() == c->GetPhone())
                            {
                                if (cFoundByPhone->GetBirthday().IsEmpty())
                                {
                                    if (strBirth != "")
                                    {
                                        birth.FromString(strBirth);
                                        c->SetBirthday(birth);
                                    }
                                }

                                if (cFoundByPhone->GetNote().empty())
                                {
                                    if (note != "")
                                    {
                                        c->SetNote(note);
                                    }
                                }

                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                AddContact(type, relation, name, phone, strBirth, note);
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

