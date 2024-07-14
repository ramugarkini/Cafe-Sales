#ifndef OUTBOUND2WIDGET_H
#define OUTBOUND2WIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
    class Outbound2Widget;
}

class Outbound2Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Outbound2Widget(QWidget *parent = nullptr);
    ~Outbound2Widget();

private:
    Ui::Outbound2Widget *ui;
    QSqlQuery *qry;
    QSqlQueryModel *modelOutbound2;
    QSqlQueryModel *modelCategory;
    void refreshOutbound2TableView(const QString& qry_clause = "");

public slots:
    // void refreshCategoryComboBox();
    void on_pushButtonQuery_clicked();
    void refreshOrderIDLineEdit();
};

#endif // OUTBOUND2WIDGET_H
