#ifndef EMPLOYEEINFO_H
#define EMPLOYEEINFO_H

#include <QDialog>
#include "login.h"

namespace Ui {
class EmployeeInfo;
}

class EmployeeInfo : public QDialog
{
    Q_OBJECT

public:

    explicit EmployeeInfo(QWidget *parent = 0);
    ~EmployeeInfo();

private slots:
    void on_pushButton_clicked(); //Save

    void on_pushButton_Edit_clicked(); //Update

    void on_pushButton_2_clicked(); //Delete

    void on_pushButton_3_clicked(); //load table (this one is good)

    void on_pushButtonLoadList_clicked(); //Load List

private:
    Ui::EmployeeInfo *ui;
};

#endif // EMPLOYEEINFO_H
