#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form) {
  ui->setupUi(this);
}

Form::~Form() { delete ui; }

void Form::print_graph(double x_min, double x_max) {
  QVector<double> x, y;
  h = 0.01;
  double min = 1000000;
  double max = -1000000;
  if (x_min > x_max) {
    double tmp = x_max;
    x_max = x_min;
    x_min = tmp;
    ui->doubleSpinBox->setValue(x_min);
    ui->doubleSpinBox_2->setValue(x_max);
  }
  xBegin = x_min;
  xEnd = x_max;
  qDebug() << input << "!!!";

  for (X = xBegin; X <= xEnd; X += h) {
    x.push_back(X);
    double d = get_result(input, X);
    if (d > max) {
      max = d;
    }
    if (d < min) {
      min = d;
    }
    y.push_back(d);
  }
  N = (xEnd - xBegin) / h + 2;

  if (!ui->radioButton->isChecked()) {
    x_min = ui->doubleSpinBox->value();
    x_max = ui->doubleSpinBox_2->value();
    min = ui->doubleSpinBox_3->value();
    max = ui->doubleSpinBox_4->value();
    N = (x_max - x_min) / h + 2;
  }
  ui->widget->xAxis->setRange(x_min, x_max);
  ui->widget->yAxis->setRange(min * 1.05, max * 1.05);
  ui->widget->addGraph();
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
  ui->widget->graph()->setData(x, y);
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void Form::slot(QString ans, char *input_str) {
  qDebug() << "!!!!" << input_str;
  ui->label->setText(ans);
  input = input_str;
  print_graph(-5, 5);
}

void Form::on_radioButton_clicked() {
  if (ui->radioButton->isChecked()) {
    ui->label_2->setDisabled(true);
    ui->label_3->setDisabled(true);
    ui->label_4->setDisabled(true);
    ui->label_5->setDisabled(true);
    ui->doubleSpinBox->setDisabled(true);
    ui->doubleSpinBox_2->setDisabled(true);
    ui->doubleSpinBox_3->setDisabled(true);
    ui->doubleSpinBox_4->setDisabled(true);
  } else {
    ui->label_2->setDisabled(false);
    ui->label_3->setDisabled(false);
    ui->label_4->setDisabled(false);
    ui->label_5->setDisabled(false);
    ui->doubleSpinBox->setDisabled(false);
    ui->doubleSpinBox_2->setDisabled(false);
    ui->doubleSpinBox_3->setDisabled(false);
    ui->doubleSpinBox_4->setDisabled(false);
  }
}

void Form::on_pushButton_clicked() {
  ui->label->text();
  QByteArray ba = ui->label->text().toLocal8Bit();
  char *str = ba.data();
  char input_str[256] = {0};

  int i;
  for (i = 0; i < 255 && *str; i++) {
    input_str[i] = *str;
    str++;
  }
  input_str[i] = '\0';
  input = input_str;

  qDebug() << ui->doubleSpinBox->value() << ":" << ui->doubleSpinBox_2->value()
           << "!!!";

  ui->widget->clearGraphs();
  print_graph(ui->doubleSpinBox->value(), ui->doubleSpinBox_2->value());
}
