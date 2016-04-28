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
    _headers = QStringList({ "Description", "IdentifyingNumber", "InstallDate", "InstallLocation", "InstallState", "Name", "PackageCache", "SKUNumber", "Vendor", "Version" });
	
    on_refreshAction_triggered();
}

VisualStudioUninstaller::~VisualStudioUninstaller()
{
}

QList<QStringList> VisualStudioUninstaller::productList()
{
    QList<QStringList> productList; // not using QStringList *, to avoid ugly code like (*productList[i])[j]

    QString program = "wmic";
    QStringList args;
    args << "product" << "list";

    _process.start(program, args);
    if (!_process.waitForStarted() || !_process.waitForFinished())
        return productList;

    QTextStream ts(&_process);
    ts.setCodec("utf8");

    QString headerLine = ts.readLine();
    if (headerLine.isEmpty())
        return productList;

    QList<int> indexes;
    foreach (QString header, _headers) {
        indexes.push_back(headerLine.indexOf(header));
    }

    QString line;
    while (!(line = ts.readLine()).isEmpty()) {
        QStringList product;

        for (int i = 0; i < indexes.length(); i++) {
            int end = (i + 1 == indexes.length()) ? line.length() : indexes[i + 1];
            product.push_back(line.mid(indexes[i], end - indexes[i]).trimmed());
        }
        productList.push_back(product);
    }

    return productList;
}

void VisualStudioUninstaller::updateTableView(const QList<QStringList>& productList)
{
    _model->clear();

    // re-init model
    _model->setColumnCount(_headers.length());
    for (size_t i = 0; i < _headers.length(); i++) {
        _model->setHeaderData(i, Qt::Horizontal, _headers[i]);
    }
    ui.tableView->setModel(_model);

    for (size_t i = 0; i < productList.length(); i++) {
        for (size_t j = 0; j < _headers.length(); j++) {
            _model->setItem(i, j, new QStandardItem(tr(productList[i][j].toStdString().c_str())));
        }
    }
}

void VisualStudioUninstaller::on_refreshAction_triggered()
{
    qDebug() << "refreshing...";

    QList<QStringList> pl = productList();
    updateTableView(pl);
}

void VisualStudioUninstaller::on_exitAction_triggered()
{
    exit(0);
}
