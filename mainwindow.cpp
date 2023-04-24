#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

PasteSpecialSign::PasteSpecialSign()
{
	all_signes.push_back(smile_sign);
	all_signes.push_back(letter_sign);
	all_signes.push_back(inf_sign);
	all_signes.push_back(heart_sign);

	all_words.push_back(smile_word);
	all_words.push_back(letter_word);
	all_words.push_back(inf_word);
	all_words.push_back(heart_word);
}

QString	PasteSpecialSign::change_signes(QString str)
{
	int		index;

	index = 0;
	for(int i = 0; i < all_words.size(); ++i)
	{
		index = str.indexOf(all_words[i], 0);
		while (index > 1)
		{			
			if ((str.indexOf("#", index - 2) < index) &&\
				(str.indexOf("@", index - 1) < index))
			{
				str.replace(index - 2, all_words[i].length() + 2, all_signes[i]);
			}
			index = str.indexOf(all_words[i], 0);
			printf("index = %d\n", index);
		}
	}
	return (str);
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	str_cursor = new QTextCursor(ui->text_edit_task_1->textCursor());

	//Setup item model
	item_model = new QStandardItemModel(ui->listView);
	item_model->appendRow(new QStandardItem(QIcon("../cpp.png"),"С++"));
	item_model->appendRow(new QStandardItem(QIcon("../python.png"),"Python"));
	item_model->appendRow(new QStandardItem(QIcon("../java.png"),"Java"));
	item_model->appendRow(new QStandardItem(QIcon("../csharp.png"),"C#"));
	item_model->appendRow(new QStandardItem(QIcon("../php.png"),"PHP"));
	item_model->appendRow(new QStandardItem(QIcon("../js.png"),"JavaScript"));

	//Setup selection model
	new_selection = new QItemSelectionModel(item_model, this);

	ui->listView->setModel(item_model);
	ui->listView->setDragDropMode(QAbstractItemView::InternalMove);
	ui->listView->setSelectionModel(new_selection);

	ui->listView->setModel(item_model);
	ui->listView->setDefaultDropAction(Qt::IgnoreAction);
	ui->listView->setSelectionModel(new_selection);

	//Create table model

	QStringList				labels{"No", "PC name", "IP", "MAC"};

	table_model = new QStandardItemModel(this);
	table_selection = new QItemSelectionModel(table_model, this);
	table_model->insertColumns(0, 3);
	table_model->setHorizontalHeaderLabels(labels);

	//Row 1
	table_model->appendRow({new QStandardItem("1"),\
							new QStandardItem("PC 1"),\
							new QStandardItem("218.144.33.40"),\
							new QStandardItem("c6:6f:a7:c9:1a:65")});

	//Row 2
	table_model->appendRow({new QStandardItem("2"),\
							new QStandardItem("PC 2"),\
							new QStandardItem("100.237.235.149"),\
							new QStandardItem("0a:b3:f2:cf:20:06")});

	//Row 3
	table_model->appendRow({new QStandardItem("3"),\
							new QStandardItem("PC 3"),\
							new QStandardItem("20.39.242.21"),\
							new QStandardItem("2b:56:2c:0f:f5:ec")});

	//Row 4
	table_model->appendRow({new QStandardItem("4"),\
							new QStandardItem("PC 4"),\
							new QStandardItem("85.248.72.114"),\
							new QStandardItem("c7:c9:42:64:29:ef")});

	ui->tableView->setModel(table_model);
	ui->tableView->setSelectionModel(table_selection);

	task_1 = new PasteSpecialSign();
}

MainWindow::~MainWindow()
{
	if (task_1)
	{
		delete task_1;
		task_1 = nullptr;
	}
	if (item_model)
	{
		delete item_model;
		item_model = nullptr;
	}
	if (new_selection)
	{
		delete new_selection;
		new_selection = nullptr;
	}
	if (str_cursor)
	{
		delete str_cursor;
		str_cursor = nullptr;
	}
	if (table_model)
	{
		delete table_model;
		table_model = nullptr;
	}
	delete ui;
}

//Task 1
void MainWindow::on_text_edit_task_1_textChanged()
{
	QString	str;
	QString result;

	str = ui->text_edit_task_1->toPlainText();
	result = task_1->change_signes(str);
	if (result != str)
	{
		ui->text_edit_task_1->setPlainText(result);
		str_cursor->setPosition(ui->text_edit_task_1->document()->characterCount());
		ui->text_edit_task_1->setTextCursor(*str_cursor);
	}
}

//Task 2
void MainWindow::on_add_new_lang_clicked()
{
	item_model->appendRow(new QStandardItem(QIcon("../rand.png"),ui->enter_new_lang->text()));
}

void MainWindow::on_icon_mode_clicked()
{
	if (ui->icon_mode->isChecked())
	{
		ui->listView->setViewMode(QListView::IconMode);
	}
	else
	{
		ui->listView->setViewMode(QListView::ListMode);
	}
	ui->listView->setDragDropMode(QAbstractItemView::InternalMove);
}

void MainWindow::on_delete_lang_clicked()
{
	QModelIndexList indexes = new_selection->selectedRows();

	if (!indexes.isEmpty())
	{
		item_model->removeRows(indexes.back().row(), 1);
	}
}


void MainWindow::on_fill_rows_btn_clicked()
{
	QModelIndexList indexes = table_selection->selectedRows();
	QColor			brush(250, 0, 0);

	foreach (auto ind, indexes)
	{
		table_model->setData(table_model->index(ind.row(), 0),\
							 brush, Qt::BackgroundRole);
		table_model->setData(table_model->index(ind.row(), 1),\
							 brush, Qt::BackgroundRole);
		table_model->setData(table_model->index(ind.row(), 2),\
							 brush, Qt::BackgroundRole);
		table_model->setData(table_model->index(ind.row(), 3),\
							 brush, Qt::BackgroundRole);
	}
}
