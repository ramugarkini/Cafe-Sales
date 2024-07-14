#ifndef OUTBOUNDWIDGET_H
#define OUTBOUNDWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
    class OutboundWidget;
}

class OutboundWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OutboundWidget(QWidget *parent = nullptr);
    ~OutboundWidget();

private:
    Ui::OutboundWidget *ui;
    QSqlQuery *qry;
    QSqlQueryModel *modelOutbound;
    QSqlQueryModel *modelOutbound2;
    QSqlQueryModel *modelCategory;
    void refreshOutboundTableView(const QString& qry_clause = "");

signals:
    void outbounded();
    void outboundedd();

public slots:
    void refreshCategoryComboBox();
    void refreshOrderTotalLabel();
    void on_pushButtonQuery_clicked();
    void on_pushButtonOutbound_clicked();
    void on_pushButtonOutboundRemoveLast_clicked();
};

#endif // OUTBOUNDWIDGET_H