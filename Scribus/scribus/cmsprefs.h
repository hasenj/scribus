#ifndef CMSPREFS_H
#define CMSPREFS_H

#include <qwidget.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include "scribusstructs.h"

class CMSPrefs : public QWidget
{
	Q_OBJECT

public:
	CMSPrefs( QWidget* parent, CMSData *Vor, ProfilesL *InputProfiles, ProfilesL *PrinterProfiles, ProfilesL *MonitorProfiles);
	~CMSPrefs() {};

	QCheckBox* checkBox1;
	QGroupBox* sysProfiles;
	QLabel* text2;
	QLabel* text1;
	QLabel* text3;
	QLabel* text4;
	QComboBox* inputP;
	QComboBox* inputP2;
	QComboBox* monitorP;
	QComboBox* printerP;
	QGroupBox* render;
	QLabel* text22;
	QComboBox* monitorI;
	QComboBox* printerI;
	QLabel* text21;
	QCheckBox* simulate;
	QCheckBox* gamutC;
	QCheckBox* blackP;
	CMSData *prefs;
	bool changed;

public slots:
	virtual void slotCMSon();
	virtual void setValues();
	virtual void slotSimula();

signals:
	void cmsOn(bool);

protected:
	QVBoxLayout* cmsPrefsLayout;
	QGridLayout* sysProfilesLayout;
	QGridLayout* renderLayout;
};

#endif // CMSPREFS_H
