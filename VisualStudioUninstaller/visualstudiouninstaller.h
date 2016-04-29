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
    void onTableViewRightClicked(const QPoint & pos);
    void onDeleteProduct(bool);

private:
	Ui::VisualStudioUninstallerClass ui;
    QProcess _process;
    QStandardItemModel *_model;
    QStringList _headers;
    QMenu *_menu;
    QString _currentProductName;
};

#endif // VISUALSTUDIOUNINSTALLER_H
