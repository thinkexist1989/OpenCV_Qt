#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling); //添加高分屏支持
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
