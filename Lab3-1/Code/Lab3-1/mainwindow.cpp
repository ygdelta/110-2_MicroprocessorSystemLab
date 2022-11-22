#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_2_clicked()
{
    if(ui->checkBox->isChecked() == true){
        ui->label->setVisible(true);
    }
    else{
        ui->label->setVisible(false);
    }
    if(ui->checkBox_2->isChecked() == true){
        ui->label_3->setVisible(true);
    }
    else{
        ui->label_3->setVisible(false);
    }
    if(ui->checkBox_3->isChecked() == true){
        ui->label_4->setVisible(true);
    }
    else{
        ui->label_4->setVisible(false);
    }
    if(ui->checkBox_4->isChecked() == true){
        ui->label_5->setVisible(true);
    }
    else{
        ui->label_5->setVisible(false);
    }
}

void MainWindow::fuc1(){
    ui->label->setVisible(false);
    ui->checkBox->setChecked(false);
    ui->label_3->setVisible(false);
    ui->checkBox_2->setChecked(false);
    ui->label_4->setVisible(true);
    ui->checkBox_3->setChecked(true);
    ui->label_5->setVisible(true);
    ui->checkBox_4->setChecked(true);
}

void MainWindow::fuc2(){
    ui->label->setVisible(true);
    ui->checkBox->setChecked(true);
    ui->label_3->setVisible(true);
    ui->checkBox_2->setChecked(true);
    ui->label_4->setVisible(false);
    ui->checkBox_3->setChecked(false);
    ui->label_5->setVisible(false);
    ui->checkBox_4->setChecked(false);
}

void MainWindow::on_pushButton_clicked()
{
    QString times = ui->lineEdit->text();
    QTimer *timer = new QTimer(this);
    int f1 = 1000;
    int f2 = 2000;
    for(int i = 0;i<times.toInt();i++){
        timer->singleShot(f1,this,SLOT(fuc2()));
        timer->singleShot(f2,this,SLOT(fuc1()));
        f1 += 2000;
        f2 += 2000;
    }
}




