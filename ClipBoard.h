#ifndef CLIPBOARD_H
#define CLIPBOARD_H
#include<iostream>
#include<vector>
#include"Context.h"
using namespace std;
class ClipBoard{
public:
    vector<string> group;
    bool Copy_One(Context& context,int pages,int line,string begin,string end,ClipBoard& clipBoard);
    void Copy_Line(Context& context,int pages,int begin,int end,ClipBoard& clipBoard);
    void Copy_Page(Context& context,int pages,ClipBoard& clipBoard);
    bool Paste(Context& context,int pages,int line,string word,ClipBoard& clipBoard);
};

#endif // CLIPBOARD_H
