#include "login.h"
#include "ui_login.h"


//This piece of code below is a constructor
Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    //Add a picture using this
    //QPixmap pix("C/Url of picture");
    //ui->label_pic->setPixmap(pix);


    //In order to connect to the database we must use the driver QSQLITE otherwise nothing will happen
    //mydb = QSqlDatabase::addDatabase("QSQLITE");
    //mydb.setDatabaseName("C:/sqlite3/database.sqlite");

    if(!connOpen())
    {
        ui->label->setText("Failed to open the database");
    }
    else
    {
        ui->label->setText("Connected...");
    }
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QString username,password;
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_Password->text();

    if(!connOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }

    //The connOpen() method (or function) is used to open a connection to the SQLite database
    connOpen();
    QSqlQuery qry;
    qry.prepare("select * from employeinfo1 where username='"+username+"' and password='"+password+"'");

    if(qry.exec());
    {
        int count = 0;
        while(qry.next())
        {
            count++;
        }
        if(count == 1)
        {
            ui->label->setText("username and password is correct");
            //if the username and password is correct we want to grant acces to the next window by hiding the current one like so:
            connClose();
            this->hide();
            EmployeeInfo employeeinfo;
            employeeinfo.setModal(true);
            employeeinfo.exec();
        }
        if(count > 1)
        {
            ui->label->setText("Duplicate username and password");
        }
        if(count < 1)
        {
            ui->label->setText("username and password is not correct");
        }
    }
}
