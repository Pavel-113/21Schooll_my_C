#include "mainwindow.h"
#include "QMessageBox"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_one_dot, SIGNAL(clicked()), this,
            SLOT(digits_numbers()));
    connect(ui->pushButton_one_plus, SIGNAL(clicked()), this,
            SLOT(digits_numbers()));
    connect(ui->pushButton_one_minus, SIGNAL(clicked()), this,
            SLOT(digits_numbers()));
    connect(ui->pushButton_one_mult, SIGNAL(clicked()), this,
            SLOT(digits_numbers()));
    connect(ui->pushButton_one_sep, SIGNAL(clicked()), this,
            SLOT(digits_numbers()));
    connect(ui->pushButton_stepen, SIGNAL(clicked()), this,
            SLOT(digits_numbers()));

    connect(ui->pushButton_br_l, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_br_r, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
    if (check_ans == true) {
        ui->result_show->clear();
        check_ans = false;
    }
    QPushButton *button = (QPushButton *)sender();
    QString new_input;
    if (button->text().contains("÷")) ui->result_show->setText(ui->result_show->text()+"/");
    else
//    new_input =
      ui->result_show->setText(ui->result_show->text()+ button->text());

//    ui->result_show->setText(new_input);
}

void MainWindow::on_pushButton_one_AC_clicked() {
    ui->result_show->setText("");
}

void MainWindow::on_pushButton_one_ans_clicked() {
    check_ans = true;
    qDebug() << ui->result_show->text();
    double x = ui->doubleSpinBox->value();
    QByteArray ba = ui->result_show->text().toLocal8Bit();
    char *str = ba.data();
    int len  = qstrlen(ba.data());
    qDebug() << len << "len";

    if (len < 256) {
        char input_str[256] = {0};
        int i;
        for (i = 0; i < 255 && *str; i++) {
            input_str[i] = *str;
            str++;
        }
        input_str[i] = '\0';

        qDebug() << input_str;
        if (ui->radioButton->isChecked()) {

            if (check_open == 1) {
                form->close();
                qDebug() << check_open;
                check_open = 0;
            }
            form = new Form;
            connect(this, &MainWindow::signal, form, &Form::slot);
            emit signal(ui->result_show->text(), input_str);
            form->show();
            qDebug() << check_open;
            check_open = 1;

        } else {
            double ans = get_result(input_str, x);
            ui->result_show->setText(QString::number(ans, 'g', 15));
        }
    } else {
       ui->result_show->setText("Error: maximum 255 characters.");
    }
}

void MainWindow::on_pushButton_one_AC_2_clicked() {
    QString str = ui->result_show->text();
    str.chop(1);
    ui->result_show->setText(str);
}

void MainWindow::on_radioButton_clicked()
{
    if (ui->radioButton->isChecked()) {
        ui->doubleSpinBox->setDisabled(true);
    } else {
        ui->doubleSpinBox->setDisabled(false);
    }
}
