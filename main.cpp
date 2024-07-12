#include "const.h"
#include "logindialog.h"
#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);  // Create the QApplication object first

    QSqlDatabase db = QSqlDatabase::addDatabase(DB_TYPE);
    db.setDatabaseName(DB_PATH);
    if (!db.open())
    {
        qDebug() << "Fails opening database:" << db.lastError();
        return -1;
    }

    LoginDialog ld;

    if (ld.exec() == QDialog::Accepted)
    {
        MainWindow mw;
        mw.show();
        int result = app.exec(); // Store the result of app.exec()
        db.close(); // Ensure the database is closed properly
        return result; // Return the result
    }
    else
    {
        db.close(); // Ensure the database is closed properly
        return 0; // Return 0 to indicate normal termination
    }
}
