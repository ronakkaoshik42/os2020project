#ifndef FILE_DIALOG_H
#define FILE_DIALOG_H

#include <QDialog>

namespace Ui {
class file_Dialog;
}

class file_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit file_Dialog(QWidget *parent = nullptr);
    ~file_Dialog();

private slots:

private:
    Ui::file_Dialog *ui;
};

#endif // FILE_DIALOG_H
