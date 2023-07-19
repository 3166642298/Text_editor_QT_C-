#ifndef ADD_H
#define ADD_H
#include<iostream>
#include"Context.h"
using namespace std;
bool Edit_Page_Add_One(Context& context,int line,int pages,string word,string s);
void Change_Line(vector<string>* group,string s);
void Edit_Page_Add_Line(Context& context,int n,int pages,vector<string>* group);
#endif // ADD_H
