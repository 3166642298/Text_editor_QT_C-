#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"Context.h"
#include"ClipBoard.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void Show_Page();
    void Init_Button(bool ok);
    ~MainWindow();

private slots:
    void on_act_New_triggered();

    void on_act_Close_triggered();

    void on_act_Next_triggered();

    void on_act_Before_triggered();

    void on_act_Sure_triggered();

    void on_act_Open_triggered();

    void on_act_Save_triggered();

    void on_act_Find_triggered();

    void on_act_Replace_triggered();

    void on_actMove_Pervious_triggered();

    void on_actMove_next_triggered();

    void on_actMove_left_triggered();

    void on_actMove_Right_triggered();

    void on_act_Add_One_triggered();

    void on_act_Add_Line_triggered();

    void on_act_Delete_One_triggered();

    void on_act_Delete_Line_triggered();

    void on_act_Copy_triggered();

    void on_act_Paste_triggered();

    void on_act_Undo_triggered();

    void on_act_Redo_triggered();

private:
    Ui::MainWindow *ui;
    Context context;
    ClipBoard clipBoard;
    int pages;
};
#endif // MAINWINDOW_H
