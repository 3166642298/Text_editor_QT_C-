#ifndef FILE_OPERATOR_H
#define FILE_OPERATOR_H
#include<iostream>
#include"Context.h"
using namespace std;
bool File_Open(string fileName,Context& context);
void File_Read(string fileName,Context& context);
bool File_Save(string fileName,Context& context);
void File_Save_context(string fileName,Context& context);
#endif // FILE_OPERATOR_H
