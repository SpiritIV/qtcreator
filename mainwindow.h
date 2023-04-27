#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QMessageBox>
#include <QKeyEvent>
#include <QShortcut>

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
	void on_open_btn_2_clicked();
	void on_eng_lang_clicked();
	void on_rus_lang_clicked();

	void new_file();
	void exit();

private:
	Ui::MainWindow*	ui;
	QTranslator		translator;
	QMessageBox		help_box;
	QShortcut*		hot_save;
	QShortcut*		hot_open;
	QShortcut*		hot_new;
	QShortcut*		hot_exit;
};

#endif // MAINWINDOW_H
