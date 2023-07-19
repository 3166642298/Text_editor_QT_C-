#include"Add.h"
bool Edit_Page_Add_One(Context &context, int line,int pages, string word, string s)
{
    bool ok=false;
    int count = 0;
    for (auto a : context.text[pages - 1][line - 1])
    {
        count++;
        if (a == s)
        {
            context.text[pages - 1][line - 1].insert(context.text[pages - 1][line - 1].begin() + count, word);
            ok=true;
            context.voke[pages - 1].Push_Up_Voke(context.voke[pages - 1]);
            context.voke[pages-1].Add_Voke(context.text[pages - 1],context.voke[pages-1]);
            break;
        }
    }
    return ok;
}

void Change_Line(vector<string> *group, string s)
{
    string word;
    for(int i=0;i<s.size();i++)
    {
        if((s[i]>='A'&&s[i]<='Z')||(s[i]>='a'&&s[i]<='z'))
        {
            word+=s[i];
            if(i==s.size()-1)
            {
                (*group).push_back(word);
            }
        }else if(s[i]!='\n'){
            if (word != "")//表示s已经存了字符，即相当于已经存了一个英文单词，先将之前的保存
            {
                (*group).push_back(word);
            }
            word = s[i];
            (*group).push_back(word);//单个字符保存
            word = "";
        }
    }
}

void Edit_Page_Add_Line(Context &context,int n,int pages,vector<string> *group)
{
    Line line;
    line.insert(line.begin(), (*group).begin(), (*group).end());
    context.text[pages - 1].insert(context.text[pages - 1].begin() + n, line);
    context.voke[pages - 1].Push_Up_Voke(context.voke[pages - 1]);
    context.voke[pages-1].Add_Voke(context.text[pages - 1],context.voke[pages-1]);
}
