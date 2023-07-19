#include"Find.h"
TextQuery::TextQuery(vector< vector<string> >& h)
{
    int n = 1;
    for (auto a : h)
    {
        for (auto b : a)
        {
            auto& lines = wm[b];
            if (!lines)
            {
                lines.reset(new set<line_no>);
            }
            lines->insert(n);
        }
        n++;
    }
}
string TextQuery::query(string s)
{
    string hang;
    auto iter = wm.find(s);
    if (iter != wm.end())
    {
        string h;
        for (auto n: *wm[s])
        {
            h=h+to_string(n)+",";
        }
        hang="该文本在此页第"+h+"出现过！";
    }
    else
    {
        hang="该文本在此页没有出现过！";
    }
    return hang;
}
