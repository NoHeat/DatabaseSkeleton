#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    /*SQLite can only support one connection to the database at a time. This is why while writing or reading from the database
     * a command to close it must come afterwards. If the database is not closed a memory leak occurs and a warning will be generated such
     * that the database won't respond because there are two active connections.*/

    QApplication a(argc, argv);
    Login w;
    w.show();

    return a.exec();
}
