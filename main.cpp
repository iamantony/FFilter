#include <QApplication>
#include <QCleanlooksStyle>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication::setStyle(new QCleanlooksStyle);
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
