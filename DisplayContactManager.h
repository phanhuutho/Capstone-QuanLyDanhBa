#pragma once
#include "Contact.h"
#include <iomanip>
#include <vector>

void DisplayListContact(vector<vector<Contact*>>& lstContact)
{
    cout << left
        << setw(10) << "[STT]"
        << setw(15) << "| [Nhom]"
        << setw(30) << "| [Ten]"
        << setw(15) << "| [SDT]"
        << setw(15) << "| [Ngay Sinh]"
        << setw(25) << "| [Ghi Chu]"
        << endl;
    cout << string(110, '-') << endl;

    int i = 0;
    for (vector<Contact*> vector_c : lstContact)
    {
        for (Contact* c : vector_c)
        {
            cout << left
                << setw(10) << (i + 1)
                << setw(15) << ("| " + c->GetRelationName())
                << setw(30) << ("| " + c->GetName())
                << setw(15) << ("| " + c->GetPhone())
                << setw(15) << ("| " + c->GetBirthday().DateToString())
                << setw(45) << ("| " + c->GetNote())
                << endl;
            i++;
        }
    }
    cout << string(110, '-') << endl;
}

void DisplayListContact(vector<Contact*>& vector_c)
{
    cout << left
        << setw(10) << "[STT]"
        << setw(15) << "| [Nhom]"
        << setw(30) << "| [Ten]"
        << setw(15) << "| [SDT]"
        << setw(15) << "| [Ngay Sinh]"
        << setw(25) << "| [Ghi Chu]"
        << endl;
    cout << string(110, '-') << endl;

    int i = 0;
    for (Contact* c : vector_c)
    {
        cout << left
            << setw(10) << (i + 1)
            << setw(15) << ("| " + c->GetRelationName())
            << setw(30) << ("| " + c->GetName())
            << setw(15) << ("| " + c->GetPhone())
            << setw(15) << ("| " + c->GetBirthday().DateToString())
            << setw(45) << ("| " + c->GetNote())
            << endl;
        i++;
    }
    cout << string(110, '-') << endl;
}

void DisplayListRelation(vector<RelationContact*>& vector_re)
{
    cout << left
        << setw(10) << "[STT]"
        << setw(30) << "| [Ten Nhom]"
        << endl;
    cout << string(50, '-') << endl;

    for (RelationContact* re : vector_re)
    {
        cout << left
            << setw(10) << re->GetTypeRelation()
            << setw(15) << ("| " + re->GetRelationName())
            << endl;
    }
    cout << string(50, '-') << endl;
}