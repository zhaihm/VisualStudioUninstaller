#include "visualstudiouninstaller.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QLocale::setDefault(QLocale("utf-8"));
	QApplication a(argc, argv);
	VisualStudioUninstaller w;
	w.show();
	return a.exec();
}
