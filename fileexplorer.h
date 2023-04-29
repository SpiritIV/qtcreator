#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QTreeView>
#include <QApplication>
#include <QComboBox>
#include <QLabel>


class FileExplorer : public QWidget
{
	Q_OBJECT
public:
	explicit			FileExplorer(QWidget *parent = nullptr);
	void				clearTree();

	QStandardItemModel*	getCurrentModel() const
	{
		return (model);
	}
	void				setNewModel(QStandardItemModel* new_model);
	void				rebuildModel(QString str);

private:
	QGridLayout*		gridLay;
	QTreeView*			tree;
	QPushButton*		mainPath;
	QLabel*				curDir;
	QComboBox*			diskBox;

private slots:
	void				chDisk(int index);
	void				goMainPath();

private:
	QStandardItemModel*	model;
	QString				currentPath;
};

#endif // FILEEXPLORER_H
