#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    inventory(new InventoryWidget(this)),
    inbound(new InboundWidget(this)),
    outbound(new OutboundWidget(this)),
    outbound2(new Outbound2Widget(this)),
    outbound3(new Outbound3Widget(this)),
    staff(new StaffWidget(this)),
    users(new UsersWidget(this))
{
    qDebug() << "[Main Window] Constructing...";
    ui->setupUi(this);

    ui->tabWidget->addTab(inventory, tr("Inventory"));
    ui->tabWidget->addTab(outbound, tr("Cart - Confirm Order"));
    ui->tabWidget->addTab(outbound2, tr("Generate Receipt"));
    ui->tabWidget->addTab(outbound3, tr("Report - Sales"));
    ui->tabWidget->addTab(inbound, tr("Report - Inventory Added Items "));
    ui->tabWidget->addTab(staff, tr("Staff Details"));
    ui->tabWidget->addTab(users, tr("Users"));

    connect(inventory, &InventoryWidget::inbounded,
            inbound, &InboundWidget::refreshCategoryComboBox);
    connect(inventory, &InventoryWidget::inbounded,
            inbound, &InboundWidget::on_pushButtonQuery_clicked);

    connect(inventory, &InventoryWidget::inbounded,
            inventory, &InventoryWidget::refreshOutNameComboBox);

    connect(inventory, &InventoryWidget::outbounded,
            outbound, &OutboundWidget::refreshCategoryComboBox);
    connect(inventory, &InventoryWidget::outbounded,
            outbound, &OutboundWidget::on_pushButtonQuery_clicked);

    connect(inventory, &InventoryWidget::outbounded,
            outbound2, &Outbound2Widget::on_pushButtonQuery_clicked);

    connect(inventory, &InventoryWidget::outbounded,
            outbound3, &Outbound3Widget::refreshCategoryComboBox);
    connect(inventory, &InventoryWidget::outbounded,
            outbound3, &Outbound3Widget::on_pushButtonQuery_clicked);

    connect(outbound, &OutboundWidget::outbounded, outbound, &OutboundWidget::refreshCategoryComboBox);
    connect(outbound, &OutboundWidget::outbounded, outbound, &OutboundWidget::on_pushButtonQuery_clicked);
    connect(outbound, &OutboundWidget::outbounded, outbound2, &Outbound2Widget::on_pushButtonQuery_clicked);
    connect(outbound, &OutboundWidget::outbounded, outbound3, &Outbound3Widget::refreshCategoryComboBox);
    connect(outbound, &OutboundWidget::outbounded, outbound3, &Outbound3Widget::on_pushButtonQuery_clicked);
}

MainWindow::~MainWindow()
{
    qDebug() << "[Main Window] Destructing...";
    delete ui;
    delete inventory;
    delete inbound;
    delete outbound;
    delete outbound2;
    delete outbound3;
    delete staff;
    delete users;
}
