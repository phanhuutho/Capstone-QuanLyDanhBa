#pragma once
#include "Contact.h"
#include "RelationContact.h"
#include "Date.h"
#include "DisplayContactManager.h"
#include "Utilities.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <chrono>

using namespace std;

class ContactManager
{
private:
    vector<vector<Contact*>> ListContacts; // Co 26 vector<Contact*>, moi vector<Contact*> dai dien cho mot chu cai. co 26 chu cai: a,b,c,d,e,f,...x,y,z va vi tri a tuong duong la 0, z la 25
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

    vector<vector<Contact*>> GetListContacts() const
    {
        return ListContacts;
    }

    vector<RelationContact*> GetListRelations() const
    {
        return ListRelations;
    }

    //Huu Tho -------------------------------------------
    ContactManager(string _filename) : Filename(_filename) {}

    void CreditRelation(string relation, int& type)
    {
        RelationContact* re;
        if (ListRelations.size() == 0)
        {
            type = 1;
            re = new RelationContact(type, relation);
            ListRelations.push_back(re);
        }
        else
        {
            bool chkExistRelation = false;
            RelationContact* re = FindRelationByName(relation, chkExistRelation);
            if (chkExistRelation)
            {
                type = re->GetTypeRelation();
            }
            else
            {
                type = ListRelations.size() + 1;
                re = new RelationContact(type, relation);
                ListRelations.push_back(re);
            }
        }
    }

    void AddContact(int type, string relation, string name, string phone, string birth = "", string note = "")
    {
        Date dBirth;
        bool foundByPhone = false;

        Contact* cFoundByPhone = FindByPhone(phone, foundByPhone);

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
                            if (birth != "")
                            {
                                dBirth.FromString(birth);
                                c->SetBirthday(dBirth);
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
        else
        {
            if (birth != "")
            {
                dBirth.FromString(birth);
            }
            Contact* c = new Contact(name, phone, relation, type, dBirth, note);
            int idx = FindIndexVectorContactByName(name);
            ListContacts[idx].push_back(c);

            //sap xep thu tu ten trong mang tuong ung theo chu cai dau tien cua ten
            sort(ListContacts[idx].begin(), ListContacts[idx].end(), [](const Contact* c1, const Contact* c2) {
                return GetLastName(c1->GetName()) < GetLastName(c2->GetName());
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
        int row = 0;
        while (getline(file, line)) { //doc du lieu tung dong va gan du lieu tung dong vao bien chuoi ky tu 'line'
            if (row > 0) //row = 0 la line header, bo qua khong can doc
            {
                stringstream ss(line); //tao doi duong ss stringstream de xu ly lay du lieu cua lien lac tu chuoi ky tu 'line' 

                getline(ss, relation, ','); //tach theo ky tu '|' lan 1 va gan chuoi ky tu duoc tach o ben trai cho bien 'relation'
                getline(ss, name, ','); //tach theo ky tu '|' lan 1 va gan chuoi ky tu duoc tach o ben trai cho bien 'name'
                getline(ss, phone, ','); //tach theo ky tu '|' lan 1 va gan chuoi ky tu duoc tach o ben trai cho bien 'phone'
                getline(ss, strBirth, ','); //tach theo ky tu '|' lan 1 va gan chuoi ky tu duoc tach o ben trai cho bien 'strBirth'
                getline(ss, note, ','); //tach theo ky tu '|' lan 1 va gan chuoi ky tu duoc tach o ben trai cho bien 'note'

                birth.FromString(strBirth); //dung ham xu ly chuoi ngay thanh kieu du lieu Date

                CreditRelation(relation, type);

                AddContact(type, relation, name, phone, strBirth, note);
            }
            row++;
        }
        file.close();
    }

    void MergeFromFile(const string& filename, bool& isMerged, bool overwrite = false)
    {
        ifstream file(filename);
        if (!file.is_open()) 
            return;
        string line, relation, name, phone, strBirth, note;
        Date birth;
        int type = ListRelations.size();
        int row = 0;
        while (getline(file, line)) {
            if (row > 0)
            {
                stringstream ss(line);

                getline(ss, relation, ',');
                getline(ss, name, ',');
                getline(ss, phone, ',');
                getline(ss, strBirth, ',');
                getline(ss, note, ',');

                birth.FromString(strBirth);

                CreditRelation(relation, type);

                bool foundByPhone = false;

                Contact* cFoundByPhone = FindByPhone(phone, foundByPhone);

                if (foundByPhone)
                {
                    if (overwrite)
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
                                    c->SetTypeRelation(type);
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
            row++;
        }
        isMerged = true;
        file.close();
    }

    vector<Contact*> GetListContactValidInYear() const
    {
        vector<Contact*> result;

        chrono::system_clock::time_point now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);

        tm localTime;
        localtime_s(&localTime, &currentTime);
        int month = localTime.tm_mon + 1;
        int day = localTime.tm_mday;

        for (vector<Contact*> vector_c : ListContacts)
        {
            for (Contact* c : vector_c)
            {
                if (!c->GetBirthday().IsEmpty() && (c->GetBirthday().GetMonth() > month || (c->GetBirthday().GetMonth() == month && c->GetBirthday().GetDay() >= day)))
                {
                    result.push_back(c);
                }
            }
        }

        sort(result.begin(), result.end(), [](const Contact* c1, const Contact* c2) {
            return c1->GetBirthday().CountDayToBirthdayInCurrentYear() < c2->GetBirthday().CountDayToBirthdayInCurrentYear();
        });

        return result;
    }

    void WriteFile(const string &filename, bool &isSuccess)
    {
        isSuccess = false;
        ofstream outFile(filename, ios::out);

        if (!outFile.is_open())
        {
            isSuccess = false;
            cout << "Error: Not open/create file: " << filename << endl;
            return;
        }

        outFile << "Nhom,Ten,SDT,Ngay Sinh,Ghi Chu";
        outFile << "\n";
        for (vector<Contact*> vector_c : ListContacts)
        {
            for (Contact* c : vector_c)
            {
                outFile << c->GetRelationName();
                outFile << ",";
                outFile << c->GetName();
                outFile << ",";
                outFile << c->GetPhone();
                outFile << ",";
                outFile << c->GetBirthday().DateToString();
                outFile << ",";
                outFile << c->GetNote();
                outFile << "\n";
            }
        }
        outFile.close();
        isSuccess = true;
    }

    void EditRelation(RelationContact& reEdit)
    {
        for (RelationContact* re : ListRelations)
        {
            if (re->GetTypeRelation() == reEdit.GetTypeRelation())
            {
                re->SetRelationName(reEdit.GetRelationName());
            }
        }
    }

    void DeleteRelation(RelationContact& reDelete)
    {
        for (vector<RelationContact*>::iterator it = ListRelations.begin(); it != ListRelations.end();)
        {
            if ((*it)->GetTypeRelation() == reDelete.GetTypeRelation())
            {
                delete* it;
                it = ListRelations.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    //---------------------------------------------------



    //Quang Huy -----------------------------------------

    //---------------------------------------------------



    //Thien Son -----------------------------------------

    //---------------------------------------------------



    //Tung Quang ----------------------------------------

    //---------------------------------------------------
};

