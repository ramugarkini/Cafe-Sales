#ifndef STAFFWIDGET_H
#define STAFFWIDGET_H

#include "const.h"
#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
    class StaffWidget;
}

class StaffWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StaffWidget(QWidget *parent = nullptr);
    ~StaffWidget();

private:
    Ui::StaffWidget *ui;
    QSqlQuery *qry;
    QSqlQueryModel *model;
    void refreshStaffTable();

private slots:
    void on_pushButtonStaff_clicked();
};

#endif // STAFFWIDGET_H
