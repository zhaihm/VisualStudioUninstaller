#include "visualstudiouninstaller.h"
#include <qDebug>

VisualStudioUninstaller::VisualStudioUninstaller(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    productList();
}

VisualStudioUninstaller::~VisualStudioUninstaller()
{

}

QList<Product *> VisualStudioUninstaller::productList()
{
    QList<Product *> productList;

    QString program = "wmic";
    QStringList args;
    args << "product" << "list";

    _process.start(program, args);
    if (!_process.waitForStarted() || !_process.waitForFinished())
        return productList;

    QString header = _process.readLine();
    if (header.isEmpty())
        return productList;

    QStringList columns = { "Description", "IdentifyingNumber", "InstallDate", "InstallLocation", "InstallState", "Name", "PackageCache", "SKUNumber", "Vendor", "Version" };
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
    return productList;
}
