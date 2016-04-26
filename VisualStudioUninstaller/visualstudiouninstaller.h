#ifndef VISUALSTUDIOUNINSTALLER_H
#define VISUALSTUDIOUNINSTALLER_H

#include <QtWidgets/QMainWindow>
#include <QProcess>
#include "ui_visualstudiouninstaller.h"

struct Product
{
    QString desc;
    QString idNumber;
    QString installDate;
    QString installLocation;
    QString installState;
    QString name;
    QString packCache;
    QString skuNumber;
    QString vendor;
    QString version;
};

class QStandardItemModel;
class VisualStudioUninstaller : public QMainWindow
{
	Q_OBJECT

public:
	VisualStudioUninstaller(QWidget *parent = 0);
	~VisualStudioUninstaller();

    QList<Product *> productList();
    void updateTableView();

private:
	Ui::VisualStudioUninstallerClass ui;
    QProcess _process;
    QStandardItemModel *_model;
};

#endif // VISUALSTUDIOUNINSTALLER_H