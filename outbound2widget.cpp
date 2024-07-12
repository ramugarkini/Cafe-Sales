#include "const.h"
#include "outbound2widget.h"
#include "ui_outbound2widget.h"
#include <QtDebug>

Outbound2Widget::Outbound2Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Outbound2Widget),
    qry(new QSqlQuery),
    modelOutbound2(new QSqlQueryModel),
    modelCategory(new QSqlQueryModel)
{
    qDebug() << "[Outbound2 Widget] Constructing...";
    ui->setupUi(this);
    // ui->lineEditNameKey->setMaxLength(ITEMNAME_MAX_LEN);
    ui->lineEditOrderIDKey->setMaxLength(ITEMNAME_MAX_LEN);
    ui->tableViewOutbound2->horizontalHeader()->
        setSectionResizeMode(QHeaderView::Stretch);

    refreshOutbound2TableView();
    refreshCategoryComboBox();
}

Outbound2Widget::~Outbound2Widget()
{
    qDebug() << "[Outbound2 Widget] Destructing...";
    delete ui;
    delete qry;
    delete modelOutbound2;
    delete modelCategory;
}

void Outbound2Widget::on_pushButtonQuery_clicked()
{
    qDebug() << "[Outbound2 Widget] Query button clicked...";
    // QString nameKey = ui->lineEditNameKey->text();
    QString OrderIDKey = ui->lineEditOrderIDKey->text();
    QString category = ui->comboBoxCategory->currentText();
    // bool searchName = ui->checkBoxName->isChecked();
    bool searchOrderID = ui->checkBoxOrderID->isChecked();
    bool categoryOnly = ui->checkBoxCate->isChecked();

    QString clause = "";  // Prepare query where cluase if needed.
    // QString nameCondition = QString("name LIKE '%%1%'").arg(nameKey);
    QString OrderIDCondition = QString("REPLACE(REPLACE(REPLACE(otime, '-', ''), ' ', ''), ':', '') LIKE '%%1%'").arg(OrderIDKey);
    QString cateCondition = QString("cate = '%1'").arg(category);
    // if (searchName)
    if (searchOrderID)
    {
        // clause += " AND " + nameCondition;
        clause += " AND " + OrderIDCondition;
        if (categoryOnly) clause += " AND " + cateCondition;
    }
    else if (categoryOnly) clause += " AND " + cateCondition;

    refreshOutbound2TableView(clause);
}

void Outbound2Widget::refreshOutbound2TableView(const QString& qry_clause/*=""*/)
{
    qDebug() << "Refreshing outbound2 table view...";
    QString s = "SELECT name AS %1, cate AS %2, "
        "amount as %3, time as %4, "
        "REPLACE(REPLACE(REPLACE(otime, '-', ''), ' ', ''), ':', '') as %5, otime as %6 "
        "FROM Outbound WHERE otime IS NOT NULL";
    QString view_outbound2 = s.arg(
        tr("Name"), tr("Category"), tr("Amount"), tr("Time"), tr("OrderID"), tr("OrderTime")) + qry_clause;
    qDebug() << view_outbound2;
    modelOutbound2->setQuery(view_outbound2);
    ui->tableViewOutbound2->setModel(modelOutbound2);
}

void Outbound2Widget::refreshCategoryComboBox()
{
    qDebug() << "Refreshing category combo box...";
    QString get_distinct_cate = "SELECT DISTINCT cate FROM Outbound WHERE otime IS NOT NULL";
    modelCategory->setQuery(get_distinct_cate);
    ui->comboBoxCategory->setModel(modelCategory);
}
