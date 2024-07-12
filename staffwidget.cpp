#include "staffwidget.h"
#include "ui_staffwidget.h"
#include <QtDebug>

StaffWidget::StaffWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaffWidget),
    qry(new QSqlQuery),
    model(new QSqlQueryModel)
{
    qDebug() << "[Staff Widget] Constructing...";
    ui->setupUi(this);
    ui->lineEditStaffName->setMaxLength(STAFFNAME_MAX_LEN);
    ui->spinBoxSalary->setMaximum(STAFF_IO_MAX);
    ui->spinBoxShift->setMaximum(STAFF_IO_MAX);
    ui->tableViewStaff->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    // If no staff table yet, create it.
    QString s = "CREATE TABLE IF NOT EXISTS Staff ("
        "name char(%1), salary int, shift int, time char(20) PRIMARY KEY)";
    QString create_staff_table = s.arg(
        QString::number(STAFFNAME_MAX_LEN));
    qDebug() << create_staff_table << qry->exec(create_staff_table);

    refreshStaffTable();
}

StaffWidget::~StaffWidget()
{
    qDebug() << "[Staff Widget] Destructing...";
    delete ui;
    delete qry;
    delete model;
}

void StaffWidget::on_pushButtonStaff_clicked()
{
    qDebug() << "[Staff Widget] Clicked add staff button...";
    QString name = ui->lineEditStaffName->text();
    int salary = ui->spinBoxSalary->value();
    int shift = ui->spinBoxShift->value();

    if (!(name.length()))
    {
        qDebug() << "Field no input, won't add staff.";
        return;
    }

    QString s = "INSERT INTO Staff VALUES ('%1', %2, %3, datetime('now', 'localtime'))";
    QString add_staff = s.arg(name, QString::number(salary), QString::number(shift));
    bool success = qry->exec(add_staff);
    qDebug() << add_staff << success;
    if (success) refreshStaffTable();
}

void StaffWidget::refreshStaffTable()
{
    qDebug() << "Refreshing staff table...";
    QString s = "SELECT name AS %1, salary AS %2, shift AS %3 FROM Staff";
    QString view_staff = s.arg(tr("Name"), tr("Salary"), tr("Shift"));
    model->setQuery(view_staff);
    ui->tableViewStaff->setModel(model);
}
