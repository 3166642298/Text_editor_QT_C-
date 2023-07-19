#include"Revoke_Redo.h"
#include"Context.h"
void Voke::Add_Voke(Page page, Voke &voke)
{
    voke.v.push_back(page);//将更改后该页的内容保存到voke容器中
    voke.count++;//计算该页进行了几次更改
}

void Voke::Push_Up_Voke(Voke &voke)
{
    voke.v.erase(voke.v.begin() + voke.count, voke.v.end());//更新voke容器
}

void Voke::Revoke(Voke &voke,Context &context, size_t pages)
{
    voke.count -= 2;
    context.text[pages-1] = voke.v[voke.count];//用voke容器中指定的内容去替换text中对应页的内容
    voke.count++;
}

void Voke::Recove(Voke &voke, Context &context, size_t pages)
{
    context.text[pages-1] = voke.v[voke.count];//用voke容器中指定的内容去替换text中对应页的内容
    voke.count++;
}
