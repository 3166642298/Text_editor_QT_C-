#ifndef FIND_H
#define FIND_H
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<memory>
using namespace std;
using line_no = vector<string>::size_type;
class TextQuery {
public:
    TextQuery(vector< vector<string> >&);
    map<string, shared_ptr<set<line_no> > > wm;
    string query(string s);
};
#endif // FIND_H
