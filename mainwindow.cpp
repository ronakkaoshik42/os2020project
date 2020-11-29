#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include"sub_window.h"
#include "file_dialog.h"

extern int num;
extern int ch;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->QLineEdit_Process_Num->setPlaceholderText("input number...");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Input_clicked()
{
    num=1;

    sub_window sub_window;
    sub_window.setModal(true);
    sub_window.exec();
}



void MainWindow::on_pushButton_clicked()
{
    file_Dialog file_window;
    file_window.setModal(true);
    file_window.exec();
}
