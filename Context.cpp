#include"Context.h"

void Context::Change_Context(string s, Context& context)
{
    vector<string> *group=new vector<string>;
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
    Page page;
    Line line;
    for (string word :(*group))
    {
        line.push_back(word);
        if (line.size() == 50)//一行已经存了l个单词时，实现换行
        {
            if (page.size() == 30)//一页已经存了p行文本后，实现换页
            {
                context.text.push_back(page);//将Page保存在text容器中
                page.clear();
                page.push_back(line);
            }
            page.push_back(line);//将Line保存到Page中
            line.clear();
        }
    }
    if (line.size() != 0)
    {
        page.push_back(line);
    }
    if (page.size() != 0) {
        context.text.push_back(page);
    }
    delete group;
}

