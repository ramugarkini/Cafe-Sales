#include "const.h"
#include "outbound2widget.h"
#include "ui_outbound2widget.h"
#include <QSqlQueryModel>
#include <QSqlRecord>
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

    // refreshOutbound2TableView();
    // refreshCategoryComboBox();
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
    // QString category = ui->comboBoxCategory->currentText();
    // bool searchName = ui->checkBoxName->isChecked();
    // bool searchOrderID = ui->checkBoxOrderID->isChecked();
    // bool categoryOnly = ui->checkBoxCate->isChecked();

    QString clause = "";  // Prepare query where cluase if needed.
    // QString nameCondition = QString("name LIKE '%%1%'").arg(nameKey);
    QString OrderIDCondition = QString("REPLACE(REPLACE(REPLACE(otime, '-', ''), ' ', ''), ':', '') = '%1'").arg(OrderIDKey);
    // QString cateCondition = QString("cate = '%1'").arg(category);
    // if (searchName)
    /*if (searchOrderID)
    {
        // clause += " AND " + nameCondition;
        clause += " AND " + OrderIDCondition;
        // if (categoryOnly) clause += " AND " + cateCondition;
    }*/
    clause += " AND " + OrderIDCondition;
    // else if (categoryOnly) clause += " AND " + cateCondition;

    refreshOutbound2TableView(clause);
}

void Outbound2Widget::refreshOutbound2TableView(const QString& qry_clause/*=""*/)
{
    qDebug() << "Refreshing outbound2 table view...";
    QString s = "SELECT REPLACE(REPLACE(REPLACE(otime, '-', ''), ' ', ''), ':', '') as %1, "
        "otime as %2, "
        "SUM(quantity) as %3, SUM(ppq * quantity) as %4 "
        "FROM Outbound WHERE otime IS NOT NULL";
    QString view_outbound2_od = s.arg(
        tr("OrderID"), tr("OrderTime"), tr("OrderTotalQty"), tr("OrderTotalPrice")) + qry_clause;
    qDebug() << view_outbound2_od;
    modelOutbound2->setQuery(view_outbound2_od);

    if (modelOutbound2->rowCount() > 0) {
        QString orderID = modelOutbound2->record(0).value("OrderID").toString();
        QString orderTime = modelOutbound2->record(0).value("OrderTime").toString();
        QString orderTotalQty = modelOutbound2->record(0).value("OrderTotalQty").toString();
        QString orderTotalPrice = modelOutbound2->record(0).value("OrderTotalPrice").toString();
        ui->labelOrderIDLabel->setText("Order ID:");
        ui->labelOrderIDValue->setText(orderID);
        ui->labelOrderTimeLabel->setText("Order Time:");
        ui->labelOrderTimeValue->setText(orderTime);
        ui->labelOrderTotalQtyL->setText("Total Quantity:");
        ui->labelOrderTotalQty->setText(orderTotalQty);
        ui->labelOrderTotalPriceL->setText("Total Price:");
        ui->labelOrderTotalPrice->setText(orderTotalPrice);
    } else {
        ui->labelOrderIDLabel->clear();
        ui->labelOrderIDValue->clear();
        ui->labelOrderTimeLabel->clear();
        ui->labelOrderTimeValue->clear();
        ui->labelOrderTotalQtyL->clear();
        ui->labelOrderTotalQty->clear();
        ui->labelOrderTotalPriceL->clear();
        ui->labelOrderTotalPrice->clear();
    }

    s = "SELECT name AS %1, cate AS %2, ppq as %3, quantity as %4, (ppq * quantity) AS %5 "
        "FROM Outbound WHERE otime IS NOT NULL";
    QString view_outbound2 = s.arg(
        tr("Name"), tr("Category"), tr("PricePerQuantity"), tr("Quantity"), tr("TotalPrice")) + qry_clause;
    qDebug() << view_outbound2;
    modelOutbound2->setQuery(view_outbound2);

    ui->tableViewOutbound2->setModel(modelOutbound2);
}

void Outbound2Widget::refreshOrderIDLineEdit()
{
    qDebug() << "Refreshing OrderID line edit...";

    QString s = "SELECT REPLACE(REPLACE(REPLACE(otime, '-', ''), ' ', ''), ':', '') as %1 "
    "FROM Outbound "
    "WHERE otime IS NOT NULL "
    "ORDER BY otime DESC LIMIT 1";
    QString get_last_otime = s.arg(tr("OrderID"));
    modelCategory->setQuery(get_last_otime);
    // Check if the query returned a result
    if (modelCategory->rowCount() > 0)
    {
        // Retrieve the last OrderID value
        QString lastOtime = modelCategory->record(0).value("OrderID").toString();
        ui->lineEditOrderIDKey->setText(lastOtime);
    }
    else
    {
        // If no result, clear the line edit
        ui->lineEditOrderIDKey->clear();
    }
}

/*void Outbound2Widget::refreshCategoryComboBox()
{
    qDebug() << "Refreshing category combo box...";
    QString get_distinct_cate = "SELECT DISTINCT cate FROM Outbound WHERE otime IS NOT NULL";
    modelCategory->setQuery(get_distinct_cate);
    ui->comboBoxCategory->setModel(modelCategory);
}*/
