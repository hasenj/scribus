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
		QLabel* angleLabel;
		//QSlider* angleSlider;
		QSpinBox* angleSpin;
		QLabel* brightnessLabel;
		//QSlider* brightnessSlider;
		QSpinBox* brightnessSpin;
		QPushButton* addButton;
		QPushButton* cancelButton;

	protected:
		void fillColorList();
		QGridLayout* formLayout;
		QHBoxLayout* mainLayout;
		QVBoxLayout* wheelLayout;
		QSpacerItem* spacer1;
		QHBoxLayout* angleLayout;
		QHBoxLayout* brightnessLayout;
		QVBoxLayout* listLayout;
		QHBoxLayout* buttonLayout;

	public slots:
		virtual void typeCombo_activated(int);
		virtual void colorWheel_clicked(int, const QPoint &);
		//virtual void angleSlider_sliderMoved(int);
		//virtual void brightnessSlider_sliderMoved(int);
		virtual void addButton_clicked();
		virtual void cancelButton_clicked();
		virtual void brightnessSpin_valueChanged(int);
		virtual void angleSpin_valueChanged(int);

	protected slots:
		virtual void languageChange();

};

#endif // CWDIALOG_H
