#include "const.h"
#include "outbound3widget.h"
#include "ui_outbound3widget.h"
#include <QtDebug>

Outbound3Widget::Outbound3Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Outbound3Widget),
    qry(new QSqlQuery),
    modelOutbound3(new QSqlQueryModel),
    modelCategory(new QSqlQueryModel)
{
    qDebug() << "[Outbound3 Widget] Constructing...";
    ui->setupUi(this);
    // ui->lineEditNameKey->setMaxLength(ITEMNAME_MAX_LEN);
    ui->lineEditOrderIDKey->setMaxLength(ITEMNAME_MAX_LEN);
    ui->tableViewOutbound3->horizontalHeader()->
        setSectionResizeMode(QHeaderView::Stretch);

    refreshOutbound3TableView();
    refreshCategoryComboBox();
}

Outbound3Widget::~Outbound3Widget()
{
    qDebug() << "[Outbound3 Widget] Destructing...";
    delete ui;
    delete qry;
    delete modelOutbound3;
    delete modelCategory;
}

void Outbound3Widget::on_pushButtonQuery_clicked()
{
    qDebug() << "[Outbound3 Widget] Query button clicked...";
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

    refreshOutbound3TableView(clause);
}

void Outbound3Widget::refreshOutbound3TableView(const QString& qry_clause/*=""*/)
{
    qDebug() << "Refreshing outbound3 table view...";
    QString s = "SELECT REPLACE(REPLACE(REPLACE(otime, '-', ''), ' ', ''), ':', '') as %1, otime as %2, "
        "name AS %3, cate AS %4, amount as %5, time as %6 "
        "FROM Outbound WHERE otime IS NOT NULL";
    QString view_outbound3 = s.arg(
        tr("OrderID"), tr("OrderTime"), tr("Name"), tr("Category"), tr("Quantity"), tr("CartEntryTime")) + qry_clause;
    qDebug() << view_outbound3;
    modelOutbound3->setQuery(view_outbound3);
    ui->tableViewOutbound3->setModel(modelOutbound3);
}

void Outbound3Widget::refreshCategoryComboBox()
{
    qDebug() << "Refreshing category combo box...";
    QString get_distinct_cate = "SELECT DISTINCT cate FROM Outbound WHERE otime IS NOT NULL";
    modelCategory->setQuery(get_distinct_cate);
    ui->comboBoxCategory->setModel(modelCategory);
}
