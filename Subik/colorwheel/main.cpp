#include "cwdialog.h"
#include <qapplication.h>

int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	ColorWheelDialog *dia = new ColorWheelDialog();
	a.setMainWidget( dia );
	dia->show();
	return a.exec();
}
