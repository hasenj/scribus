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

#define USPACE QString(QChar(0xA0))

extern ScribusApp *ScApp;


void IndexDialog::init()
{
	for (uint i = 5; i < ScApp->doc->Vorlagen.count(); ++i)
		stylesBox->insertItem(ScApp->doc->Vorlagen[i].Vname);
	okButton->setEnabled(FALSE);
	appendButton->setEnabled(FALSE);
	stylesBox->sort();
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
			PageItem *item = ScApp->view->Pages.at(i)->Items.at(j);
			bool newParagraph = TRUE;
			bool inToc = FALSE;
			// paragraphs
			for (uint k = 0; k < item->Ptext.count(); ++k)
			{
				// mark if the style is found
				if (newParagraph && tocStyles.find(item->Ptext.at(k)->cab) != tocStyles.end())
					inToc = TRUE;
				// until the end of the paragraph. replace all " " with non-breakable one
				if (inToc && item->Ptext.at(k)->ch != QChar(13))
				{
					if (item->Ptext.at(k)->ch == " ")
						toc += USPACE;
					else
						toc += item->Ptext.at(k)->ch;
				}
				// append number of the page
				if (inToc && (item->Ptext.at(k)->ch == QChar(13) || k == item->Ptext.count()-1))
				{
					QString pageNo;
					toc += " " + pageNo.setNum(item->OwnPage->PageNr + ScApp->doc->FirstPnum) + QString(QChar(13));
				}
				// set flags for new para
				if (item->Ptext.at(k)->ch == QChar(13) || k == item->Ptext.count()-1)
				{
					newParagraph = TRUE;
					inToc = FALSE;
				}
				else
					newParagraph = FALSE;
			}
		} // for items
	} // for pages

    // create frame on the new page
	ScApp->slotNewPageP(ScApp->doc->PageC, "Normal");
	ScApp->view->GotoPage(ScApp->doc->PageC - 1);
	int itno = ScApp->doc->ActPage->PaintText(ScApp->doc->ActPage->Margins.Left,
											  ScApp->doc->ActPage->Margins.Top,
											  ScApp->doc->PageB - 2*ScApp->doc->ActPage->Margins.Right,
											  ScApp->doc->PageH - 2*ScApp->doc->ActPage->Margins.Bottom,
											  ScApp->doc->Dwidth, ScApp->doc->DpenText);
	ScApp->doc->ActPage->SetRectFrame(ScApp->doc->ActPage->Items.at(itno));
	PageItem *item = ScApp->doc->ActPage->Items.at(itno);
	// text into frame
	toc = "Table" + USPACE + "of" + USPACE + "Contents" + QString(QChar(13)) + toc;
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
	// enforce align BLOCK formating for this frame
	int apMode = ScApp->doc->AppMode;
	item->OwnPage->SelItem.clear();
	item->OwnPage->SelItem.append(item);
	if (item->HasSel)
		ScApp->doc->AppMode = 7;
	ScApp->setNewAbStyle(4); // ALIGN_BLOCK
	ScApp->doc->AppMode = apMode;
	item->OwnPage->Deselect();
	item->paintObj();
	// return
	accept();
}

void IndexDialog::appendButton_pressed()
{
	tocStylesBox->insertItem(stylesBox->currentText());
	stylesBox->removeItem(stylesBox->currentItem());
	tocStylesBox->count() ? okButton->setEnabled(TRUE) : okButton->setEnabled(FALSE);
	stylesBox->sort();
	tocStylesBox->sort();
}

void IndexDialog::removeButton_pressed()
{
	stylesBox->insertItem(tocStylesBox->currentText());
	tocStylesBox->removeItem(tocStylesBox->currentItem());
	tocStylesBox->count() ? okButton->setEnabled(TRUE) : okButton->setEnabled(FALSE);
	stylesBox->sort();
	tocStylesBox->sort();
}

void IndexDialog::stylesBox_highlighted(int)
{
	appendButton->setEnabled(TRUE);
}
