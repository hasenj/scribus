#ifndef CWDIALOG_H
#define CWDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "colorwheelwidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QComboBox;
class QListView;
class QListViewItem;

class ColorWheelDialog : public QDialog
{
	Q_OBJECT

	public:
		ColorWheelDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
		~ColorWheelDialog();

		QComboBox* typeCombo;
		QListView* colorList;
		ColorWheel* colorWheel;

	public slots:
		virtual void typeCombo_activated(int);
		virtual void colorWheel_clicked(int, const QPoint &);

	protected slots:
		virtual void languageChange();

};

#endif // CWDIALOG_H
