#pragma once
#include <string>

using namespace std;

int FindIndexVectorContactByName(string _name)
{
    // 1. rfind: tim vi tri khoang trang cuoi cung tu phai sang trai (de tach lay last name)
    size_t last_space = _name.rfind(' ');
    string last_name = _name; // gan last name ban dau la tham so _name

    if (last_space != string::npos) //kiem tra vi tri last_space co ton tai hay khong
    {
        last_name = _name.substr(last_space + 1); // gan lai ten cho last name
    }

    // 2. Lay ky tu dau tien cua last name de phan loai vao cac vector<Contact>
    unsigned char c1 = last_name[0];
    unsigned char c2 = (last_name.length() > 1) ? last_name[1] : 0;
    int index = 0; // Mac dinh vi tri cua vector<Contact> 'a'

    if (c1 >= 'a' && c1 <= 'z') {
        index = c1 - 'a';
    }
    else if (c1 >= 'A' && c1 <= 'Z') {
        index = tolower(c1) - 'a';
    }
    else {
        // Xu ly cac chu cai tieng Viet co dau o ten chinh
        char base_char = 'a';

        if (c1 == 195) {
            if (c2 >= 128 && c2 <= 143) base_char = 'a';
            else if (c2 >= 148 && c2 <= 155) base_char = 'e';
            else if (c2 >= 156 && c2 <= 159) base_char = 'i';
            else if (c2 >= 160 && c2 <= 179) base_char = 'o';
            else if (c2 >= 180 && c2 <= 187) base_char = 'u';
            else if (c2 >= 188 && c2 <= 191) base_char = 'y';
        }
        else if (c1 == 196) {
            if (c2 == 142 || c2 == 143) base_char = 'd'; // Chu D tieng viet
        }

        index = base_char - 'a';
    }

    // Dam bao an toan khong vuot quá 26 vector
    if (index < 0 || index > 25)
        index = 0;

    return index;
}

string GetLastName(string _name)
{
    size_t last_space = _name.rfind(' ');
    string last_name = _name;

    if (last_space != string::npos)
    {
        last_name = _name.substr(last_space + 1);
    }
    return last_name;
}
