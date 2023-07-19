#ifndef CONTEXT_H
#define CONTEXT_H
#include<iostream>
#include<vector>
#include<map>
#include"Revoke_Redo.h"
using namespace std;
typedef vector<string> Line;
typedef vector<Line>  Page;
class Context{
public:
    vector<Page> text;
    map<int,Voke> voke;
    void static Change_Context(string s,Context& context);
};
#endif // CONTEXT_H
