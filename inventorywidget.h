#ifndef INVENTORYWIDGET_H
#define INVENTORYWIDGET_H

#include "const.h"
#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
    class InventoryWidget;
}

class InventoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InventoryWidget(QWidget *parent = nullptr);
    ~InventoryWidget();

private:
    Ui::InventoryWidget *ui;
    QSqlQuery *qry;
    QSqlQueryModel *model;
    QSqlQueryModel *modelName;

signals:
    void inbounded();
    void outbounded();

private slots:
    void on_pushButtonInbound_clicked();
    void on_pushButtonOutbound_clicked();

public slots:
    void refreshInventoryTable();
    void refreshOutNameComboBox();
};

#endif // INVENTORYWIDGET_H
