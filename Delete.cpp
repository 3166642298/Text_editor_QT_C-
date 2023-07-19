#include"Delete.h"
bool Edit_Page_Delete_One(Context &context, int pages, int n, string word)
{
    bool ok=false;
    int count = 0;
    for (auto a : context.text[pages-1][n-1])
    {
        if (a == word)
        {
            context.text[pages - 1][n - 1].erase(context.text[pages - 1][n - 1].begin() + count);
            context.voke[pages - 1].Push_Up_Voke(context.voke[pages - 1]);
            context.voke[pages-1].Add_Voke(context.text[pages - 1],context.voke[pages-1]);
            ok=true;
            break;
        }
        count++;
    }
    return ok;
}

void Edit_Page_Delete_Line(Context &context, int pages, int n)
{
    context.text[pages - 1].erase(context.text[pages - 1].begin() + n - 1);
    context.voke[pages - 1].Push_Up_Voke(context.voke[pages - 1]);
    context.voke[pages-1].Add_Voke(context.text[pages - 1],context.voke[pages-1]);
}
