#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QMessageBox"
#include"QInputDialog"
#include"File_Operator.h"
#include"Find.h"
#include"Replace.h"
#include"Move.h"
#include"Add.h"
#include"Delete.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString title="提示信息";
    QString Info="此文本编译器使用说明: 用户每次打开文本编译器时，首先选择新建文本or打开文件，否则文本编辑区域为只读模式。";
    QMessageBox::information(this,title,Info);
    ui->textEdit->setReadOnly(true);//设为只读模式
    pages=1;
    context.text.clear();
    ui->textEdit->clear();
    Init_Button(false);
}

void MainWindow::Show_Page()
{
    if(context.voke[pages-1].v.size()==0)
    {
        context.voke[pages-1].Add_Voke(context.text[pages-1],context.voke[pages-1]);
    }
    ui->textEdit->clear();
    for(Line line:context.text[pages-1])
    {
        for(string s:line)
        {
            ui->textEdit->insertPlainText(QString::fromStdString(s));
        }
        ui->textEdit->insertPlainText("\n");
    }
}

void MainWindow::Init_Button(bool ok)
{
    ui->act_Save->setEnabled(ok);
    ui->act_Before->setEnabled(ok);
    ui->act_Next->setEnabled(ok);
    ui->act_Sure->setEnabled(ok);
    ui->act_Find->setEnabled(ok);
    ui->act_Replace->setEnabled(ok);
    ui->act_Close->setEnabled(ok);
    ui->act_Redo->setEnabled(ok);
    ui->act_Undo->setEnabled(ok);

    ui->act_Add_Line->setEnabled(ok);
    ui->act_Add_One->setEnabled(ok);

    ui->actMove_Pervious->setEnabled(ok);
    ui->actMove_next->setEnabled(ok);
    ui->actMove_left->setEnabled(ok);
    ui->actMove_Right->setEnabled(ok);

    ui->act_Delete_One->setEnabled(ok);
    ui->act_Delete_Line->setEnabled(ok);

    ui->act_Copy->setEnabled(ok);
    ui->act_Paste->setEnabled(ok);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_act_New_triggered()
{
    pages=1;
    context.text.clear();
    ui->textEdit->clear();
    Init_Button(false);
    ui->act_Close->setEnabled(true);
    ui->act_Open->setEnabled(false);
    ui->textEdit->setReadOnly(false);//进入编辑模式
    QString title="提示信息";
    QString Info="此为新建功能，可在文本编辑区域输入您的内容，新建完成时请点击Finish按钮以此退出该功能模块，方可使用其他功能。";
    QMessageBox::information(this,title,Info);
}


void MainWindow::on_act_Close_triggered()
{
    ui->textEdit->setReadOnly(true);//设为只读模式
    QString word=ui->textEdit->toPlainText();
    Context::Change_Context(word.toStdString(),context);
    if(context.text.size()!=0)
    {
         Show_Page();
         Init_Button(true);
    }
    ui->act_Close->setEnabled(false);
    ui->act_Open->setEnabled(true);
}

void MainWindow::on_act_Open_triggered()
{
    pages=1;
    context.text.clear();
    ui->textEdit->clear();
    Init_Button(false);
    ui->textEdit->setReadOnly(false);//进入编辑模式
    QString Title="输入文件名对话框";
    QString label="请输入要打开的文件名: ";
    QString iniInput="F:\文件名.txt";
    QLineEdit::EchoMode e=QLineEdit::Normal;
    bool ok1=false;
    QString fileName=QInputDialog::getText(this,Title,label,e,iniInput,&ok1);
    if(ok1==true&&!fileName.isEmpty())
    {
         bool ok=File_Open(fileName.toStdString(),context);
         if(ok==true){
            QString title="提示信息";
            QString Info="文件打开成功";
            QMessageBox::information(this,title,Info);
            if(context.text.size()!=0)
            {
                Show_Page();
                Init_Button(true);
            }
         }else{
            QString title="错误信息";
            QString Info="此文件名对应的文件不存在";
            QMessageBox::critical(this,title,Info);
         }
    }else{
         QString title="提示信息";
         QString Info="尝试打开文件失败";
         QMessageBox::information(this,title,Info);
    }
    ui->textEdit->setReadOnly(true);//设为只读模式
}

void MainWindow::on_act_Save_triggered()
{
    QString Title="输入文件名对话框";
    QString label="请输入要保存的文件名: ";
    QString iniInput="F:\文件名.txt";
    QLineEdit::EchoMode e=QLineEdit::Normal;
    bool ok1=false;
    QString fileName=QInputDialog::getText(this,Title,label,e,iniInput,&ok1);
    if(ok1==true&&!fileName.isEmpty())
    {
         bool ok=File_Save(fileName.toStdString(),context);
         if(ok==false)
         {
            QString Title="文件保存消息框";
            QString label="同名文件已存在,是否替换?";
            QMessageBox::StandardButton defaultBtn=QMessageBox::NoButton;
            QMessageBox::StandardButton result;
            result=QMessageBox::question(this,Title,label,QMessageBox::Yes|QMessageBox::No,defaultBtn);
            if(result==QMessageBox::Yes)
            {
                File_Save_context(fileName.toStdString(),context);
            }else{
                QString title="提示信息";
                QString Info="文件保存失败";
                QMessageBox::information(this,title,Info);
            }
         }else{
            QString title="提示信息";
            QString Info="文件保存成功";
            QMessageBox::information(this,title,Info);
         }
    }else{
         QString title="提示信息";
         QString Info="尝试保存文件失败";
         QMessageBox::information(this,title,Info);
    }
}

void MainWindow::on_act_Next_triggered()
{
    if(pages==context.text.size())
    {
        QString title="错误信息";
        QString Info="已经为最后一页，翻页操作失败";
        QMessageBox::critical(this,title,Info);
    }
    else{
        pages++;
        Show_Page();
    }
}


void MainWindow::on_act_Before_triggered()
{
    if(pages==1){
        QString title="错误信息";
        QString Info="已经为第一页，翻页操作失败";
        QMessageBox::critical(this,title,Info);
    }else{
        pages--;
        Show_Page();
    }
}


void MainWindow::on_act_Sure_triggered()
{
    QString title="翻看指定页文本";
    QString Info="请输入要查看文本的页码";
    int MaxPages=context.text.size();
    int MinPages=1;
    int stepValue=1;
    bool ok=false;
    int page=QInputDialog::getInt(this,title,Info,pages,MinPages,MaxPages,stepValue,&ok);
    if(ok)
    {
        pages=page;
        Show_Page();
    }
}

void MainWindow::on_act_Find_triggered()
{
    QString Title="查找";
    QString label="请输入要查找的文本: ";
    QString iniInput="English";
    QLineEdit::EchoMode e=QLineEdit::Normal;
    bool ok1=false;
    QString word=QInputDialog::getText(this,Title,label,e,iniInput,&ok1);
    if(ok1&&!word.isEmpty())
    {
        TextQuery find(context.text[pages - 1]);
        QString informations=QString::fromStdString(find.query(word.toStdString()));
        QString title="查找";
        QMessageBox::information(this,title,informations);
    }else{
        QString title="提示信息";
        QString Info="查找失败";
        QMessageBox::information(this,title,Info);
    }
}


void MainWindow::on_act_Replace_triggered()
{
    QString Title1="替换";
    QString label1="请输入要替换的单词：";
    QString iniInput1="ss";
    QLineEdit::EchoMode e1=QLineEdit::Normal;
    bool ok1=false;
    QString s1=QInputDialog::getText(this,Title1,label1,e1,iniInput1,&ok1);
    QString Title2="替换";
    QString label2="请输入替换后的单词：";
    QString iniInput2="ss";
    QLineEdit::EchoMode e2=QLineEdit::Normal;
    bool ok2=false;
    QString s2=QInputDialog::getText(this,Title2,label2,e2,iniInput2,&ok2);
    if(ok1&&ok2&&!s1.isEmpty()&&!s2.isEmpty())
    {
        bool ok=Replace(s1.toStdString(),s2.toStdString(),context,pages);
        if(ok==false)
        {
            QString title="提示信息";
            QString Info="替换失败,没有找到与之相匹配的文本";
            QMessageBox::information(this,title,Info);
        }else{
            QString title="提示信息";
            QString Info="替换成功";
            QMessageBox::information(this,title,Info);
        }
    }else{
        QString title="提示信息";
        QString Info="替换失败";
        QMessageBox::information(this,title,Info);
    }
    Show_Page();
}


void MainWindow::on_actMove_Pervious_triggered()
{
    QString title="输入行号对话框";
    QString Info="请输入要移动文本所在的行号";
    int MaxPages=context.text.size();
    int MinPages=1;
    int stepValue=1;
    bool ok=false;
    int line=QInputDialog::getInt(this,title,Info,pages,MinPages,MaxPages,stepValue,&ok);//得到移动单词所在行号

    QString title1="输入移动文本对话框";
    QString Info2="请输入要移动的文本";
    QString iniInput1="ss";
    QLineEdit::EchoMode e1=QLineEdit::Normal;
    bool ok1=false;
    QString word=QInputDialog::getText(this,title1,Info2,e1,iniInput1,&ok1);//得到要移动的单词

    QString title2="输入行号对话框";
    QString Info1="输入向上移动几行";
    int MaxPages1=context.text.size();
    int MinPages1=1;
    int stepValue1=1;
    bool ok2=false;
    int n=QInputDialog::getInt(this,title2,Info1,pages,MinPages1,MaxPages1,stepValue1,&ok2);//得到移动单词所在行号

    if(ok&&ok1&&ok2&&!word.isEmpty())
    {
        if(line<n)
        {
            QString title="提示信息";
            QString Info="超出边界，此操作无效";
            QMessageBox::information(this,title,Info);
        }else{
            bool ok=Edit_Page_Move_Pervious_Line(context,line,n,pages,word.toStdString());
            if(ok==true)
            {
                QString title="提示信息";
                QString Info="操作成功";
                QMessageBox::information(this,title,Info);
            }else{
                QString title="提示信息";
                QString Info="操作失败，请检查您输入的文本在此行是否存在";
                QMessageBox::information(this,title,Info);
            }
        }
    }else{
        QString title="错误信息";
        QString Info="输入数据不完整";
        QMessageBox::critical(this,title,Info);
    }
    Show_Page();
}


void MainWindow::on_actMove_next_triggered()
{
    QString title="输入行号对话框";
    QString Info="请输入要移动文本所在的行号";
     int MaxPages=context.text[pages-1].size();
    int MinPages=1;
    int stepValue=1;
    bool ok=false;
    int line=QInputDialog::getInt(this,title,Info,pages,MinPages,MaxPages,stepValue,&ok);//得到移动单词所在行号

    QString title1="输入移动文本对话框";
    QString Info2="请输入要移动的文本";
    QString iniInput1="ss";
    QLineEdit::EchoMode e1=QLineEdit::Normal;
    bool ok1=false;
    QString word=QInputDialog::getText(this,title1,Info2,e1,iniInput1,&ok1);//得到要移动的单词

    QString title2="输入行号对话框";
    QString Info1="输入向下移动几行";
    int MaxPages1=context.text[pages-1].size();
    int MinPages1=1;
    int stepValue1=1;
    bool ok2=false;
    int n=QInputDialog::getInt(this,title2,Info1,pages,MinPages1,MaxPages1,stepValue1,&ok2);//得到移动单词所在行号

    if(ok&&ok1&&ok2&&!word.isEmpty())
    {
        if(line - 1 + n >= context.text[pages - 1].size())
        {
            QString title="提示信息";
            QString Info="超出边界，此操作无效";
            QMessageBox::information(this,title,Info);
        }else{
            bool ok=Edit_Page_Move_Next_Line(context,line,n,pages,word.toStdString());
            if(ok==true)
            {
                QString title="提示信息";
                QString Info="操作成功";
                QMessageBox::information(this,title,Info);
            }else{
                QString title="提示信息";
                QString Info="操作失败，请检查您输入的文本在此行是否存在";
                QMessageBox::information(this,title,Info);
            }
        }
    }else{
        QString title="错误信息";
        QString Info="输入数据不完整";
        QMessageBox::critical(this,title,Info);
    }
    Show_Page();
}


void MainWindow::on_actMove_left_triggered()
{
    QString title="输入行号对话框";
    QString Info="请输入要移动文本所在的行号";
    int MaxPages=context.text[pages-1].size();
    int MinPages=1;
    int stepValue=1;
    bool ok=false;
    int line=QInputDialog::getInt(this,title,Info,pages,MinPages,MaxPages,stepValue,&ok);//得到移动单词所在行号

    QString title1="输入移动文本对话框";
    QString Info2="请输入要移动的文本";
    QString iniInput1="ss";
    QLineEdit::EchoMode e1=QLineEdit::Normal;
    bool ok1=false;
    QString word=QInputDialog::getText(this,title1,Info2,e1,iniInput1,&ok1);//得到要移动的单词

    QString title2="输入行号对话框";
    QString Info1="输入向左移动几列";
    int MaxPages1=context.text[pages-1].size();
    int MinPages1=1;
    int stepValue1=1;
    bool ok2=false;
    int n=QInputDialog::getInt(this,title2,Info1,pages,MinPages1,MaxPages1,stepValue1,&ok2);//得到移动单词所在行号

    if(ok&&ok1&&ok2&&!word.isEmpty())
    {
        bool ok=Edit_Page_Move_Left_Column(context,line,n,pages,word.toStdString());
        if(ok==false)
        {
            QString title="错误信息";
            QString Info="输入数据不完整or移动操作边界，此操作无效";
            QMessageBox::critical(this,title,Info);
        }else{
            QString title="提示信息";
            QString Info="操作成功";
            QMessageBox::information(this,title,Info);
        }
    }else{
        QString title="错误信息";
        QString Info="输入数据不完整";
        QMessageBox::critical(this,title,Info);
    }
    Show_Page();
}


void MainWindow::on_actMove_Right_triggered()
{
    QString title="输入行号对话框";
    QString Info="请输入要移动文本所在的行号";
    int MaxPages=context.text[pages-1].size();
    int MinPages=1;
    int stepValue=1;
    bool ok=false;
    int line=QInputDialog::getInt(this,title,Info,pages,MinPages,MaxPages,stepValue,&ok);//得到移动单词所在行号

    QString title1="输入移动文本对话框";
    QString Info2="请输入要移动的文本";
    QString iniInput1="ss";
    QLineEdit::EchoMode e1=QLineEdit::Normal;
    bool ok1=false;
    QString word=QInputDialog::getText(this,title1,Info2,e1,iniInput1,&ok1);//得到要移动的单词

    QString title2="输入行号对话框";
    QString Info1="输入向右移动几列";
    int MaxPages1=context.text[pages-1].size();
    int MinPages1=1;
    int stepValue1=1;
    bool ok2=false;
    int n=QInputDialog::getInt(this,title2,Info1,pages,MinPages1,MaxPages1,stepValue1,&ok2);//得到移动单词所在行号

    if(ok&&ok1&&ok2&&!word.isEmpty())
    {
        bool ok=Edit_Page_Move_Right_Column(context,line,n,pages,word.toStdString());
        if(ok==false)
        {
            QString title="错误信息";
            QString Info="输入数据不完整or移动操作边界，此操作无效";
            QMessageBox::critical(this,title,Info);
        }else{
            QString title="提示信息";
            QString Info="操作成功";
            QMessageBox::information(this,title,Info);
        }
    }else{
        QString title="错误信息";
        QString Info="输入数据不完整";
        QMessageBox::critical(this,title,Info);
    }
    Show_Page();
}


void MainWindow::on_act_Add_One_triggered()
{
    QString title="输入行号对话框";
    QString Info="请输入要添加文本所在的行号";
    int MaxPages=context.text[pages-1].size();
    int MinPages=1;
    int stepValue=1;
    bool ok=false;
    int line=QInputDialog::getInt(this,title,Info,pages,MinPages,MaxPages,stepValue,&ok);//行号

    QString title1="输入文本对话框";
    QString Info1="请输入要添加的文本(如果想添加空格，请输入""#"")";
    QString iniInput1="ss";
    QLineEdit::EchoMode e1=QLineEdit::Normal;
    bool ok1=false;
    QString word=QInputDialog::getText(this,title1,Info1,e1,iniInput1,&ok1);//得到要移动的单词
    if(word=="#")
    {
        word=" ";
    }

    QString title2="输入文本对话框";
    QString Info2="该文本插入在哪个单词后面";
    QString iniInput2="ss";
    QLineEdit::EchoMode e2=QLineEdit::Normal;
    bool ok2=false;
    QString s=QInputDialog::getText(this,title2,Info2,e2,iniInput2,&ok2);//得到要移动的单词

    if(ok&&ok1&&ok2&&!word.isEmpty()&&!s.isEmpty())
    {
        bool ok=Edit_Page_Add_One(context,line,pages,word.toStdString(),s.toStdString());
        if(ok==false)
        {
            QString title="错误信息";
            QString Info="请检查输入数据是否准确";
            QMessageBox::critical(this,title,Info);
        }else{
            QString title="提示信息";
            QString Info="操作成功";
            QMessageBox::information(this,title,Info);
        }
    }else{
        QString title="错误信息";
        QString Info="输入数据不完整";
        QMessageBox::critical(this,title,Info);
    }
     Show_Page();
}


void MainWindow::on_act_Add_Line_triggered()
{
     QString title="输入行号对话框";
     QString Info="请输入添加文本将要插入的行号";
     int MaxPages=context.text[pages-1].size();
     int MinPages=1;
     int stepValue=1;
     bool ok=false;
     int line=QInputDialog::getInt(this,title,Info,pages,MinPages,MaxPages,stepValue,&ok);//行号

     QString title1="输入文本对话框";
     QString Info1="请输入要添加的文本(单次添加不可超过20个文本)";
     QString iniInput1="ss";
     QLineEdit::EchoMode e1=QLineEdit::Normal;
     bool ok1=false;
     QString word=QInputDialog::getText(this,title1,Info1,e1,iniInput1,&ok1);//得到要移动的单词

     if(ok&&ok1&&!word.isEmpty())
     {
        vector<string>* group = new vector<string>;//用一个动态内存来暂时存放读进来的文本
        Change_Line(group,word.toStdString());
        Edit_Page_Add_Line(context,line,pages,group);
        delete group;
        QString title="提示信息";
        QString Info="操作成功";
        QMessageBox::information(this,title,Info);
     }else{
        QString title="错误信息";
        QString Info="输入数据不完整";
        QMessageBox::critical(this,title,Info);
     }
     Show_Page();
}


void MainWindow::on_act_Delete_One_triggered()
{
     QString title="输入行号对话框";
     QString Info="请输入删除文本所在的行号";
     int MaxPages=context.text[pages-1].size();
     int MinPages=1;
     int stepValue=1;
     bool ok=false;
     int line=QInputDialog::getInt(this,title,Info,pages,MinPages,MaxPages,stepValue,&ok);//行号

     QString title1="输入文本对话框";
     QString Info1="请输入要删除的文本(如果想删除空格，请输入""#"")";
     QString iniInput1="ss";
     QLineEdit::EchoMode e1=QLineEdit::Normal;
     bool ok1=false;
     QString word=QInputDialog::getText(this,title1,Info1,e1,iniInput1,&ok1);//得到要移动的单词
     if(word=="#")
     {
        word=" ";
     }

     if(ok&&ok1&&!word.isEmpty())
     {
        bool ok=Edit_Page_Delete_One(context,pages,line,word.toStdString());
        if(ok==true)
        {
            QString title="提示信息";
            QString Info="删除一个文本操作成功";
            QMessageBox::information(this,title,Info);
        }else{
            QString title="错误信息";
            QString Info="该页未找到与之对应的文本";
            QMessageBox::critical(this,title,Info);
        }
     }else{
        QString title="错误信息";
        QString Info="输入数据不完整";
        QMessageBox::critical(this,title,Info);
     }
     Show_Page();
}


void MainWindow::on_act_Delete_Line_triggered()
{
     QString title="输入行号对话框";
     QString Info="请输入删除行的行号";
     int MaxPages=context.text[pages-1].size();
     int MinPages=1;
     int stepValue=1;
     bool ok=false;
     int line=QInputDialog::getInt(this,title,Info,pages,MinPages,MaxPages,stepValue,&ok);//行号

     if(ok)
     {
        Edit_Page_Delete_Line(context,pages,line);
        QString title="提示信息";
        QString Info="删除一个文本操作成功";
        QMessageBox::information(this,title,Info);
     }else{
        QString title="错误信息";
        QString Info="输入数据不完整";
        QMessageBox::critical(this,title,Info);
     }
     Show_Page();
}




void MainWindow::on_act_Copy_triggered()
{
     clipBoard.group.clear();
     QString title="选择操作对话框";
     QString Info="1:复制一行中部分文本;2:复制多行文本;3:复制当前页内容";
     int MaxPages=3;
     int MinPages=1;
     int stepValue=1;
     bool ok=false;
     int choice=QInputDialog::getInt(this,title,Info,pages,MinPages,MaxPages,stepValue,&ok);//选择
     if(ok)
     {
        switch(choice){
        case 1:
        {
            QString title="输入行号对话框";
            QString Info="请输入要复制文本所在的行号";
            int MaxPages=context.text[pages-1].size();
            int MinPages=1;
            int stepValue=1;
            bool ok=false;
            int line=QInputDialog::getInt(this,title,Info,pages,MinPages,MaxPages,stepValue,&ok);//行号

            QString title1="复制单行文本对话框";
            QString Info1="请输入要复制的文本的开始单词";
            QString iniInput1="ss";
            QLineEdit::EchoMode e1=QLineEdit::Normal;
            bool ok1=false;
            QString begin=QInputDialog::getText(this,title1,Info1,e1,iniInput1,&ok1);

            QString title2="复制单行文本对话框";
            QString Info2="请输入要复制的文本的结束单词";
            QString iniInput2="ss";
            QLineEdit::EchoMode e2=QLineEdit::Normal;
            bool ok2=false;
            QString finish=QInputDialog::getText(this,title2,Info2,e2,iniInput2,&ok2);

            if(ok&&!begin.isEmpty()&&!finish.isEmpty())
            {
                clipBoard.Copy_One(context,pages,line,begin.toStdString(),finish.toStdString(),clipBoard);
                QString title="提示信息";
                QString Info="复制某行内文本操作成功";
                QMessageBox::information(this,title,Info);
            }else{
                QString title="错误信息";
                QString Info="输入数据不完整";
                QMessageBox::critical(this,title,Info);
            }
            break;
        }
        case 2:
        {
            QString title="输入行号对话框";
            QString Info="请输入要复制文本起始行号";
            int MaxPages=context.text[pages-1].size();
            int MinPages=1;
            int stepValue=1;
            bool ok=false;
            int begin=QInputDialog::getInt(this,title,Info,pages,MinPages,MaxPages,stepValue,&ok);//行号

            QString title1="输入行号对话框";
            QString Info1="请输入要复制文本结束行号";
            int MaxPages1=context.text[pages-1].size();
            int MinPages1=1;
            int stepValue1=1;
            bool ok1=false;
            int end=QInputDialog::getInt(this,title1,Info1,pages,MinPages1,MaxPages1,stepValue1,&ok1);//行号

            if(ok&&ok1)
            {
                clipBoard.Copy_Line(context,pages,begin,end,clipBoard);
                QString title="提示信息";
                QString Info="复制多行文本内容操作成功";
                QMessageBox::information(this,title,Info);
            }else{
                QString title="错误信息";
                QString Info="输入数据不完整";
                QMessageBox::critical(this,title,Info);
            }
            break;
        }
        case 3:
        {
            clipBoard.Copy_Page(context,pages,clipBoard);
            QString title="提示信息";
            QString Info="复制当前页文本内容操作成功";
            QMessageBox::information(this,title,Info);
            break;
        }
        default:
            break;
        }
     }
}


void MainWindow::on_act_Paste_triggered()
{
     if(clipBoard.group.size()==0)
     {
        QString title="错误信息";
        QString Info="剪切板未保存数据,当前不可粘贴";
        QMessageBox::critical(this,title,Info);
     }else{
        QString title="粘贴对话框";
        QString Info="请输入将要粘贴文本的位置的所在行号";
        int MaxPages=context.text[pages-1].size();
        int MinPages=1;
        int stepValue=1;
        bool ok=false;
        int line=QInputDialog::getInt(this,title,Info,pages,MinPages,MaxPages,stepValue,&ok);//行号

        QString title1="粘贴对话框";
        QString Info1="请输入粘贴在哪一个单词的前面";
        QString iniInput1="ss";
        QLineEdit::EchoMode e1=QLineEdit::Normal;
        bool ok1=false;
        QString begin=QInputDialog::getText(this,title1,Info1,e1,iniInput1,&ok1);

        bool ok2=clipBoard.Paste(context,pages,line,begin.toStdString(),clipBoard);

        if(ok2==true)
        {
            QString title="提示信息";
            QString Info="粘贴文本操作成功";
            QMessageBox::information(this,title,Info);
        }else{
            QString title="错误信息";
            QString Info="请检查输入数据是否准确";
            QMessageBox::critical(this,title,Info);
        }
     }
     Show_Page();
}


void MainWindow::on_act_Undo_triggered()
{
     if(context.voke[pages-1].count==1)
     {
        QString title="提示信息";
        QString Info="该页撤销操作失败,当前不可进行撤销操作";
        QMessageBox::information(this,title,Info);
     }else{
        context.voke[pages-1].Revoke(context.voke[pages-1],context,pages);
        QString title="提示信息";
        QString Info="撤销操作成功";
        QMessageBox::information(this,title,Info);
     }
     Show_Page();
}


void MainWindow::on_act_Redo_triggered()
{
     if(context.voke[pages-1].count>=context.voke[pages-1].v.size())
     {
        QString title="提示信息";
        QString Info="该页重做操作失败,当前不可进行重做操作";
        QMessageBox::information(this,title,Info);
     }else{
        context.voke[pages-1].Recove(context.voke[pages-1],context,pages);
        QString title="提示信息";
        QString Info="重做操作成功";
        QMessageBox::information(this,title,Info);
     }
     Show_Page();
}

