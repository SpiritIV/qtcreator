#include "fileexplorer.h"
#include <QDir>

FileExplorer::FileExplorer(QWidget *parent) : QWidget(parent), model(nullptr)
{
	gridLay	= new QGridLayout(this);

	curDir = new QLabel(this);
	this->setLayout(gridLay);

	tree = new QTreeView(this);

	gridLay->addWidget(tree, 2, 0, 10, 10);
	gridLay->addWidget(curDir);

//	setMinimumSize(500, 600);
	if (QSysInfo::productType() == "windows")
	{
		diskBox = new QComboBox(this);

		QFileInfoList	list = QDir::drives();
		QFileInfoList::const_iterator list_disk = list.begin();
		int amount = list.count();
		for (int i = 0; i < amount; ++i)
		{
			diskBox->addItem(list_disk->path());
			++list_disk;
		}
		if (amount > 0)
		{
			rebuildModel(list.at(0).path());
		}
		gridLay->addWidget(diskBox, 1, 0, 1, 2);
		connect(diskBox, SIGNAL(activated(int)), this, SLOT(chDisk(int)));
	}
	else
	{
		mainPath = new QPushButton(this);
		mainPath->setText("/");
		gridLay->addWidget(mainPath, 0, 0, 1, 2);
		connect(mainPath, SIGNAL(clicked()), this, SLOT(goMainPath()));
		rebuildModel("/");
	}
}

void FileExplorer::setNewModel(QStandardItemModel *new_model)
{
	tree->setModel(new_model);
	model = new_model;
}

void FileExplorer::rebuildModel(QString str)
{
	QStandardItemModel*		model = new QStandardItemModel(this);
	QList<QStandardItem*>	items;

	currentPath = str;
	this->curDir->setText("Current path: " + currentPath);
	items.append(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DriveHDIcon)), str));
	model->appendRow(items);

	QDir	dir(str);
	dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs);
	QStringList	list = dir.entryList();
	int			amount = list.count();


	QList<QStandardItem*>	folders;
	for(int i = 0; i < amount; ++i)
	{
		QStandardItem*	f = new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)), list.at(i));
		folders.append(f);
	}

	items.at(0)->appendRows(folders);

	dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Files);
	amount = list.count();

	QList<QStandardItem*>	files;
	for(int i = 0; i < amount; ++i)
	{
		QStandardItem*	f = new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)), list.at(i));
		files.append(f);
	}
	items.at(0)->appendRows(files);
	setNewModel(model);
}

void FileExplorer::chDisk(int index)
{
	QFileInfoList	list = QDir::drives();

	rebuildModel(list.at(index).path());
}

void FileExplorer::goMainPath()
{
	rebuildModel("/");
}


