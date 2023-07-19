#include"File_Operator.h"
#include<fstream>
bool File_Open(string fileName,Context& context)
{
    ifstream ifs(fileName,ios::in);
    if(!ifs.is_open())
    {
        return false;
    }else{
        ifs.close();
        File_Read(fileName,context);
        return true;
    }
}

void File_Read(string fileName, Context &context)
{
    ifstream ifs(fileName,ios::in);
    string word,line;
    while (getline(ifs,line))
    {
        word+=line;
    }
    context.Change_Context(word,context);
    ifs.close();
}

bool File_Save(string fileName, Context &context)
{
    ifstream ifs(fileName, ios::in);
    if(ifs.is_open())
    {
        return false;
    }else{
        File_Save_context(fileName,context);
        return true;
    }
}

void File_Save_context(string fileName, Context &context)
{
    ofstream ofs;
    ofs.open(fileName, ios::trunc);
    for (Page page :context.text)
    {
        for (Line line : page)
        {
            for (string word : line)
            {
                ofs<< word;
            }
        }
        ofs<< endl;
    }
    ofs.close();
}
