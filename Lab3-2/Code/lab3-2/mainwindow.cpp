#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTime>
#include <QTimer>
#include "direction.h"
#include "export.h"
#include "un_export.h"
#include "value.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    count = 0;
    judge = 0;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));

    timer->start(120 / 24 * 100);

    ui->setupUi(this);

    gpio_export(393);
    gpio_export(389);
    gpio_export(398);
    gpio_export(427);
    gpio_direction(393,"out");
    gpio_direction(389,"out");
    gpio_direction(398,"out");
    gpio_direction(427,"out");

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update(){
    QList<QLabel *> allPic = ui->splitter->findChildren<QLabel *>();
    QList<QCheckBox *> allCheck = ui->splitter_2->findChildren<QCheckBox *>();
    if(count > 0 && judge){
        allCheck.at(0)->setChecked(false);
        allCheck.at(1)->setChecked(false);
        allCheck.at(2)->setChecked(true);
        allCheck.at(3)->setChecked(true);
        allPic.at(2)->setDisabled(0);
        allPic.at(3)->setDisabled(0);
        allPic.at(0)->setDisabled(1);
        allPic.at(1)->setDisabled(1);
        gpio_value(393, 0);
        gpio_value(389, 0);
        gpio_value(398, 1);
        gpio_value(427, 1);
        count = 0;
    }
    else if(count == 0 && judge){
        allCheck.at(0)->setChecked(true);
        allCheck.at(1)->setChecked(true);
        allCheck.at(2)->setChecked(false);
        allCheck.at(3)->setChecked(false);
        allPic.at(2)->setDisabled(1);
        allPic.at(3)->setDisabled(1);
        allPic.at(0)->setDisabled(0);
        allPic.at(1)->setDisabled(0);
        gpio_value(393, 1);
        gpio_value(389, 1);
        gpio_value(398, 0);
        gpio_value(427, 0);
        count = 1;
    }

}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    timer->setInterval(120 / value * 100);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{

}

void MainWindow::on_pushButton_2_clicked()
{

    this->judge = 1;
}

void MainWindow::on_pushButton_3_clicked()
{
    QList<QLabel *> allPic = ui->splitter->findChildren<QLabel *>();
    QList<QCheckBox *> allCheck = ui->splitter_2->findChildren<QCheckBox *>();
    this->judge = 0;
    allCheck.at(0)->setChecked(false);
    allCheck.at(1)->setChecked(false);
    allCheck.at(2)->setChecked(false);
    allCheck.at(3)->setChecked(false);
    allPic.at(2)->setDisabled(1);
    allPic.at(3)->setDisabled(1);
    allPic.at(0)->setDisabled(1);
    allPic.at(1)->setDisabled(1);
    gpio_value(393, 0);
    gpio_value(389, 0);
    gpio_value(398, 0);
    gpio_value(427, 0);
}

void MainWindow::on_pushButton_clicked()
{
    QList<QLabel *> allPic = ui->splitter->findChildren<QLabel *>();
    QList<QCheckBox *> allCheck = ui->splitter_2->findChildren<QCheckBox *>();
    for(int i = 0; i < allCheck.size(); i ++){
        if(allCheck.at(i)->isChecked()){
            allPic.at(i)->setDisabled(0);
            if(i == 0){
                gpio_value(393, 1);
            }
            if(i == 1){
                gpio_value(389, 1);
            }
            if(i == 2){
                gpio_value(398, 1);
            }
            if(i == 3){
                gpio_value(427, 1);
            }
        }else{
            allPic.at(i)->setDisabled(1);
            if(i == 0){
                gpio_value(393, 0);
            }
            if(i == 1){
                gpio_value(389, 0);
            }
            if(i == 2){
                gpio_value(398, 0);
            }
            if(i == 3){
                gpio_value(427, 0);
            }
        }
    }
}
