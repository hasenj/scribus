#include "loremipsum.h"
#include "loremconfig.h"
#include "loremnetwork.h"
#include "loremturkey.h"
#include "loremdialog.h"
#include "loremstandard.h"

#include <qcombobox.h>
#include <qtabwidget.h>

extern ScribusApp *ScApp;


QString Name()
{
	return QObject::tr("&Lorem Ipsum...");
}

int Type()
{
	return 1;
}

int ID()
{
	return 666;
}

#include <iostream.h>
void Run(QWidget *d, ScribusApp *plug)
{
	// only one selection check
	if (ScApp->doc->ActPage->SelItem.count() != 1)
	{
		ScApp->FMess->setText("Select only one frame");
		return;
	}
	PageItem *item = ScApp->doc->ActPage->Items.at(ScApp->doc->ActPage->SelItem.at(0)->ItemNr);
	if (item->Ptext.count() != 0)
	{
		ScApp->FMess->setText("Cannot replace text in the frame");
		return;
	}
	// types of the lorems
	LoremDialog *dia = new LoremDialog(ScApp, 0, TRUE, 0);
	LoremConfig *config = new LoremConfig();
	LoremInfo *info;
	for (info = config->info.first(); info; info = config->info.next())
	{
		QListViewItem *listItem = new QListViewItem(dia->dictionaryView, info->name, info->description, info->url);
		if (info->type == "turkey")
			dia->dictionaryView->insertItem(listItem);
		else
			dia->networkView->insertItem(listItem);
	}
	// GUI
	if (dia->exec() == QDialog::Accepted)
	{
		// handling options etc.
		QString loremText = "";
		if (dia->tabWidget->currentPage() == dia->turkeyTab)
		{
			LoremTurkey *lorem = new LoremTurkey(dia->dictionaryView->currentItem()->text(2),
												dia->turkeyParagraphs->value(),
												dia->avgSentences->value(),
												dia->turkeyStartLorem->isChecked()
												);
			loremText = lorem->makeLorem();
			delete lorem;
		}
		if (dia->tabWidget->currentPage() == dia->networkTab)
		{
			qDebug(dia->networkView->currentItem()->text(2));
			LoremNetwork *lorem = new LoremNetwork(dia->networkView->currentItem()->text(2));
			loremText = lorem->makeLorem();
			delete lorem;
		}
		if (dia->tabWidget->currentPage() == dia->standardTab)
		{
			LoremStandard *lorem = new LoremStandard(dia->standardParaBox->value());
			loremText = lorem->makeLorem();
			delete lorem;
		}

		// fill text into frame
		item->Ptext.clear();
		for (uint i = 0; i < loremText.length(); ++i)
		{
			struct Pti *hg = new Pti;
			hg->ch = loremText.at(i);
			if (hg->ch == QChar(10))
				hg->ch = QChar(13);
			hg->cfont = item->IFont;
			hg->csize = item->ISize;
			hg->ccolor = item->TxtFill;
			hg->cshade = item->ShTxtFill;
			hg->cstroke = item->TxtStroke;
			hg->cshade2 = item->ShTxtStroke;
			hg->cscale = item->TxtScale;
			hg->cextra = 0;
			hg->cselect = false;
			hg->cstyle = 0;
			hg->cab = ScApp->doc->CurrentABStil;
			hg->xp = 0;
			hg->yp = 0;
			hg->PRot = 0;
			hg->PtransX = 0;
			hg->PtransY = 0;
			item->Ptext.append(hg);
		} // for
	}
	//ScApp->FMess->setText(resultComment);
	ScApp->FMess->setText("DONE");
	delete config;
	delete dia;
	delete info;
}

/*
 QString resultComment()
{
    QStringList comment;
    comment.append("Remarkably well done!");
    comment.append("Beautiful execution, what a fabulous $lang1!!");
    comment.append("Extremely well done!");
    comment.append("Very well done!");
    comment.append("Magnificently well done!");
    comment.append("Superb performance, exquisite $lang1 delivered!");
    comment.append("No doubt, the mother of all $lang1! Perfect.");
    comment.append("Brilliant execution, this is a beauty!");
    comment.append("Extraordinary performance!");
    comment.append("This $lang1 is perfect!");
    comment.append("Congratulate yourself ...the mother of 'em $lang1!");
    comment.append("Fella, you now how to press a button, respect!");
    comment.append("Best $lang1 ever generated, governor!");
    comment.append("Awesome result, give yourself a hand!");
    comment.append("Have a cigar - this $lang1 is sweet!");
	return(*comment.at(rand()%comment.count()+1));
}

*/

