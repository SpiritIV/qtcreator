#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QApplication>
#include <QKeySequence>
#include <QAbstractButton>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	my_widget = new FileExplorer(this);
	ui->fileExp->addWidget(my_widget);

	//Get styles
	setStyleSheet(open_file(light_style));

	//Save message
	approve_btn = save_box.addButton("", QMessageBox::ActionRole);
	disapprove_btn = save_box.addButton("", QMessageBox::RejectRole);

	hot_save = new QShortcut(QKeySequence("Ctrl+S"), this);
	hot_open = new QShortcut(QKeySequence("Ctrl+O"), this);
	hot_new = new QShortcut(QKeySequence("Ctrl+N"), this);
	hot_exit = new QShortcut(QKeySequence("Ctrl+Q"), this);

	QObject::connect(hot_save, SIGNAL(activated()), this, SLOT(on_save_btn_clicked()));
	QObject::connect(hot_open, SIGNAL(activated()), this, SLOT(on_open_btn_clicked()));
	QObject::connect(hot_new, SIGNAL(activated()), this, SLOT(new_file()));
	QObject::connect(hot_exit, SIGNAL(activated()), this, SLOT(exit()));

	//Set language
	set_language("en");
}

MainWindow::~MainWindow()
{
	delete ui;
}

//Work with files
/*-------------------------------------------------------*/

QString	MainWindow::open_file(QString path)
{
	QString	result = "";

	if (path.length() == 0)
	{
		path = QFileDialog::getOpenFileName();
	}

	if (path.isEmpty())
	{
		return (result);
	}

	QFile	file(path);

	if (file.open(QIODevice::ReadOnly))
	{
		QByteArray	byte_ar = file.readAll();
		QString		text(byte_ar);

		result = text;
	}
	return (result);
}

void	MainWindow::save_file()
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

void	MainWindow::new_file()
{
	save_box.exec();
	if (save_box.clickedButton() == approve_btn)
	{
		save_file();
	}
	ui->text_edit->clear();
}

void	MainWindow::exit()
{
	close();
}

void MainWindow::on_open_btn_clicked()
{
	ui->text_edit->setPlainText(open_file());
	ui->text_edit->setReadOnly(false);
}

void MainWindow::on_open_btn_2_clicked()
{
	ui->text_edit->setPlainText(open_file());
	ui->text_edit->setReadOnly(true);
}

void MainWindow::on_save_btn_clicked()
{
	save_file();
}

void MainWindow::on_help_btn_clicked()
{
	help_box.exec();
}

/*-------------------------------------------------------*/

//Translation events and methods
/*-------------------------------------------------------*/

void MainWindow::on_eng_lang_clicked()
{
	if ((ui->eng_lang->isChecked()))
	{
		set_language("en");
	}
}

void MainWindow::on_rus_lang_clicked()
{
	if ((ui->rus_lang->isChecked()))
	{
		set_language("ru");
	}
}

void MainWindow::set_language(QString lang)
{
	translator.load(":/tr/QtLanguage_" + lang + ".qm");

	qApp->installTranslator(&translator);

	//Buttons
	ui->save_btn->setText(tr("Save"));
	ui->open_btn->setText(tr("Open"));
	ui->open_btn_2->setText(tr("Open\n(read only)"));
	ui->help_btn->setText(tr("Help"));

	//Lables
	ui->label->setText(tr("Choose language:"));
	ui->label_style->setText(tr("Choose style:"));

	//Radio
	ui->rus_lang->setText(tr("RUS"));
	ui->eng_lang->setText(tr("ENG"));
	ui->radio_style_light->setText(tr("Light"));
	ui->radio_style_night->setText(tr("Night"));

	//Other widgets
	save_box.setText(tr("Would you like to save document?"));
	approve_btn->setText(tr("Yes"));
	disapprove_btn->setText(tr("No"));

	help_box.setText(tr("Press 'Save' button to save file to the custom path\n"
						"Press 'Open' button to open from the custom path\n"
						"Press 'Open (read only)' button to open only for read\n"
						"Press Ctrl+O to open file\n"
						"Press Ctrl+S to save file\n"
						"Press Ctrl+N to create a new file\n"
						"Press Ctrl+Q to close application"));
}

/*-------------------------------------------------------*/


//Set styles
void MainWindow::on_radio_style_light_clicked()
{
	if (ui->radio_style_light->isChecked())
	{
		setStyleSheet(open_file(light_style));
	}
}

void MainWindow::on_radio_style_night_clicked()
{
	if (ui->radio_style_night->isChecked())
	{
		setStyleSheet(open_file(night_style));
	}
}
