#include "file_dialog.h"
#include "ui_file_dialog.h"
#include "file_dialog.h"
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include "mainwindow.h"

file_Dialog::file_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::file_Dialog)
{
    ui->setupUi(this);
}

file_Dialog::~file_Dialog()
{
    delete ui;
}
