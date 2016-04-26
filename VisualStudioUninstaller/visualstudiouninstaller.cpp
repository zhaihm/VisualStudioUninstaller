#include "visualstudiouninstaller.h"
#include <qDebug>
#include <QStandardItemModel>
#include <QStandardItem>

VisualStudioUninstaller::VisualStudioUninstaller(QWidget *parent)
	: QMainWindow(parent)
{
    _model = new QStandardItemModel;

	ui.setupUi(this);
    productList();
}

VisualStudioUninstaller::~VisualStudioUninstaller()
{

}

QList<Product *> VisualStudioUninstaller::productList()
{
    QList<Product *> productList;

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

    QString header = _process.readLine();
    if (header.isEmpty())
        return productList;

    QList<int> indexes;
    foreach (QString column, columns) {
        indexes.push_back(header.indexOf(column));
    }

    QString line;
    while (!(line = _process.readLine()).isEmpty()) {
        Product *product = new Product;
        int i = 0;
        product->desc = line.mid(indexes[i], indexes[i + 1] - indexes[i++]).trimmed();
        product->idNumber = line.mid(indexes[i], indexes[i + 1] - indexes[i++]).trimmed();
        product->installDate = line.mid(indexes[i], indexes[i + 1] - indexes[i++]).trimmed();
        product->installLocation = line.mid(indexes[i], indexes[i + 1] - indexes[i++]).trimmed();
        product->installState = line.mid(indexes[i], indexes[i + 1] - indexes[i++]).trimmed();
        product->name = line.mid(indexes[i], indexes[i + 1] - indexes[i++]).trimmed();
        product->packCache = line.mid(indexes[i], indexes[i + 1] - indexes[i++]).trimmed();
        product->skuNumber = line.mid(indexes[i], indexes[i + 1] - indexes[i++]).trimmed();
        product->vendor = line.mid(indexes[i], indexes[i + 1] - indexes[i++]).trimmed();
        product->version = line.mid(indexes[i], line.length() - indexes[i++]).trimmed();

        productList.push_back(product);
    }

    for (size_t i = 0; i < productList.length(); i++) {
        _model->setItem(i, 0, new QStandardItem(tr(productList[i]->desc.toStdString().c_str())));
        _model->setItem(i, 1, new QStandardItem(productList[i]->idNumber));
        _model->setItem(i, 2, new QStandardItem(productList[i]->installDate));
        _model->setItem(i, 3, new QStandardItem(productList[i]->installLocation));
        _model->setItem(i, 4, new QStandardItem(productList[i]->installState));
        _model->setItem(i, 5, new QStandardItem(productList[i]->name));
        _model->setItem(i, 6, new QStandardItem(productList[i]->packCache));
        _model->setItem(i, 7, new QStandardItem(productList[i]->skuNumber));
        _model->setItem(i, 8, new QStandardItem(productList[i]->vendor));
        _model->setItem(i, 9, new QStandardItem(productList[i]->version));
    }

    return productList;
}

void VisualStudioUninstaller::updateTableView()
{
    
}
