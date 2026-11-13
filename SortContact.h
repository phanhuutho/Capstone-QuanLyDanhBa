#pragma once
#include "Contact.h"
#include "Utilities.h"
#include <algorithm>
#include <vector>

//Hoan vi gia tri cua cap mang phan tu 0 vs 25, 1 vs 24, 2 vs 23,....., 12 vs 13
void Swap(vector<vector<Contact*>>& lstContact)
{
    int start = 0;
    int end = lstContact.size() - 1;

    while (start < end)
    {
        swap(lstContact[start], lstContact[end]);
        start++;
        end--;
    }
}

//Sap xep ten theo thu tu a->z
void SortContact_ASC(vector<vector<Contact*>>& lstContact)
{
    /*for (vector<Contact*>& vector_c : lstContact)
    {
        sort(vector_c.begin(), vector_c.end(), [](const Contact* c1, const Contact* c2) {
            return GetLastName(c1->GetName()) < GetLastName(c2->GetName());
        });
    }*/
}

//Sap xep ten theo thu tu z->a
void SortContact_DESC(vector<vector<Contact*>>& lstContact)
{
    Swap(lstContact); //goi ham hoan vi
    for (vector<Contact*>& vector_c : lstContact)
    {
        sort(vector_c.begin(), vector_c.end(), [](const Contact* c1, const Contact* c2) {
            return GetLastName(c1->GetName()) > GetLastName(c2->GetName());
        });
    }
}