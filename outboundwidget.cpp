#include "const.h"
#include "outboundwidget.h"
#include "ui_outboundwidget.h"
#include <QtDebug>

OutboundWidget::OutboundWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutboundWidget),
    qry(new QSqlQuery),
    modelOutbound(new QSqlQueryModel),
    modelCategory(new QSqlQueryModel)
{
    qDebug() << "[Outbound Widget] Constructing...";
    ui->setupUi(this);
    ui->lineEditNameKey->setMaxLength(ITEMNAME_MAX_LEN);
    ui->tableViewOutbound->horizontalHeader()->
        setSectionResizeMode(QHeaderView::Stretch);

    refreshOutboundTableView();
    refreshCategoryComboBox();
}

OutboundWidget::~OutboundWidget()
{
    qDebug() << "[Outbound Widget] Destructing...";
    delete ui;
    delete qry;
    delete modelOutbound;
    delete modelCategory;
}

void OutboundWidget::on_pushButtonQuery_clicked()
{
    qDebug() << "[Outbound Widget] Query button clicked...";
    QString nameKey = ui->lineEditNameKey->text();
    QString category = ui->comboBoxCategory->currentText();
    bool searchName = ui->checkBoxName->isChecked();
    bool categoryOnly = ui->checkBoxCate->isChecked();

    QString clause = "";  // Prepare query where cluase if needed.
    QString nameCondition = QString("name LIKE '%%1%'").arg(nameKey);
    QString cateCondition = QString("cate = '%1'").arg(category);
    if (searchName)
    {
        clause += " AND " + nameCondition;
        if (categoryOnly) clause += " AND " + cateCondition;
    }
    else if (categoryOnly) clause += " AND " + cateCondition;

    refreshOutboundTableView(clause);
}

void OutboundWidget::on_pushButtonOutbound2_clicked()
{
    qDebug() << "[Inventory Widget] Outbound2 button clicked...";

    // Confirm Order by SET otime
    QString s = "UPDATE Outbound SET otime = datetime('now', 'localtime') WHERE otime IS NULL";
    QString outbound2 = s;
    bool success = qry->exec(outbound2);
    qDebug() << outbound2 << success;
    if (success)
    {
        refreshOutboundTableView();
        outbounded();
    }
}

void OutboundWidget::refreshOutboundTableView(const QString& qry_clause/*=""*/)
{
    qDebug() << "Refreshing outbound table view...";
    QString s = "SELECT time as %1, name AS %2, cate AS %3, "
        "ppq as %4, quantity as %5, (ppq * quantity) AS %6  "
        "FROM Outbound WHERE otime IS NULL";
    QString view_outbound = s.arg(
        tr("CartEntryTime"), tr("Name"), tr("Category"), tr("PricePerQuantity"), tr("Quantity"), tr("TotalPrice")) + qry_clause;
    qDebug() << view_outbound;
    modelOutbound->setQuery(view_outbound);
    ui->tableViewOutbound->setModel(modelOutbound);
}

void OutboundWidget::refreshCategoryComboBox()
{
    qDebug() << "Refreshing category combo box...";
    QString get_distinct_cate = "SELECT DISTINCT cate FROM Outbound WHERE otime IS NULL";
    modelCategory->setQuery(get_distinct_cate);
    ui->comboBoxCategory->setModel(modelCategory);
}
