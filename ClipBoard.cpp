#include"ClipBoard.h"
bool ClipBoard::Copy_One(Context &context, int pages, int line, string begin, string end, ClipBoard &clipBoard)
{
    bool ok=false;
    bool ok1=false;
    for(string s:context.text[pages-1][line-1])
    {
        if(s==begin)
        {
            ok=true;
            ok1=true;
        }
        if(ok==true)
        {
             clipBoard.group.push_back(s);
        }
        if(s==end)
        {
             ok=false;
        }
    }
    return ok1;
}

void ClipBoard::Copy_Line(Context &context, int pages, int begin, int end, ClipBoard &clipBoard)
{
    Line line;
    for(int i=begin-1;i<=end-1;i++)
    {
        line.insert(line.begin(),context.text[pages-1][i].begin(),context.text[pages-1][i].end());
        clipBoard.group.insert(clipBoard.group.end(),line.begin(),line.end());
    }
}

void ClipBoard::Copy_Page(Context &context, int pages, ClipBoard &clipBoard)
{
    for(Line line:context.text[pages-1])
    {
        for(string s:line)
        {
             clipBoard.group.push_back(s);
        }
    }
}

bool ClipBoard::Paste(Context &context, int pages, int line, string word,ClipBoard& clipBoard)
{
    int count=0;
    bool ok=false;
    for(string s :context.text[pages-1][line-1])
    {
        if(s==word)
        {
             ok=true;
             break;
        }
        count++;
    }
    if(ok==false)
    {
        return ok;
    }else{
        context.text[pages-1][line-1].insert(context.text[pages-1][line-1].begin()+count,clipBoard.group.begin(),clipBoard.group.end());
        context.voke[pages - 1].Push_Up_Voke(context.voke[pages - 1]);
        context.voke[pages-1].Add_Voke(context.text[pages - 1],context.voke[pages-1]);
        return ok;
    }
}
