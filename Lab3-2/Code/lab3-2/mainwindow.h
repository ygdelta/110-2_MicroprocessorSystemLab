#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTimer *timer;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void update();


private:
    int count;
    int judge;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
