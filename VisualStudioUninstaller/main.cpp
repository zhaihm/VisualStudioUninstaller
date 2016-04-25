#include "visualstudiouninstaller.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VisualStudioUninstaller w;
	w.show();
	return a.exec();
}
