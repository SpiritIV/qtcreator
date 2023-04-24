#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QTextCursor>
#include <QStringListModel>

class PasteSpecialSign
{
private:
	QString				smile_sign = "☺";
	QString				letter_sign = "✉";
	QString				inf_sign = "∞";
	QString				heart_sign = "♡";
	QString				smile_word = "smile@";
	QString				letter_word = "letter@";
	QString				inf_word = "inf@";
	QString				heart_word = "heart@";

	QVector<QString>	all_words;
	QVector<QString>	all_signes;
public:
	PasteSpecialSign();

	QString	change_signes(QString str);

	~PasteSpecialSign() {}
};

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
	void on_text_edit_task_1_textChanged();

	void on_add_new_lang_clicked();

	void on_icon_mode_clicked();

	void on_delete_lang_clicked();

	void on_fill_rows_btn_clicked();

private:
	Ui::MainWindow*			ui;
	PasteSpecialSign*		task_1;
	QStandardItemModel*		item_model;
	QItemSelectionModel*	new_selection;
	QTextCursor*			str_cursor;
	QStandardItemModel*		table_model;
	QItemSelectionModel*	table_selection;
};

#endif // MAINWINDOW_H
