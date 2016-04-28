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
    void updateTableView(const QList<QStringList>& productList);

private slots:
    void on_refreshAction_triggered();
    void on_exitAction_triggered();

private:
	Ui::VisualStudioUninstallerClass ui;
    QProcess _process;
    QStandardItemModel *_model;
    QStringList _headers;
};

#endif // VISUALSTUDIOUNINSTALLER_H
