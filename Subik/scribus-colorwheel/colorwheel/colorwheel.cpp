/* $Id$ */
#include "colorwheel.h"
#include "cwdialog.h"
#include "pluginmanager.h"
#include <qcursor.h>
#include <qlistview.h>

QString name()
{
	return QObject::tr("&Color Wheel");
}

PluginManager::PluginType type()
{
	return PluginManager::Standard;
}

int ID()
{
	return 66;
}


QString actionName()
{
	return "ColorWheel";
}

QString actionKeySequence()
{
	return "";
}

QString actionMenu()
{
	return "Extras";
}

QString actionMenuAfterName()
{
	return "";
}

bool actionEnabledOnStartup()
{
	return true;
}

/**
Create dialog and insert font into Style menu when user accepts.
*/
void run(QWidget *d, ScribusApp */*plug*/)
{
	ColorWheelDialog *dlg = new ColorWheelDialog(d, "dlg", TRUE, 0);
	// run it and wait for user's reaction
	if (dlg->exec() == QDialog::Accepted)
	{
	    qDebug("exec");
	/*
		if  (plug->pluginManager->dllInput == "")
			plug->SetNewFont(dlg->fontList->currentItem()->text(0));
		else
			plug->pluginManager->dllReturn = dlg->fontList->currentItem()->text(0);
			*/
	}
	delete dlg;
}
