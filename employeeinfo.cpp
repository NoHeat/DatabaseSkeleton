#include "employeeinfo.h"
#include "ui_employeeinfo.h"
#include <QMessageBox>

EmployeeInfo::EmployeeInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeInfo)
{
    ui->setupUi(this);

     Login conn;

    if(!conn.connOpen())
    {
        ui->label_sec_status->setText("Failed to open the database");
    }
    else
    {
        ui->label_sec_status->setText("Connected...");
    }
}

EmployeeInfo::~EmployeeInfo()
{
    delete ui;
}

void EmployeeInfo::on_pushButton_clicked()
{
    Login conn;
    QString eid,name,surname,age;
    eid = ui->lineEdit_eid->text();
    name = ui->lineEdit_Name->text();
    surname = ui->lineEdit_Surname->text();
    age = ui->lineEdit_Age->text();

    if(!conn.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }

    //The connOpen() method (or function) is used to open a connection to the SQLite database
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into employeinfo1 (eid,name,surname,age) values ('"+eid+"','"+name+"','"+surname+"','"+age+"')");

    if(qry.exec())
    {
       //This message box will inform the user that the data was succesfully written and saved to the database
        QMessageBox::information(this,tr("Save"),tr("Saved"));
        //This is closing the connection to the database when the function to write into it was sucessfully executed
        conn.connClose();
    }
    else
    {
        //This message will show that there was an error during execution
        QMessageBox::critical(this,tr("Error"),qry.lastError().text());
    }
}

void EmployeeInfo::on_pushButton_Edit_clicked()
{
    Login conn;
    QString eid,name,surname,age;
    eid = ui->lineEdit_eid->text();
    name = ui->lineEdit_Name->text();
    surname = ui->lineEdit_Surname->text();
    age = ui->lineEdit_Age->text();

    if(!conn.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }

    //The connOpen() method (or function) is used to open a connection to the SQLite database
    conn.connOpen();
    QSqlQuery qry;

    //To let SQLite where to add the values we use where
    qry.prepare("update employeinfo1 set eid='"+eid+"',name='"+name+"',surname='"+surname+"',age='"+age+"' where eid='"+eid+"'");

    if(qry.exec())
    {
       //This message box will inform the user that the data was succesfully written and saved to the database
        QMessageBox::information(this,tr("Edit"),tr("Field Updated"));
        //This is closing the connection to the database when the function to write into it was sucessfully executed
        conn.connClose();
    }
    else
    {
        //This message will show that there was an error during execution
        QMessageBox::critical(this,tr("Error"),qry.lastError().text());
    }
}

void EmployeeInfo::on_pushButton_2_clicked()
{
    Login conn;
    QString eid,name,surname,age;
    eid = ui->lineEdit_eid->text();
    name = ui->lineEdit_Name->text();
    surname = ui->lineEdit_Surname->text();
    age = ui->lineEdit_Age->text();

    if(!conn.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }

    //The connOpen() method (or function) is used to open a connection to the SQLite database
    conn.connOpen();
    QSqlQuery qry;

    //This is an example of how to delete from the database by using the employee ID as reference
    qry.prepare("delete from employeinfo1 where eid='"+eid+"'");

    if(qry.exec())
    {
       //Use a QmessageBox to alert the user they are about to delete the entry

        //This message box will inform the user that the data was succesfully written and saved to the database
        QMessageBox::information(this,tr("Delete"),tr("Deleted"));
        //This is closing the connection to the database when the function to write into it was sucessfully executed
        conn.connClose();
    }
    else
    {
        //This message will show that there was an error during execution
        QMessageBox::critical(this,tr("Error"),qry.lastError().text());
    }
}

void EmployeeInfo::on_pushButton_3_clicked()
{
    //table view code here
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    //Change this code here to get the values necessary
    qry->prepare("select * from employeinfo1");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

    conn.connClose();
    qDebug() << (modal->rowCount());

}


void EmployeeInfo::on_pushButtonLoadList_clicked()
{
    //THIS PART OF THE CODE IS NOT WORKING


    //List view code here
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    //Change this code here to get the values necessary
    qry->prepare("select name from employeinfo1"); //eid or surname will work to load other columns
    qry->exec();
    modal->setQuery(*qry);
    ui->listView->setModel(modal);

    conn.connClose();
    qDebug() << (modal->rowCount());
}
