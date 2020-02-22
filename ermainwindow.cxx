#include "ermainwindow.hxx"
#include "ui_ermainwindow.h"

ERMainWindow::ERMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ERMainWindow)
{
    ui->setupUi(this);
}

ERMainWindow::~ERMainWindow()
{
    delete ui;
}

