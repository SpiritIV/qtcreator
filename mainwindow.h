#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMath>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_sqrt_button_clicked();

	void on_triangle_button_clicked();

	void on_copy_left_right_button_clicked();

	void on_copy_right_left_button_clicked();

	void on_add_html_button_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
