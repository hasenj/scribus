/* $Id$ */
#ifndef CWDIALOG_H
#define CWDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "colorwheelwidget.h"
#include <scribus.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QComboBox;
class QListView;
class QListViewItem;
class QPushButton;
class QSpinBox;

class ColorWheelDialog : public QDialog
{
	Q_OBJECT

	public:
		ColorWheelDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
		~ColorWheelDialog();

		QLabel* typeLabel;
		QComboBox* typeCombo;
		QListView* colorList;
		ColorWheel* colorWheel;
		QLabel* previewLabel;
		QLabel* angleLabel;
		QSpinBox* angleSpin;
		QPushButton* addButton;
		QPushButton* cancelButton;

	protected:
		void fillColorList();
		QGridLayout* formLayout;
		QHBoxLayout* mainLayout;
		QVBoxLayout* wheelLayout;
		QSpacerItem* spacer1;
		QHBoxLayout* angleLayout;
		QVBoxLayout* listLayout;
		QHBoxLayout* buttonLayout;
		/** Configuration structure */
		PrefsContext* prefs;
		void setPreview();

	public slots:
		virtual void typeCombo_activated(int);
		virtual void colorWheel_clicked(int, const QPoint &);
		virtual void addButton_clicked();
		virtual void cancelButton_clicked();
		virtual void angleSpin_valueChanged(int);

	protected slots:
		virtual void languageChange();

};

#endif // CWDIALOG_H
