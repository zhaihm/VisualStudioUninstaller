#ifndef VISUALSTUDIOUNINSTALLER_H
#define VISUALSTUDIOUNINSTALLER_H

#include <QtWidgets/QMainWindow>
#include <QProcess>
#include "ui_visualstudiouninstaller.h"

class QStandardItemModel;
class VisualStudioUninstaller : public QMainWindow
{
	Q_OBJECT

public:
	VisualStudioUninstaller(QWidget *parent = 0);
	~VisualStudioUninstaller();

    QList<QStringList> productList();
    void updateTableView();

private:
	Ui::VisualStudioUninstallerClass ui;
    QProcess _process;
    QStandardItemModel *_model;
};

#endif // VISUALSTUDIOUNINSTALLER_H
