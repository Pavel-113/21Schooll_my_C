#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <form.h>

extern "C" {
#include "../../s21_calc.h"
}


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Form *form;
    int check_open;
    int check_ans;


private slots:
    void digits_numbers();
    void on_pushButton_one_AC_clicked();
    void on_pushButton_one_ans_clicked();
    void on_pushButton_one_AC_2_clicked();

    void on_radioButton_clicked();

signals:
    void signal(QString, char *);
};

#endif // MAINWINDOW_H
