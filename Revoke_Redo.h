#ifndef REVOKE_REDO_H
#define REVOKE_REDO_H
#include<iostream>
#include<vector>
using namespace std;
typedef vector<string> Line;
typedef vector<Line>  Page;
class Context;
class Voke{
public:
    vector<Page> v;
    int count;
    void Add_Voke(Page page, Voke& voke);//该函数实现对该页文章内容更改的保存
    void Push_Up_Voke(Voke& voke);//更新v容器所保存的撤销和回退操作，主要模仿实现word的撤销和回退操作
    void Revoke(Voke& voke,Context& context, size_t pages);//进行撤销操作会调用该函数
    void Recove(Voke& voke,Context& context, size_t pages);//进行回退操作会调用该函数
};

#endif // REVOKE_REDO_H
