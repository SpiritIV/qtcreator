#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_sqrt_button_clicked()
{
	QString	result;
	double	number = ui->enter_task_1_lineEdit->text().toDouble();

	if (number < 0)
	{
		result = QString::number(qSqrt(-number));
		result.append("i");
		ui->result_task_1->setText(result);
	}
	else
	{
		result = QString::number(qSqrt(number));
		ui->result_task_1->setText(result);
	}
}

void MainWindow::on_triangle_button_clicked()
{
	double	side_a = ui->enter_a->text().toDouble();
	double	side_b = ui->enter_b->text().toDouble();
	double	angle = 0.0;

	angle = ui->radians_radio->isChecked() ? ui->enter_angle->text().toDouble() : qDegreesToRadians(ui->enter_angle->text().toDouble());
	ui->result_task_2->setText(QString::number(0.5 * side_a * side_b * qSin(angle)));
}

void MainWindow::on_copy_left_right_button_clicked()
{
	ui->task_3_textEdit_right->setPlainText(ui->task_3_textEdit_left->toPlainText());
	ui->task_3_textEdit_left->setPlainText("");
}

void MainWindow::on_copy_right_left_button_clicked()
{
	ui->task_3_textEdit_left->setPlainText(ui->task_3_textEdit_right->toPlainText());
	ui->task_3_textEdit_right->setPlainText("");
}

void MainWindow::on_add_html_button_clicked()
{
	ui->task_3_textEdit_right->setHtml("<font color='red'>Hello</font>");
}
