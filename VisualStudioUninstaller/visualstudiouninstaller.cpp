#include "visualstudiouninstaller.h"
#include <qDebug>
#include <QStandardItemModel>
#include <QStandardItem>

#define LOCALE  "GBK"

VisualStudioUninstaller::VisualStudioUninstaller(QWidget *parent)
	: QMainWindow(parent)
{
    ui.setupUi(this);
    ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tableView->setSortingEnabled(true);
    _model = new QStandardItemModel;
	
    productList();
}

VisualStudioUninstaller::~VisualStudioUninstaller()
{

}

QList<QStringList> VisualStudioUninstaller::productList()
{
    QList<QStringList> productList; // not using QStringList *, to avoid (*productList[i])[j]

    // init table
    QStringList columns = { "Description", "IdentifyingNumber", "InstallDate", "InstallLocation", "InstallState", "Name", "PackageCache", "SKUNumber", "Vendor", "Version" };
    _model->setColumnCount(columns.length());
    for (size_t i = 0; i < columns.length(); i++) {
        _model->setHeaderData(i, Qt::Horizontal, columns[i]);
    }
    ui.tableView->setModel(_model);

    QString program = "wmic";
    QStringList args;
    args << "product" << "list";

    _process.start(program, args);
    if (!_process.waitForStarted() || !_process.waitForFinished())
        return productList;

    QTextStream ts(&_process);
    ts.setCodec(LOCALE);

    QString header = ts.readLine();
    if (header.isEmpty())
        return productList;

    QList<int> indexes;
    foreach (QString column, columns) {
        indexes.push_back(header.indexOf(column));
    }

    QString line;
    while (!(line = ts.readLine()).isEmpty()) {
        QStringList product;

        for (int i = 0; i < indexes.length(); i++) {
            int end = (i + 1 == indexes.length()) ? line.length() : indexes[i + 1];
            product[i] = line.mid(indexes[i], end - indexes[i]).trimmed();
        }
        productList.push_back(product);
    }

    for (size_t i = 0; i < productList.length(); i++) {
        for (size_t j = 0; j < columns.length(); j++) {
            _model->setItem(i, j, new QStandardItem(tr(productList[i][j].toStdString().c_str())));
        }
    }

    return productList;
}

void VisualStudioUninstaller::updateTableView()
{
    
}
