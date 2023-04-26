#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QRegExp>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

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
}

void MainWindow::on_help_btn_clicked()
{
	QMessageBox	help_box;

	help_box.setText("Click on 'Save' to save document\nClick on 'Open' to open document");
	help_box.exec();
}

//Task 2

QString	MainWindow::getHtml(const QString &url)
{
	QNetworkAccessManager	manager;
	QNetworkReply*			response = manager.get(QNetworkRequest(QUrl(url)));
	QEventLoop				event;

	QObject::connect(response, SIGNAL(finished()), &event, SLOT(quit()));
	event.exec();

	response->deleteLater();
	return (response->readAll());
}

QStringList	MainWindow::parseStr(const QString &html)
{
	QRegExp		regex_cur("(currency:item:\\w\\w\\w\" data-updatable=\"true\" data-value=\")([\\d\.]+)");
	QRegExp		regex_w("(weather__temperature)(.*)(\\+[\\d]+)");
	QStringList	result;

	int	lastPos = 0;
	while((lastPos = regex_cur.indexIn(html, lastPos)) != -1)
	{
		lastPos += regex_cur.matchedLength();
		result.append(regex_cur.cap(2));
	}

	lastPos = 0;
	if ((lastPos = regex_w.indexIn(html, lastPos)) != -1)
	{
		result.append(regex_w.cap(3));
	}

	return (result);
}

void MainWindow::on_parse_btn_clicked()
{
	const QString	mail_url = "https://mail.ru/";
	const QString	error_msg = "Error";
	QString			data;
	QStringList		result;

	data = getHtml(mail_url);

	if (data.isEmpty())
	{
		qDebug() << "Can't recieve a data";
	}
	else
	{

		result = parseStr(data);

		if (result.length() == 3)
		{
			ui->usd_text->setText(result[0]);
			ui->euro_text->setText(result[1]);
			ui->weather_text->setText(result[2]);
		}
		else
		{
			ui->usd_text->setText(error_msg);
			ui->euro_text->setText(error_msg);
			ui->weather_text->setText(error_msg);
		}
	}
}
