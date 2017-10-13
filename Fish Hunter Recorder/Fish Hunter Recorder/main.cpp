#include "FishHunterRecorder.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FishHunterRecorder w;
	w.show();
	return a.exec();
}
