#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_start_button_clicked()
{
    //ui->stackedWidget(start_page)->show()
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_rules_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_return_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

