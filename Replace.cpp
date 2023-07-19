#include"Replace.h"
bool Replace(string s1, string s2, Context &context,int pages)
{
    bool ok=false;
    for (auto& a :context.text[pages-1])
    {
        for (auto& b : a)
        {
            if (b == s1)
            {
                ok=true;
                b = s2;
            }
        }
    }
    if(ok==true)
    {
        context.voke[pages - 1].Push_Up_Voke(context.voke[pages - 1]);
        context.voke[pages-1].Add_Voke(context.text[pages - 1],context.voke[pages-1]);
    }
    return ok;
}
