#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QMessageBox>
#include <QKeyEvent>
#include <QShortcut>
#include "fileexplorer.h"

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

	//Button slots
	void	on_save_btn_clicked();
	void	on_open_btn_clicked();
	void	on_help_btn_clicked();
	void	on_open_btn_2_clicked();
	void	on_eng_lang_clicked();
	void	on_rus_lang_clicked();

	//File
	QString	open_file(QString path="");
	void	save_file();
	void	new_file();
	void	exit();

	//Translation
	void	set_language(QString lang);

	void on_radio_style_light_clicked();

	void on_radio_style_night_clicked();

private:
	Ui::MainWindow*		ui;
	FileExplorer*		my_widget;

	//Translator
	QTranslator			translator;

	//Message boxes
	QMessageBox			help_box;
	QMessageBox			save_box;
	QAbstractButton*	approve_btn;
	QAbstractButton*	disapprove_btn;

	//Hot keys
	QShortcut*			hot_save;
	QShortcut*			hot_open;
	QShortcut*			hot_new;
	QShortcut*			hot_exit;

	//Set style
	QString				light_style = ":/st/style_light.txt";
	QString				night_style = ":/st/style_night.txt";

};

#endif // MAINWINDOW_H
