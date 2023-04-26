#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
	void on_save_btn_clicked();

	void on_open_btn_clicked();

	void on_help_btn_clicked();

	void on_parse_btn_clicked();

private:
	Ui::MainWindow *ui;
	QString		getHtml(const QString &url);
	QStringList	parseStr(const QString &html);
};

#endif // MAINWINDOW_H
