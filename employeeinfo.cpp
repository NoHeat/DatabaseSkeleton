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

    //To let SQLite know where to add the values we use
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
    //ui->listView->setModel(modal);
    ui->tableView->setModel(modal);


    conn.connClose();
    qDebug() << (modal->rowCount());

}


void EmployeeInfo::on_pushButtonLoadList_clicked()
{



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
    ui->comboBox->setModel(modal);

    conn.connClose();
    qDebug() << (modal->rowCount());
}

void EmployeeInfo::on_comboBox_currentIndexChanged(const QString &arg1)
{
    //The idea behind this code is to grab the current name displayed and put it in the name variable
    QString name = ui->comboBox->currentText();
    //conn is the loging object to open and close the conection to the database
    Login conn;


    if(!conn.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }

    //The connOpen() method (or function) is used to open a connection to the SQLite database
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from employeinfo1 where name='"+name+"'");

    if(qry.exec())
    {
       while(qry.next())
       {
         //From the database each colunm has an index. The index starts at 0. To specify eid we need colunm 0.
         //To specify name then the value is 1, surname would have value 2, and so on... going from left to right.

           ui->lineEdit_eid->setText(qry.value(0).toString());
           ui->lineEdit_Name->setText(qry.value(1).toString());
           ui->lineEdit_Surname->setText(qry.value(2).toString());
           ui->lineEdit_Age->setText(qry.value(3).toString());
       }
        //This is closing the connection to the database when the function to write into it was sucessfully executed
        conn.connClose();
    }
    else
    {
        //This message will show that there was an error during execution
        QMessageBox::critical(this,tr("Error"),qry.lastError().text());
    }


}

void EmployeeInfo::on_pushButton_LoadData_clicked()
{

    //Load Data code
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    //Change this code here to get the values necessary
    qry->prepare("select * from employeinfo1"); //eid or surname will work to load other columns
    qry->exec();
    modal->setQuery(*qry);

    /*Once we get our table going with all the information we need we have to modify this code so that
     * it will load all views models.*/

    //ui->listView->setModel(modal);
    //ui->comboBox->setModel(modal);


    //Right now only table view works. When clickin Load Data it will put the information on the table.
     ui->tableView->setModel(modal);

    conn.connClose();
    qDebug() << (modal->rowCount());
}

void EmployeeInfo::on_tableView_activated(const QModelIndex &index)
{
    //takes index selected from table view and converts it to a string stored in variable val
    QString val = ui->tableView->model()->data(index).toString();



    //conn is the loging object to open and close the conection to the database
    Login conn;


    if(!conn.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }

    //The connOpen() method (or function) is used to open a connection to the SQLite database
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from employeinfo1 where eid='"+val+"' or name='"+val+"' or surname='"+val+"' or age='"+val+"'");

    if(qry.exec())
    {
       while(qry.next())
       {
         //From the database each colunm has an index. The index starts at 0. To specify eid we need colunm 0.
         //To specify name then the value is 1, surname would have value 2, and so on... going from left to right.

           ui->lineEdit_eid->setText(qry.value(0).toString());
           ui->lineEdit_Name->setText(qry.value(1).toString());
           ui->lineEdit_Surname->setText(qry.value(2).toString());
           ui->lineEdit_Age->setText(qry.value(3).toString());
       }
        //This is closing the connection to the database when the function to write into it was sucessfully executed
        conn.connClose();
    }
    else
    {
        //This message will show that there was an error during execution
        QMessageBox::critical(this,tr("Error"),qry.lastError().text());
    }

}

void EmployeeInfo::on_listView_activated(const QModelIndex &index)
{
    //takes index selected from table view and converts it to a string stored in variable val
    QString val = ui->listView->model()->data(index).toString();



    //conn is the loging object to open and close the conection to the database
    Login conn;


    if(!conn.connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }

    //The connOpen() method (or function) is used to open a connection to the SQLite database
    conn.connOpen();
    QSqlQuery qry;

    //listView can only show 1 item. This is why we can only use a value here. This can be changed as necessary.
    qry.prepare("select * from employeinfo1 where name='"+val+"'");

    if(qry.exec())
    {
       while(qry.next())
       {
         //From the database each colunm has an index. The index starts at 0. To specify eid we need colunm 0.
         //To specify name then the value is 1, surname would have value 2, and so on... going from left to right.

           ui->lineEdit_eid->setText(qry.value(0).toString());
           ui->lineEdit_Name->setText(qry.value(1).toString());
           ui->lineEdit_Surname->setText(qry.value(2).toString());
           ui->lineEdit_Age->setText(qry.value(3).toString());
       }
        //This is closing the connection to the database when the function to write into it was sucessfully executed
        conn.connClose();
    }
    else
    {
        //This message will show that there was an error during execution
        QMessageBox::critical(this,tr("Error"),qry.lastError().text());
    }

}
