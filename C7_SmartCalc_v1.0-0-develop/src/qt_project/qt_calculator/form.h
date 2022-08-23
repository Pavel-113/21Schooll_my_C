#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QVector>
extern "C" {
#include "../../s21_calc.h"
}


namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    void print_graph(double x_min, double x_max);

private:
    Ui::Form *ui;
    double xBegin, xEnd, h, X;
    int N;
    char * input;

public slots:
    void slot(QString ans, char * input_str);

private slots:
    void on_radioButton_clicked();
    void on_pushButton_clicked();
};

#endif // FORM_H
