#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QApplication>
#include <QKeySequence>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	hot_save = new QShortcut(QKeySequence("Ctrl+S"), this);
	hot_open = new QShortcut(QKeySequence("Ctrl+O"), this);
	hot_new = new QShortcut(QKeySequence("Ctrl+N"), this);
	hot_exit = new QShortcut(QKeySequence("Ctrl+Q"), this);

	ui->save_btn->setText(tr("Save"));
	ui->open_btn->setText(tr("Open"));
	ui->open_btn_2->setText(tr("Open\n(read only)"));
	ui->help_btn->setText(tr("Help"));
	ui->label->setText(tr("Choose language:"));
	help_box.setText(tr("Click on 'Save' to save document\nClick on 'Open' to open document"));

//	connect(ui->save_btn, &QPushButton::clicked, this, &MainWindow::on_save_btn_clicked);
	QObject::connect(hot_save, SIGNAL(activated()), this, SLOT(on_save_btn_clicked()));
	QObject::connect(hot_open, SIGNAL(activated()), this, SLOT(on_open_btn_clicked()));
	QObject::connect(hot_new, SIGNAL(activated()), this, SLOT(new_file()));
	QObject::connect(hot_exit, SIGNAL(activated()), this, SLOT(exit()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

//Task 1

void MainWindow::on_save_btn_clicked()
{
	QString	path = QFileDialog::getSaveFileName();

	if (path.isEmpty())
	{
		return ;
	}

	QFile	file(path);

	if (file.open(QIODevice::WriteOnly))
	{
		QString		text = ui->text_edit->toPlainText();
		QByteArray	byte_ar = text.toUtf8();
		file.write(byte_ar, byte_ar.length());
		file.close();
	}
}

void MainWindow::on_open_btn_clicked()
{
	QString	path = QFileDialog::getOpenFileName();

	if (path.isEmpty())
	{
		return ;
	}

	QFile	file(path);

	if (file.open(QIODevice::ReadOnly))
	{
		QByteArray	byte_ar = file.readAll();
		QString		text(byte_ar);
		ui->text_edit->setPlainText(text);
	}
	ui->text_edit->setReadOnly(false);
}

void MainWindow::on_help_btn_clicked()
{
	help_box.setText(tr("Click on 'Save' to save document\nClick on 'Open' to open document"));
	help_box.exec();
}

void MainWindow::on_open_btn_2_clicked()
{
	QString	path = QFileDialog::getOpenFileName();

	if (path.isEmpty())
	{
		return ;
	}

	QFile	file(path);

	if (file.open(QIODevice::ReadOnly))
	{
		QByteArray	byte_ar = file.readAll();
		QString		text(byte_ar);
		ui->text_edit->setPlainText(text);
	}
	ui->text_edit->setReadOnly(true);
}

void MainWindow::on_eng_lang_clicked()
{
	if ((ui->eng_lang->isChecked()))
	{
		translator.load(":/tr/QtLanguage_en.qm");
		qApp->installTranslator(&translator);

		ui->save_btn->setText(tr("Save"));
		ui->open_btn->setText(tr("Open"));
		ui->open_btn_2->setText(tr("Open\n(read only)"));
		ui->help_btn->setText(tr("Help"));
		help_box.setText(tr("Click on 'Save' to save document\nClick on 'Open' to open document"));
		ui->label->setText(tr("Choose language:"));
	}
}

void MainWindow::on_rus_lang_clicked()
{
	if ((ui->rus_lang->isChecked()))
	{
		translator.load(":/tr/QtLanguage_ru.qm");
		qApp->installTranslator(&translator);

		ui->save_btn->setText(tr("Save"));
		ui->open_btn->setText(tr("Open"));
		ui->open_btn_2->setText(tr("Open\n(read only)"));
		ui->help_btn->setText(tr("Help"));
		help_box.setText(tr("Click on 'Save' to save document\nClick on 'Open' to open document"));
		ui->label->setText(tr("Choose language:"));
	}
}

void	MainWindow::new_file()
{
	ui->text_edit->clear();
}

void	MainWindow::exit()
{
	close();
}


