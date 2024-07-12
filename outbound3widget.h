#ifndef OUTBOUND3WIDGET_H
#define OUTBOUND3WIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
    class Outbound3Widget;
}

class Outbound3Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Outbound3Widget(QWidget *parent = nullptr);
    ~Outbound3Widget();

private:
    Ui::Outbound3Widget *ui;
    QSqlQuery *qry;
    QSqlQueryModel *modelOutbound3;
    QSqlQueryModel *modelCategory;
    void refreshOutbound3TableView(const QString& qry_clause = "");

public slots:
    void refreshCategoryComboBox();
    void on_pushButtonQuery_clicked();
};

#endif // OUTBOUND3WIDGET_H
