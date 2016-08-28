#ifndef LOGIN_H
#define LOGIN_H


#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "employeeinfo.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen()
    {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/Sqlite_DB2/sqlite3/database.sqlite");

        if(!mydb.open())
        {
            qDebug() << ("Failed to open the database");
            return false;
        }
        else
        {
            qDebug() << ("Connected...");
            return true;
        }
    }

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;

};

#endif // LOGIN_H
