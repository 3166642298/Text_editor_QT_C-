#ifndef MOVE_H
#define MOVE_H
#include<iostream>
using namespace std;
#include"Context.h"
bool Edit_Page_Move_Pervious_Line(Context& context,int line,int n,int pages,string word);
bool Edit_Page_Move_Next_Line(Context& context,int line,int n,int pages,string word);
bool Edit_Page_Move_Left_Column(Context& context,int line,int n,int pages,string word);
bool Edit_Page_Move_Right_Column(Context& context,int line,int n,int pages,string word);
#endif // MOVE_H
