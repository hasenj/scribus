/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

/* $Id$ */

#include "scribus.h"

extern ScribusApp *ScApp;


void IndexDialog::init()
{
	for (uint i = 5; i < ScApp->doc->Vorlagen.count(); ++i)
		stylesBox->insertItem(ScApp->doc->Vorlagen[i].Vname);
	okButton->setEnabled(FALSE);
	appendButton->setEnabled(FALSE);
}

void IndexDialog::cancelButton_pressed()
{
	reject();
}


void IndexDialog::okButton_pressed()
{
	QValueList<uint> tocStyles;
	QString toc("");
	uint tocLength = 0;

    // selected style names into their indexes
	for (uint i = 0; i < tocStylesBox->count(); ++i)
		for (uint j = 5; j < ScApp->doc->Vorlagen.count(); ++j)
			if (ScApp->doc->Vorlagen[j].Vname == tocStylesBox->text(i))
				tocStyles.append(j);

    // pages
	for (uint i = 0; i < ScApp->view->Pages.count(); ++i)
	{
        // items
		for (uint j = 0; j < ScApp->view->Pages.at(i)->Items.count(); ++j)
		{
			tocLength = toc.length();
            // paragraphs
			PageItem *item = ScApp->view->Pages.at(i)->Items.at(j);
			bool newParagraph = TRUE;
			bool inToc = FALSE;
			for (uint k = 0; k < item->Ptext.count(); ++k)
			{
				if (newParagraph && tocStyles.find(item->Ptext.at(k)->cstyle) != tocStyles.end())
					inToc = TRUE;
				if (inToc && item->Ptext.at(k)->ch != QChar(13))
					toc += item->Ptext.at(k)->ch;
				if (item->Ptext.at(k)->ch == QChar(13))
					newParagraph = TRUE;
				else
					newParagraph = FALSE;
			}
            // add page number into ToC
			if (tocLength < toc.length())
			{
				toc += (toc+" %").arg(item->OwnPage->PageNr + ScApp->doc->FirstPnum);
				tocLength = toc.length();
			}
		} // for items
	} // for pages

    // create frame on the new page
	ScApp->slotNewPageP(ScApp->doc->PageC + 1, "Table of Contents");
	ScApp->view->GotoPage(ScApp->doc->PageC);
	int itno = ScApp->doc->ActPage->PaintText(ScApp->doc->ActPage->Margins.Left,
											  ScApp->doc->ActPage->Margins.Top,
											  ScApp->doc->ActPage->Margins.Right,
											  ScApp->doc->ActPage->Margins.Bottom,
											  ScApp->doc->Dwidth, ScApp->doc->DpenText);
	qDebug("1");
	ScApp->doc->ActPage->SetRectFrame(ScApp->doc->ActPage->Items.at(itno));
	qDebug("2");
	PageItem *item = ScApp->doc->ActPage->Items.at(itno);
	qDebug("3");
	// text into frame
	for (uint i = 0; i < toc.length(); ++i)
	{
		struct Pti *hg = new Pti;
		hg->ch = toc[i];
		/*if (hg->ch == QChar(10))
		hg->ch = QChar(13);*/
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
	}
	qDebug("4");
	item->paintObj();
	qDebug("5");
	// return
	accept();
}

void IndexDialog::appendButton_pressed()
{
 QListBoxItem *item = stylesBox->selectedItem();
 tocStylesBox->insertItem(item);
 //stylesBox->removeItem(stylesBox->index(item));
 tocStylesBox->count() ? okButton->setEnabled(TRUE) : okButton->setEnabled(FALSE);
}


void IndexDialog::removeButton_pressed()
{
 QListBoxItem *item = tocStylesBox->selectedItem();
 stylesBox->insertItem(item);
 //tocStylesBox->removeItem(tocStylesBox->index(item));
 tocStylesBox->count() ? okButton->setEnabled(TRUE) : okButton->setEnabled(FALSE);
}


void IndexDialog::stylesBox_selected( const QString & )
{
	if (stylesBox->selectedItem())
		appendButton->setEnabled(TRUE);
}
