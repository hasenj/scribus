/*! This is the Scribus Short Words plugin interface implementation.

This code is based on the Scribus-Vlna plug in rewritten for
international use.

2004 Petr Vanek <petr@yarpen.cz>

This program is free software - see LICENSE file in the distribution
or documentation
*/

#include "shortwords.h"
#include "version.h"
#include "vlnadialog.h"

#include <scribus.h>
#include <qmessagebox.h>
#include <qtextcodec.h>
#include <qcursor.h>
#include <qprogressdialog.h>
#include <qfile.h>
#include <qdir.h>

ShortWords* shortWords;
extern ScribusApp *ScApp;

QString Name()
{
	return shortWords->tr("Short &Words...");
}


int Type()
{
	return 1;
}

int ID()
{
	return 11;
}

void Run(QWidget *d, ScribusApp *plug)
{
	// translator TODO: dont use locale but scribus internal coding
	QString pPath = QDir::convertSeparators(PLUGINDIR);
	QTranslator *trans = new QTranslator(0);
	trans->load(QString("libscribusshortwords.") + QString(QTextCodec::locale()).left(2) +QString(".qm"), pPath);
	qApp->installTranslator(trans);
	// run plug
	ShortWords *sw = new ShortWords();
	delete sw;
	delete trans;
}

ShortWords::ShortWords()
{
	shortWords = this;
	originalPage = ScApp->doc->ActPage->PageNr;
	cfg = new Config();
	parse = new Parse();
	VlnaDialog *dlg = new VlnaDialog(ScApp, "dlg", TRUE, 0);

	cfg->userConfig ? dlg->userCheckBox->setChecked(TRUE) : dlg->userCheckBox->setChecked(FALSE);
	dlg->selectAction(cfg->action);
	if (dlg->exec() == QDialog::Accepted) {
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
		ScApp->FMess->setText(shortWords->tr("Short Words processing. Wait please..."));
		dlg->userCheckBox->isChecked() ? cfg->userConfig = 1 : cfg->userConfig = 0;
		cfg->action = dlg->actionSelected;
		switch (dlg->actionSelected) {
			case 0:
				parse->parseSelection();
				break;
			case 1:
				parse->parsePage(ScApp->doc->ActPage);
				break;
			case 2:
				parse->parseAll();
				break;
		} // switch
		// enable "Save" icon
		if (parse->modify > 0)
			ScApp->slotDocCh(TRUE);
		// redraw document
		ScApp->view->DrawNew();
		QApplication::restoreOverrideCursor();
		ScApp->FMess->setText(shortWords->tr("Short Words processing. Done."));
		ScApp->FProg->reset();
		// set page where user calls vlna
		ScApp->view->GotoPage(originalPage);
	} // action
	delete dlg;
} // constructor

ShortWords::~ShortWords()
{
	delete cfg;
	delete parse;
}
