#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<iostream>
#include<cstdlib>
#include<queue>
#include<cstdio>
using namespace std;

typedef struct process
{
   int id,at,bt,ct,it,st,ft,pr,cpu_count,io_count,cpu_flag=1,rt,io_flag=0,res_t;

   float wt,tat;

   QString color;

}process;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Input_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
