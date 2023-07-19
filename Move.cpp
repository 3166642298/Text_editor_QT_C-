#include"Move.h"
bool Edit_Page_Move_Pervious_Line(Context &context, int line, int n,int pages, string word)
{
    bool ok=false;
    int column=0;
    for(string s:context.text[pages-1][line-1])
    {
        if(s==word)
        {
            context.text[pages-1][line-1].erase(context.text[pages-1][line-1].begin() + column);
            ok=true;
            break;
        }
        column++;
    }
    if(ok==false)
    {
        return ok;
    }else{
        context.text[pages-1][line-1-n].insert( context.text[pages - 1][line- 1-n].begin() + column, word);
        context.voke[pages - 1].Push_Up_Voke(context.voke[pages - 1]);
        context.voke[pages-1].Add_Voke(context.text[pages - 1],context.voke[pages-1]);
        return true;
    }
}

bool Edit_Page_Move_Next_Line(Context &context, int line, int n, int pages, string word)
{
    bool ok=false;
    int column=0;
    for (string s : context.text[pages - 1][line - 1])
    {
        if (s == word)
        {
            context.text[pages - 1][line - 1].erase(context.text[pages - 1][line - 1].begin() + column);
            ok=true;
            break;
        }
        column++;
    }
    if(ok==false)
    {
        return ok;
    }else{
        context.text[pages - 1][line- 1+n].insert(context.text[pages - 1][line- 1+n].begin() + column, word);
        context.voke[pages - 1].Push_Up_Voke(context.voke[pages - 1]);
        context.voke[pages-1].Add_Voke(context.text[pages - 1],context.voke[pages-1]);
        return true;
    }
}

bool Edit_Page_Move_Left_Column(Context &context, int line, int n, int pages, string word)
{
    bool ok=false;
    int column=0;
    for (string s : context.text[pages - 1][line - 1])
    {
        if (s == word)
        {
            ok=true;
            break;
        }
        column++;
    }
    if(column<n)
    {
        ok=false;
    }
    if(ok==false)
    {
        return ok;
    }else{
        context.text[pages - 1][line - 1].erase(context.text[pages - 1][line - 1].begin() + column);
        context.text[pages - 1][line - 1].insert(context.text[pages - 1][line - 1].begin() + column - n, word);
        context.voke[pages - 1].Push_Up_Voke(context.voke[pages - 1]);
        context.voke[pages-1].Add_Voke(context.text[pages - 1],context.voke[pages-1]);
        return true;
    }
}

bool Edit_Page_Move_Right_Column(Context &context, int line, int n, int pages, string word)
{
    bool ok=false;
    int column=0;
    for (string s : context.text[pages - 1][line - 1])
    {
        if (s == word)
        {
            ok=true;
            break;
        }
        column++;
    }
    if (column + n >= context.text[pages - 1][line - 1].size())
    {
        ok=false;
    }
    if(ok==false)
    {
        return ok;
    }else{
        context.text[pages - 1][line - 1].erase(context.text[pages - 1][line - 1].begin() + column);
        context.text[pages - 1][line - 1].insert(context.text[pages - 1][line - 1].begin() + column + n, word);
        context.voke[pages - 1].Push_Up_Voke(context.voke[pages - 1]);
        context.voke[pages-1].Add_Voke(context.text[pages - 1],context.voke[pages-1]);
        return true;
    }
}
