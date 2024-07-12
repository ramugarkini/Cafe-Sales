#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "inventorywidget.h"
#include "inboundwidget.h"
#include "outboundwidget.h"
#include "outbound2widget.h"
#include "outbound3widget.h"
#include "staffwidget.h"
#include "userswidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    InventoryWidget *inventory;
    InboundWidget *inbound;
    OutboundWidget *outbound;
    Outbound2Widget *outbound2;
    Outbound3Widget *outbound3;
    StaffWidget *staff;
    UsersWidget *users;
};

#endif // MAINWINDOW_H
