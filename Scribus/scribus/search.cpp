/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#include "search.h"
#include "search.moc"

#include <qvariant.h>
#include <qregexp.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qmessagebox.h>

#include "colorm.h"
#include "commonstrings.h"
#include "colorcombo.h"
#include "fontcombo.h"
#include "mspinbox.h"
#include "page.h"
#include "prefscontext.h"
#include "prefsfile.h"
#include "prefsmanager.h"
#include "scribus.h"
#include "shadebutton.h"
#include "story.h"
#include "styleselect.h"
#include "util.h"
#include "text/nlsconfig.h"


extern QPixmap loadIcon(QString nam);

SearchReplace::SearchReplace( QWidget* parent, ScribusDoc *doc, PageItem* ite, bool mode )
	: QDialog( parent, "SearchReplace", true, 0 ),
	matchesFound(0)
{
	setCaption( tr( "Search/Replace" ) );
	setIcon(loadIcon("AppIcon.png"));
	ColorList::Iterator it;
	Item = ite;
	Doc = doc;
	NotFound = false;
	SMode = mode;
	SearchReplaceLayout = new QVBoxLayout( this, 10, 5, "SearchReplaceLayout");
	SelLayout = new QHBoxLayout( 0, 0, 6, "SelLayout");
	Search = new QGroupBox( this, "Search" );
	Search->setTitle( tr( "Search for:" ) );
	Search->setColumnLayout(0, Qt::Vertical );
	Search->layout()->setSpacing( 2 );
	Search->layout()->setMargin( 5 );
	SearchLayout = new QGridLayout( Search->layout() );
	SearchLayout->setAlignment( Qt::AlignTop );
	SText = new QCheckBox( Search, "SText" );
	SText->setText( tr( "Text" ) );
	SearchLayout->addWidget( SText, 0, 0 );
	SStyle = new QCheckBox( Search, "SStyle" );
	SStyle->setText( tr( "Paragraph Style" ) );
	SearchLayout->addWidget( SStyle, 1, 0 );
	SFont = new QCheckBox( Search, "SFont" );
	SFont->setText( tr( "Font" ) );
	SearchLayout->addWidget( SFont, 2, 0 );
	SSize = new QCheckBox( Search, "SSize" );
	SSize->setText( tr( "Font Size" ) );
	SearchLayout->addWidget( SSize, 3, 0 );
	SEffect = new QCheckBox( Search, "SEffect" );
	SEffect->setText( tr( "Font Effects" ) );
	SearchLayout->addWidget( SEffect, 4, 0 );
	SFill = new QCheckBox( Search, "SFill" );
	SFill->setText( tr( "Fill Color" ) );
	SearchLayout->addWidget( SFill, 5, 0 );
	SFillS = new QCheckBox( Search, "SFillS" );
	SFillS->setText( tr( "Fill Shade" ) );
	SearchLayout->addWidget( SFillS, 6, 0 );
	SStroke = new QCheckBox( Search, "SStroke" );
	SStroke->setText( tr( "Stroke Color" ) );
	SearchLayout->addWidget( SStroke, 7, 0 );
	SStrokeS = new QCheckBox( Search, "SStrokeS" );
	SStrokeS->setText( tr( "Stroke Shade" ) );
	SearchLayout->addWidget( SStrokeS, 8, 0 );
	STextVal = new QLineEdit( Search, "STextVal" );
	STextVal->setEnabled(false);
	SearchLayout->addWidget( STextVal, 0, 1 );
	SStyleVal = new QComboBox( true, Search, "SStyleVal" );
	SStyleVal->setEditable(false);
	QString tmp_sty[] = { tr("Left"), tr("Center"), tr("Right"), tr("Block"), tr("Forced")};
	size_t ar_sty = sizeof(tmp_sty) / sizeof(*tmp_sty);
	for (uint a = 0; a < ar_sty; ++a)
		SStyleVal->insertItem(tmp_sty[a]);
	if (doc->docParagraphStyles.count() > 5)
	{
		for (uint x = 5; x < doc->docParagraphStyles.count(); ++x)
			SStyleVal->insertItem(doc->docParagraphStyles[x].name());
	}
	SStyleVal->listBox()->setMinimumWidth(SStyleVal->listBox()->maxItemWidth()+24);
	SStyleVal->setCurrentItem(findParagraphStyle(doc, doc->currentStyle));
	SStyleVal->setEnabled(false);
	SearchLayout->addWidget( SStyleVal, 1, 1 );
	SFontVal = new FontCombo(Search);
	SFontVal->setMaximumSize(190, 30);
	SFontVal->setCurrentText(doc->currentStyle.charStyle().font()->scName());
	SFontVal->setEnabled(false);
	SearchLayout->addWidget( SFontVal, 2, 1 );
	SSizeVal = new MSpinBox( Search, 1 );
	SSizeVal->setSuffix( tr( " pt" ) );
	SSizeVal->setMinValue( 0.5 );
	SSizeVal->setMaxValue( 2048 );
	SSizeVal->setValue( doc->currentStyle.charStyle().fontSize() / 10.0 );
	SSizeVal->setEnabled(false);
	SearchLayout->addWidget( SSizeVal, 3, 1 );
	SEffVal = new StyleSelect( Search );
	SEffVal->setStyle(0);
	SEffVal->setEnabled(false);
	SearchLayout->addWidget( SEffVal, 4, 1, Qt::AlignLeft );
	SFillVal = new ColorCombo( true, Search, "SFillVal" );
	SFillVal->setEditable(false);
	SFillVal->insertItem(CommonStrings::NoneColor);
	for (it = doc->PageColors.begin(); it != doc->PageColors.end(); ++it)
	{
		SFillVal->insertWideItem( doc->PageColors[it.key()], it.key() );
	}
	SFillVal->listBox()->setMinimumWidth(SFillVal->listBox()->maxItemWidth()+24);
	SFillVal->setCurrentText(doc->currentStyle.charStyle().fillColor());
	SFillVal->setEnabled(false);
	SearchLayout->addWidget( SFillVal, 5, 1 );
	SFillSVal = new ShadeButton(Search);
	SFillSVal->setEnabled(false);
	SearchLayout->addWidget( SFillSVal, 6, 1, Qt::AlignLeft );
	SStrokeVal = new ColorCombo( true, Search, "SStrokeVal" );
	SStrokeVal->setEditable(false);
	SStrokeVal->insertItem(CommonStrings::NoneColor);
	for (it = doc->PageColors.begin(); it != doc->PageColors.end(); ++it)
	{
		SStrokeVal->insertWideItem( doc->PageColors[it.key()], it.key() );
	}
	SStrokeVal->listBox()->setMinimumWidth(SStrokeVal->listBox()->maxItemWidth()+24);
	SStrokeVal->setCurrentText(doc->currentStyle.charStyle().strokeColor());
	SStrokeVal->setEnabled(false);
	SearchLayout->addWidget( SStrokeVal, 7, 1 );
	SStrokeSVal =  new ShadeButton(Search);
	SStrokeSVal->setEnabled(false);
	SearchLayout->addWidget( SStrokeSVal, 8, 1, Qt::AlignLeft );
	SelLayout->addWidget( Search );

	Replace = new QGroupBox( this, "Replace" );
	Replace->setTitle( tr( "Replace with:" ) );
	Replace->setColumnLayout(0, Qt::Vertical );
	Replace->layout()->setSpacing( 2 );
	Replace->layout()->setMargin( 5 );
	ReplaceLayout = new QGridLayout( Replace->layout() );
	ReplaceLayout->setAlignment( Qt::AlignTop );
	RText = new QCheckBox( Replace, "RText" );
	RText->setText( tr( "Text" ) );
	ReplaceLayout->addWidget( RText, 0, 0 );
	RStyle = new QCheckBox( Replace, "RStyle" );
	RStyle->setText( tr( "Paragraph Style" ) );
	ReplaceLayout->addWidget( RStyle, 1, 0 );
	RFont = new QCheckBox( Replace, "RFont" );
	RFont->setText( tr( "Font" ) );
	ReplaceLayout->addWidget( RFont, 2, 0 );
	RSize = new QCheckBox( Replace, "RSize" );
	RSize->setText( tr( "Font Size" ) );
	ReplaceLayout->addWidget( RSize, 3, 0 );
	REffect = new QCheckBox( Replace, "REffect" );
	REffect->setText( tr( "Font Effects" ) );
	ReplaceLayout->addWidget( REffect, 4, 0 );
	RFill = new QCheckBox( Replace, "RFill" );
	RFill->setText( tr( "Fill Color" ) );
	ReplaceLayout->addWidget( RFill, 5, 0 );
	RFillS = new QCheckBox( Replace, "RFillS" );
	RFillS->setText( tr( "Fill Shade" ) );
	ReplaceLayout->addWidget( RFillS, 6, 0 );
	RStroke = new QCheckBox( Replace, "RStroke" );
	RStroke->setText( tr( "Stroke Color" ) );
	ReplaceLayout->addWidget( RStroke, 7, 0 );
	RStrokeS = new QCheckBox( Replace, "RStrokeS" );
	RStrokeS->setText( tr( "Stroke Shade" ) );
	ReplaceLayout->addWidget( RStrokeS, 8, 0 );
	RTextVal = new QLineEdit( Replace, "RTextVal" );
	RTextVal->setEnabled(false);
	ReplaceLayout->addWidget( RTextVal, 0, 1 );
	RStyleVal = new QComboBox( true, Replace, "RStyleVal" );
	RStyleVal->setEditable(false);
	for (uint a = 0; a < ar_sty; ++a)
		RStyleVal->insertItem(tmp_sty[a]);
	if (doc->docParagraphStyles.count() > 5)
	{
		for (uint x = 5; x < doc->docParagraphStyles.count(); ++x)
			RStyleVal->insertItem(doc->docParagraphStyles[x].name());
	}
	RStyleVal->listBox()->setMinimumWidth(RStyleVal->listBox()->maxItemWidth()+24);
	RStyleVal->setCurrentItem(findParagraphStyle(doc, doc->currentStyle));
	RStyleVal->setEnabled(false);
	ReplaceLayout->addWidget( RStyleVal, 1, 1 );
	RFontVal = new FontCombo(Replace);
	RFontVal->setMaximumSize(190, 30);
	RFontVal->setCurrentText(doc->currentStyle.charStyle().font()->scName());
	RFontVal->setEnabled(false);
	ReplaceLayout->addWidget( RFontVal, 2, 1 );
	RSizeVal = new MSpinBox( Replace, 1 );
	RSizeVal->setSuffix( tr( " pt" ) );
	RSizeVal->setMinValue( 0.5 );
	RSizeVal->setMaxValue( 2048 );
	RSizeVal->setValue( doc->currentStyle.charStyle().fontSize() / 10.0 );
	RSizeVal->setEnabled(false);
	ReplaceLayout->addWidget( RSizeVal, 3, 1 );
	REffVal = new StyleSelect( Replace );
	REffVal->setStyle(0);
	REffVal->setEnabled(false);
	ReplaceLayout->addWidget( REffVal, 4, 1, Qt::AlignLeft );
	RFillVal = new ColorCombo( true, Replace, "RFillVal" );
	RFillVal->setEditable(false);
	RFillVal->insertItem(CommonStrings::NoneColor);
	for (it = doc->PageColors.begin(); it != doc->PageColors.end(); ++it)
	{
		RFillVal->insertWideItem( doc->PageColors[it.key()], it.key() );
	}
	RFillVal->listBox()->setMinimumWidth(RFillVal->listBox()->maxItemWidth()+24);
	RFillVal->setCurrentText(doc->currentStyle.charStyle().fillColor());
	RFillVal->setEnabled(false);
	ReplaceLayout->addWidget( RFillVal, 5, 1 );
	RFillSVal = new ShadeButton(Replace);
	RFillSVal->setEnabled(false);
	ReplaceLayout->addWidget( RFillSVal, 6, 1, Qt::AlignLeft );
	RStrokeVal = new ColorCombo( true, Replace, "RStrokeVal" );
	RStrokeVal->setEditable(false);
	RStrokeVal->insertItem(CommonStrings::NoneColor);
	for (it = doc->PageColors.begin(); it != doc->PageColors.end(); ++it)
	{
		RStrokeVal->insertWideItem( doc->PageColors[it.key()], it.key() );
	}
	RStrokeVal->listBox()->setMinimumWidth(RStrokeVal->listBox()->maxItemWidth()+24);
	RStrokeVal->setCurrentText(doc->currentStyle.charStyle().strokeColor());
	RStrokeVal->setEnabled(false);
	ReplaceLayout->addWidget( RStrokeVal, 7, 1 );
	RStrokeSVal = new ShadeButton(Replace);;
	RStrokeSVal->setEnabled(false);
	ReplaceLayout->addWidget( RStrokeSVal, 8, 1, Qt::AlignLeft );
	SelLayout->addWidget( Replace );
	SearchReplaceLayout->addLayout( SelLayout );

	OptsLayout = new QHBoxLayout( 0, 0, 6, "OptsLayout");
	Word = new QCheckBox( tr( "&Whole Word" ), this, "Word" );
	if (mode)
		Word->setEnabled(false);
	OptsLayout->addWidget( Word );
	CaseIgnore = new QCheckBox( tr( "&Ignore Case" ), this, "CaseIgnore" );
	if (mode)
		CaseIgnore->setEnabled(false);
	OptsLayout->addWidget( CaseIgnore );
	SearchReplaceLayout->addLayout( OptsLayout );

	ButtonsLayout = new QHBoxLayout( 0, 0, 4, "ButtonsLayout");
	DoSearch = new QPushButton( tr( "&Search" ), this, "DoSearch" );
	DoSearch->setDefault( true );
	ButtonsLayout->addWidget( DoSearch );
	DoReplace = new QPushButton( tr( "&Replace" ), this, "DoReplace" );
	DoReplace->setEnabled(false);
	ButtonsLayout->addWidget( DoReplace );
	AllReplace = new QPushButton( tr( "Replace &All" ), this, "DoReplace" );
	AllReplace->setEnabled(false);
	ButtonsLayout->addWidget( AllReplace );
	clearButton = new QPushButton( tr("C&lear"), this, "clearButton");
	ButtonsLayout->addWidget(clearButton);
	Leave = new QPushButton( tr( "&Close" ), this, "Leave" );
	ButtonsLayout->addWidget( Leave );
	SearchReplaceLayout->addLayout( ButtonsLayout );

	resize(minimumSizeHint());

 // signals and slots connections
	connect( Leave, SIGNAL( clicked() ), this, SLOT( writePrefs() ) );
	connect( DoSearch, SIGNAL( clicked() ), this, SLOT( slotSearch() ) );
	connect( DoReplace, SIGNAL( clicked() ), this, SLOT( slotReplace() ) );
	connect( AllReplace, SIGNAL( clicked() ), this, SLOT( slotReplaceAll() ) );
	connect( SText, SIGNAL( clicked() ), this, SLOT( enableTxSearch() ) );
	connect( SStyle, SIGNAL( clicked() ), this, SLOT( enableStyleSearch() ) );
	connect( SFont, SIGNAL( clicked() ), this, SLOT( enableFontSearch() ) );
	connect( SSize, SIGNAL( clicked() ), this, SLOT( enableSizeSearch() ) );
	connect( SEffect, SIGNAL( clicked() ), this, SLOT( enableEffSearch() ) );
	connect( SFill, SIGNAL( clicked() ), this, SLOT( enableFillSearch() ) );
	connect( SFillS, SIGNAL( clicked() ), this, SLOT( enableFillSSearch() ) );
	connect( SStrokeS, SIGNAL( clicked() ), this, SLOT( enableStrokeSSearch() ) );
	connect( SStroke, SIGNAL( clicked() ), this, SLOT( enableStrokeSearch() ) );
	connect( RText, SIGNAL( clicked() ), this, SLOT( enableTxReplace() ) );
	connect( RStyle, SIGNAL( clicked() ), this, SLOT( enableStyleReplace() ) );
	connect( RFont, SIGNAL( clicked() ), this, SLOT( enableFontReplace() ) );
	connect( RSize, SIGNAL( clicked() ), this, SLOT( enableSizeReplace() ) );
	connect( REffect, SIGNAL( clicked() ), this, SLOT( enableEffReplace() ) );
	connect( RFill, SIGNAL( clicked() ), this, SLOT( enableFillReplace() ) );
	connect( RStroke, SIGNAL( clicked() ), this, SLOT( enableStrokeReplace() ) );
	connect( RFillS, SIGNAL( clicked() ), this, SLOT( enableFillSReplace() ) );
	connect( RStrokeS, SIGNAL( clicked() ), this, SLOT( enableStrokeSReplace() ) );
	connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));

 // tab order
	setTabOrder( SText, SStyle );
	setTabOrder( SStyle, SFont );
	setTabOrder( SFont, SSize );
	setTabOrder( SSize, SEffect );
	setTabOrder( SEffect, SFill );
	setTabOrder( SFill, SStroke );
	setTabOrder( SStroke, STextVal );
	setTabOrder( STextVal, SStyleVal );
	setTabOrder( SStyleVal, SFontVal );
	setTabOrder( SFontVal, SSizeVal );
	setTabOrder( SSizeVal, SEffVal );
	setTabOrder( SEffVal, SFillVal );
	setTabOrder( SFillVal, SStrokeVal );
	setTabOrder( SStrokeVal, RText );
	setTabOrder( RText, RStyle );
	setTabOrder( RStyle, RFont );
	setTabOrder( RFont, RSize );
	setTabOrder( RSize, REffect );
	setTabOrder( REffect, RFill );
	setTabOrder( RFill, RStroke );
	setTabOrder( RStroke, RTextVal );
	setTabOrder( RTextVal, RStyleVal );
	setTabOrder( RStyleVal, RFontVal );
	setTabOrder( RFontVal, RSizeVal );
	setTabOrder( RSizeVal, REffVal );
	setTabOrder( REffVal, RFillVal );
	setTabOrder( RFillVal, RStrokeVal );
	setTabOrder( RStrokeVal, Word );
	setTabOrder( Word, CaseIgnore );
	setTabOrder( CaseIgnore, DoSearch );
	setTabOrder( DoSearch, DoReplace );
	setTabOrder( DoReplace, AllReplace );
	setTabOrder( AllReplace, Leave );

	prefs = PrefsManager::instance()->prefsFile->getContext("SearchReplace");
	readPrefs();
}

void SearchReplace::slotSearch()
{
	if (SMode)
		ScMW->view->slotDoCurs(false);
	slotDoSearch();
	if (SMode)
	{
		ScMW->view->slotDoCurs(true);
		ScMW->view->RefreshItem(Item);
	}
}

void SearchReplace::slotDoSearch()
{
	int maxChar = Item->itemText.length() - 1;
	DoReplace->setEnabled(false);
	AllReplace->setEnabled(false);
	if (SMode)
	{
		Item->itemText.deselectAll();
		Item->HasSel = false;
	}
	QString fCol = "";
	QString sCol = "";
	QString sFont = "";
	QString sText = "";
	NotFound = true;
	int sStyle = 0;
	int sSize = 0;
	int sEff = 0;
	int sFillSh = 100;
	int sStrokeSh = 100;
	bool rep = false;
	bool found = true;
	if ((RFill->isChecked()) || (RStroke->isChecked()) || (RStyle->isChecked()) || (RFont->isChecked())
		|| (RStrokeS->isChecked()) || (RFillS->isChecked()) || (RSize->isChecked()) || (RText->isChecked())
		|| (REffect->isChecked()))
		rep = true;
	if (SText->isChecked())
		sText = STextVal->text();
	if (CaseIgnore->isChecked())
		sText = sText.lower();
	if (SEffect->isChecked())
		sEff = SEffVal->getStyle();
	if (SFill->isChecked())
		fCol = SFillVal->currentText();
	if (SFillS->isChecked())
		sFillSh = SFillSVal->getValue();
	if (SStroke->isChecked())
		sCol = SStrokeVal->currentText();
	if (SStrokeS->isChecked())
		sStrokeSh = SStrokeSVal->getValue();
	if (SFont->isChecked())
		sFont = SFontVal->currentText();
	if (SStyle->isChecked())
		sStyle = SStyleVal->currentItem();
	if (SSize->isChecked())
		sSize = qRound(SSizeVal->value() * 10);
	if (sText.length() > 0)
		found = false;
	uint inde = 0;
	uint as = Item->CPos;
	ReplStart = as;
	int a;
	if (SMode)
	{
		for (a = as; a < Item->itemText.length(); ++a)
		{
			if (SText->isChecked())
			{
				QString chx = Item->itemText.text(a,1);
				if (CaseIgnore->isChecked())
					chx = chx.lower();
				found = chx == sText.mid(inde, 1) ? true : false;
				if ((Word->isChecked()) && (inde == 0) && (chx[0].isSpace()))
					found = true;
			}
			else
				found = true;
			if (SSize->isChecked())
			{
				if (Item->itemText.charStyle(a).fontSize() != sSize)
					found = false;
			}
			if (SFont->isChecked())
			{
				if (Item->itemText.charStyle(a).font()->scName() != sFont)
					found = false;
			}
#ifndef NLS_PROTO
			if (SStyle->isChecked())
			{
				if (Item->itemText.at(a)->cab != sStyle)
					found = false;
			}
#endif
			if (SStroke->isChecked())
			{
				if (Item->itemText.charStyle(a).strokeColor() != sCol)
					found = false;
			}
			if (SStrokeS->isChecked())
			{
				if (Item->itemText.charStyle(a).strokeShade() != sStrokeSh)
					found = false;
			}
			if (SFillS->isChecked())
			{
				if (Item->itemText.charStyle(a).fillShade() != sFillSh)
					found = false;
			}
			if (SEffect->isChecked())
				{
				if ((Item->itemText.charStyle(a).effects() & 1919) != sEff)
					found = false;
				}
			if (SFill->isChecked())
			{
				if (Item->itemText.charStyle(a).fillColor() != fCol)
					found = false;
			}
			if (found)
			{
				Item->itemText.select(a,1);
				Item->HasSel = true;
				if (rep)
				{
					DoReplace->setEnabled(true);
					AllReplace->setEnabled(true);
				}
				Item->CPos = a+1;
				if (SText->isChecked())
				{
					if (inde == 0)
						ReplStart = a;
					inde++;
					if ((Word->isChecked()) && (inde == 1) && (Item->itemText.text(a).isSpace()))
					{
						inde--;
						Item->itemText.select(a, 1, false);
					}
					if ( Word->isChecked()  &&  inde == sText.length()  &&
						! Item->itemText.text(QMIN(a+1, maxChar)).isSpace() )
					{
						for (int xx = ReplStart; xx < a+1; ++xx)
							Item->itemText.select(QMIN(xx, maxChar), 1, false);
						Item->HasSel = false;
						inde = 0;
						found = false;
					}
					else
					{
						if (inde == sText.length())
							break;
					}
				}
				else
					break;
			}
			else
			{
				if (SText->isChecked())
				{
					for (int xx = ReplStart; xx < a+1; ++xx)
						Item->itemText.select(QMIN(xx, maxChar), 1, false);
					Item->HasSel = false;
				}
				inde = 0;
			}
		}
		if ((!found) || (a == Item->itemText.length()))
		{
			Doc->DoDrawing = true;
			ScMW->view->RefreshItem(Item);
			DoReplace->setEnabled(false);
			AllReplace->setEnabled(false);
			QMessageBox::information(this, tr("Search/Replace"), tr("Search finished"), CommonStrings::tr_OK);
			Item->CPos = 0;
			NotFound = false;
		}
	}
	else
	{
		if (ScMW->CurrStED != NULL)
		{
			int p, i;
			ScMW->CurrStED->Editor->getCursorPosition(&p, &i);
			uint inde = 0;
			int as = i;
			uint fpa = p;
			int fch = i;
			found = false;
			if (ScMW->CurrStED->Editor->StyledText.count() != 0)
			{
				for (uint pa = p; pa < ScMW->CurrStED->Editor->StyledText.count(); ++pa)
				{
					SEditor::ChList *chars;
					chars = ScMW->CurrStED->Editor->StyledText.at(pa);
					if (SText->isChecked())
					{
						if (Word->isChecked())
						{
							QRegExp rx( "(\\b"+sText+"\\b)" );
							if (CaseIgnore->isChecked())
								as = rx.search( ScMW->CurrStED->Editor->text(pa).lower(), i );
							else
								as = rx.search( ScMW->CurrStED->Editor->text(pa), i );
						}
						else
						{
							if (CaseIgnore->isChecked())
								as = ScMW->CurrStED->Editor->text(pa).lower().find(sText, i);
							else
								as = ScMW->CurrStED->Editor->text(pa).find(sText, i);
						}
						if (as != -1)
						{
							fch = as;
							fpa = pa;
							found = true;
							inde = 0;
							for (uint ap = 0; ap < sText.length(); ++ap)
							{
								struct PtiSmall *hg;
								hg = chars->at(as+ap);
								if ((SSize->isChecked()) && (hg->charStyle.fontSize() != sSize))
									found = false;
								if ((SFont->isChecked()) && (hg->charStyle.font()->scName() != sFont))
									found = false;
								if ((SStyle->isChecked()) && (hg->cab != sStyle))
									found = false;
								if ((SStroke->isChecked()) && (hg->charStyle.strokeColor() != sCol))
									found = false;
								if ((SStrokeS->isChecked()) && (hg->charStyle.strokeShade() != sStrokeSh))
									found = false;
								if ((SFillS->isChecked()) && (hg->charStyle.fillShade() != sFillSh))
									found = false;
								if ((SEffect->isChecked()) && ((hg->charStyle.effects() & 1919) != sEff))
									found = false;
								if ((SFill->isChecked()) && (hg->charStyle.fillColor() != fCol))
									found = false;
								inde++;
							}
							i = as + inde;
							if (found)
								break;
						}
						else
						{
							i = 0;
							inde = 0;
						}
					}
					else
					{
						for (uint e = i; e < chars->count(); ++e)
						{
							found = true;
							inde = 1;
							struct PtiSmall *hg;
							hg = chars->at(e);
							if ((SSize->isChecked()) && (hg->charStyle.fontSize() != sSize))
								found = false;
							if ((SFont->isChecked()) && (hg->charStyle.font()->scName() != sFont))
								found = false;
							if ((SStyle->isChecked()) && (hg->cab != sStyle))
								found = false;
							if ((SStroke->isChecked()) && (hg->charStyle.strokeColor() != sCol))
								found = false;
							if ((SStrokeS->isChecked()) && (hg->charStyle.strokeShade() != sStrokeSh))
								found = false;
							if ((SFillS->isChecked()) && (hg->charStyle.fillShade() != sFillSh))
								found = false;
							if ((SEffect->isChecked()) && ((hg->charStyle.effects() & 1919) != sEff))
								found = false;
							if ((SFill->isChecked()) && (hg->charStyle.fillColor() != fCol))
								found = false;
							if (found)
							{
								fch = e;
								fpa = pa;
								break;
							}
						}
						if (found)
							break;
						else
							i = 0;
					}
				}
				if (found)
				{
					ScMW->CurrStED->Editor->setSelection(fpa, fch, fpa, fch+inde);
					ScMW->CurrStED->updateProps(fpa, fch);
					ScMW->CurrStED->Editor->setCursorPosition(fpa, fch+inde);
					if (rep)
					{
						DoReplace->setEnabled(true);
						AllReplace->setEnabled(true);
					}
					matchesFound++;
				}
				else
				{
					QMessageBox::information(this, tr("Search/Replace"),
							tr("Search finished, found %1 matches").arg(matchesFound),
							CommonStrings::tr_OK);
					matchesFound = 0;
					NotFound = false;
					ScMW->CurrStED->Editor->removeSelection();
					ScMW->CurrStED->Editor->setCursorPosition(0, 0);
				}
			}
		}
	}
}

void SearchReplace::slotReplace()
{
	if (SMode)
		ScMW->view->slotDoCurs(false);
	slotDoReplace();
	if (SMode)
	{
		ScMW->view->slotDoCurs(true);
		ScMW->view->RefreshItem(Item);
	}
}

void SearchReplace::slotDoReplace()
{
	if (SMode)
	{
		QString repl, sear;
		uint cs, cx;
		ScText *hg;
		if (RText->isChecked())
		{
			repl = RTextVal->text();
			sear = STextVal->text();
			if (sear.length() == repl.length())
			{
				for (cs = 0; cs < sear.length(); ++cs)
					Item->itemText.replaceChar(ReplStart+cs, repl[cs]);
			}
			else
			{
				if (sear.length() < repl.length())
				{
					for (cs = 0; cs < sear.length(); ++cs)
						Item->itemText.replaceChar(ReplStart+cs, repl[cs]);
					for (cx = cs; cx < repl.length(); ++cx)
					{
#ifndef NLS_PROTO
						hg = new ScText;
						hg->ch = repl[cx];
						if (RSize->isChecked())
							hg->setFontSize(qRound(RSizeVal->value() * 10.0));
						else
							hg->setFontSize(Doc->currentStyle.charStyle().fontSize());
						if (RFill->isChecked())
							hg->setFillColor(RFillVal->currentText());
						else
							hg->setFillColor(Doc->currentStyle.charStyle().fillColor());
						hg->setFillShade(Doc->currentStyle.charStyle().fillShade());
						if (RStroke->isChecked())
							hg->setStrokeColor(RStrokeVal->currentText());
						else
							hg->setStrokeColor(Doc->currentStyle.charStyle().strokeColor());
						hg->setStrokeShade(Doc->currentStyle.charStyle().strokeShade());
						hg->setScaleH(Doc->currentStyle.charStyle().scaleH());
						hg->setScaleV(Doc->currentStyle.charStyle().scaleV());
						hg->setBaselineOffset(Doc->currentStyle.charStyle().baselineOffset());
						hg->setShadowXOffset(Doc->currentStyle.charStyle().shadowXOffset());
						hg->setShadowYOffset(Doc->currentStyle.charStyle().shadowYOffset());
						hg->setOutlineWidth(Doc->currentStyle.charStyle().outlineWidth());
						hg->setUnderlineOffset(Doc->currentStyle.charStyle().underlineOffset());
						hg->setUnderlineWidth(Doc->currentStyle.charStyle().underlineWidth());
						hg->setStrikethruOffset(Doc->currentStyle.charStyle().strikethruOffset());
						hg->setStrikethruWidth(Doc->currentStyle.charStyle().strikethruWidth());
						hg->setEffects(Doc->currentStyle.charStyle().effects());
						if (RStyle->isChecked())
							hg->cab = RStyleVal->currentItem();
						else
							hg->cab = findParagraphStyle(Doc, Doc->currentStyle);
						if (Doc->docParagraphStyles[hg->cab].charStyle().font() != &Foi::NONE)
						{
							hg->setFont((*Doc->AllFonts)[Doc->docParagraphStyles[hg->cab].charStyle().font()->scName()]);
							hg->setFontSize(Doc->docParagraphStyles[hg->cab].charStyle().fontSize());
							hg->setEffects(Doc->docParagraphStyles[hg->cab].charStyle().effects());
						}
						if (RFont->isChecked())
							hg->setFont((*Doc->AllFonts)[RFontVal->currentText()]);
						else
							hg->setFont((*Doc->AllFonts)[Doc->currentStyle.charStyle().font()->scName()]);
						hg->setTracking(0);
						Item->itemText.insert(ReplStart+cx, hg);
#else
						Item->itemText.insertChars(ReplStart+cx, repl.mid(cx,1)); 
#endif
					}
					Item->CPos = ReplStart+cx;
				}
				else
				{
					for (cs = 0; cs < repl.length(); ++cs)
						Item->itemText.replaceChar(ReplStart+cs, repl[cs]);
					Item->itemText.removeChars(ReplStart+cs, sear.length() - cs);
					Item->CPos = ReplStart+cs;
				}
			}
		}
		if (RStyle->isChecked())
			emit NewAbs(RStyleVal->currentItem());
		if (RFill->isChecked())
			Doc->ItemTextBrush(RFillVal->currentText());
		if (RFillS->isChecked())
			Doc->ItemTextBrushS(RFillSVal->getValue());
		if (RStroke->isChecked())
			Doc->ItemTextPen(RStrokeVal->currentText());
		if (RStrokeS->isChecked())
			Doc->ItemTextPenS(RStrokeSVal->getValue());
		if (RFont->isChecked())
			emit NewFont(RFontVal->currentText());
		if (RSize->isChecked())
			Doc->chFSize(qRound(RSizeVal->value() * 10.0));
		if (REffect->isChecked())
		{
#ifndef NLS_PROTO
			int s = REffVal->getStyle();
			Doc->currentStyle.charStyle().setEffects(static_cast<StyleFlag>(s)); // ???
			for (int a = 0; a < Item->itemText.length(); ++a)
			{
				if (Item->itemText.selected(a))
				{
					StyleFlag fl = Item->itemText.at(a)->effects();
					fl &= static_cast<StyleFlag>(~1919);
					fl |= static_cast<StyleFlag>(s);
					Item->itemText.at(a)->setEffects(fl);
				}
			}
#endif
		}
		Item->itemText.deselectAll();
	}
	else
	{
		if (ScMW->CurrStED != NULL)
		{
			if (RStyle->isChecked())
				ScMW->CurrStED->newAlign(RStyleVal->currentItem());
			if (RFill->isChecked())
				ScMW->CurrStED->newTxFill(RFillVal->currentItem(), -1);
			if (RFillS->isChecked())
				ScMW->CurrStED->newTxFill(-1, RFillSVal->getValue());
			if (RStroke->isChecked())
				ScMW->CurrStED->newTxStroke(RStrokeVal->currentItem(), -1);
			if (RStrokeS->isChecked())
				ScMW->CurrStED->newTxStroke(-1, RStrokeSVal->getValue());
			if (RFont->isChecked())
				ScMW->CurrStED->newTxFont(RFontVal->currentText());
			if (RSize->isChecked())
				ScMW->CurrStED->newTxSize(RSizeVal->value());
			if (REffect->isChecked())
				ScMW->CurrStED->newTxStyle(REffVal->getStyle());
			if (RText->isChecked())
			{
				disconnect(ScMW->CurrStED->Editor, SIGNAL(cursorPositionChanged(int, int)), ScMW->CurrStED, SLOT(updateProps(int, int)));
				int PStart, PEnd, SelStart, SelEnd;
				ScMW->CurrStED->Editor->getSelection(&PStart, &SelStart, &PEnd, &SelEnd);
				ScMW->CurrStED->Editor->insChars(RTextVal->text());
				ScMW->CurrStED->Editor->setSelection(PStart, SelStart, PEnd, SelEnd);
				ScMW->CurrStED->Editor->removeSelectedText();
				ScMW->CurrStED->Editor->setStyle(ScMW->CurrStED->Editor->CurrentStyle);
				ScMW->CurrStED->Editor->insert(RTextVal->text());
				connect(ScMW->CurrStED->Editor, SIGNAL(cursorPositionChanged(int, int)), ScMW->CurrStED, SLOT(updateProps(int, int)));
				ScMW->CurrStED->newAlign(ScMW->CurrStED->Editor->currentParaStyle);
			}
		}
	}
	DoReplace->setEnabled(false);
	AllReplace->setEnabled(false);
		slotDoSearch();
}

void SearchReplace::slotReplaceAll()
{
	if (SMode)
	{
		ScMW->view->slotDoCurs(false);
		Doc->DoDrawing = false;
	}
	do
	{
		slotDoReplace();
//		slotDoSearch();
	}
	while (NotFound);
	if (SMode)
	{
		Doc->DoDrawing = true;
		ScMW->view->slotDoCurs(true);
		ScMW->view->RefreshItem(Item);
	}
}

void SearchReplace::enableTxSearch()
{
	bool setter = SText->isChecked();
	STextVal->setEnabled(setter);
	Word->setEnabled(setter);
	CaseIgnore->setEnabled(setter);
	if (setter)
		STextVal->setFocus();
}

void SearchReplace::enableStyleSearch()
{
	SStyleVal->setEnabled(SStyle->isChecked());
}

void SearchReplace::enableFontSearch()
{
	SFontVal->setEnabled(SFont->isChecked());
}

void SearchReplace::enableSizeSearch()
{
	SSizeVal->setEnabled(SSize->isChecked());
}

void SearchReplace::enableEffSearch()
{
	SEffVal->setEnabled(SEffect->isChecked());
}

void SearchReplace::enableFillSearch()
{
	SFillVal->setEnabled(SFill->isChecked());
}

void SearchReplace::enableFillSSearch()
{
	SFillSVal->setEnabled(SFillS->isChecked());
}

void SearchReplace::enableStrokeSearch()
{
	SStrokeVal->setEnabled(SStroke->isChecked());
}

void SearchReplace::enableStrokeSSearch()
{
	SStrokeSVal->setEnabled(SStrokeS->isChecked());
}

void SearchReplace::enableTxReplace()
{
	RTextVal->setEnabled(RText->isChecked());
	if (RText->isChecked())
		RTextVal->setFocus();
}

void SearchReplace::enableStyleReplace()
{
	RStyleVal->setEnabled(RStyle->isChecked());
}

void SearchReplace::enableFontReplace()
{
	RFontVal->setEnabled(RFont->isChecked());
}

void SearchReplace::enableSizeReplace()
{
	RSizeVal->setEnabled(RSize->isChecked());
}

void SearchReplace::enableEffReplace()
{
	REffVal->setEnabled(REffect->isChecked());
}

void SearchReplace::enableFillReplace()
{
	RFillVal->setEnabled(RFill->isChecked());
}

void SearchReplace::enableFillSReplace()
{
	RFillSVal->setEnabled(RFillS->isChecked());
}

void SearchReplace::enableStrokeReplace()
{
	RStrokeVal->setEnabled(RStroke->isChecked());
}

void SearchReplace::enableStrokeSReplace()
{
	RStrokeSVal->setEnabled(RStrokeS->isChecked());
}

void SearchReplace::clear()
{

	SStroke->setChecked(false);
	SFill->setChecked(false);
	SStrokeS->setChecked(false);
	SFillS->setChecked(false);
	SSize->setChecked(false);
	SFont->setChecked(false);
	SStyle->setChecked(false);
	SText->setChecked(false);
	SEffect->setChecked(false);
	REffect->setChecked(false);
	STextVal->setText("");
	int currentParaStyle = findParagraphStyle(Doc, Doc->currentStyle);
	SStyleVal->setCurrentItem(currentParaStyle);
	SFontVal->setCurrentText(Doc->currentStyle.charStyle().font()->scName());
	SSizeVal->setValue(Doc->currentStyle.charStyle().fontSize() / 10.0);
	SFillVal->setCurrentText(Doc->currentStyle.charStyle().fillColor());
	SStrokeVal->setCurrentText(Doc->currentStyle.charStyle().strokeColor());
	RStroke->setChecked(false);
	RStrokeS->setChecked(false);
	RFill->setChecked(false);
	RFillS->setChecked(false);
	RSize->setChecked(false);
	RFont->setChecked(false);
	RStyle->setChecked(false);
	RText->setChecked(false);
	RTextVal->setText("");
	RStyleVal->setCurrentItem(currentParaStyle);
	RFontVal->setCurrentText(Doc->currentStyle.charStyle().font()->scName());
	RSizeVal->setValue(Doc->currentStyle.charStyle().fontSize() / 10.0);
	RFillVal->setCurrentText(Doc->currentStyle.charStyle().fillColor());
	RStrokeVal->setCurrentText(Doc->currentStyle.charStyle().strokeColor());
	Word->setChecked(false);
	CaseIgnore->setChecked(false);
	enableTxSearch();
	enableStyleSearch();
	enableFontSearch();
	enableSizeSearch();
	enableEffSearch();
	enableFillSearch();
	enableFillSSearch();
	enableStrokeSearch();
	enableStrokeSSearch();
	enableTxReplace();
	enableStyleReplace();
	enableFontReplace();
	enableSizeReplace();
	enableEffReplace();
	enableFillReplace();
	enableFillSReplace();
	enableStrokeReplace();
	enableStrokeSReplace();
}

void SearchReplace::readPrefs()
{
	SStroke->setChecked(prefs->getBool("SStroke", false));
	SFill->setChecked(prefs->getBool("SFill", false));
	SStrokeS->setChecked(prefs->getBool("SStrokeS", false));
	SFillS->setChecked(prefs->getBool("SFillS", false));
	SSize->setChecked(prefs->getBool("SSize", false));
	SFont->setChecked(prefs->getBool("SFont", false));
	SStyle->setChecked(prefs->getBool("SStyle", false));
	SText->setChecked(prefs->getBool("SText", false));
	SEffect->setChecked(prefs->getBool("SEffect", false));
	REffect->setChecked(prefs->getBool("REffect", false));
	STextVal->setText(prefs->get("STextVal", ""));
	int tmp = prefs->getInt("SStyleVal", findParagraphStyle(Doc, Doc->currentStyle));
	if (tmp < 0 || tmp >= SStyleVal->count())
		SStyleVal->setCurrentItem(0);
	else
		SStyleVal->setCurrentItem(tmp);

	SFontVal->setCurrentText(prefs->get("SFontVal", Doc->currentStyle.charStyle().font()->scName()));
	SSizeVal->setValue(prefs->getDouble("SSizeVal", Doc->currentStyle.charStyle().fontSize() / 10.0));
	SFillVal->setCurrentText(prefs->get("SFillVal", Doc->currentStyle.charStyle().fillColor()));
	SStrokeVal->setCurrentText(prefs->get("SStrokeVal", Doc->currentStyle.charStyle().strokeColor()));
	RStroke->setChecked(prefs->getBool("RStroke", false));
	RStrokeS->setChecked(prefs->getBool("RStrokeS", false));
	RFill->setChecked(prefs->getBool("RFill", false));
	RFillS->setChecked(prefs->getBool("RFillS", false));
	RSize->setChecked(prefs->getBool("RSize", false));
	RFont->setChecked(prefs->getBool("RFont", false));
	RStyle->setChecked(prefs->getBool("RStyle", false));
	RText->setChecked(prefs->getBool("RText", false));
	RTextVal->setText(prefs->get("RTextVal", ""));
	tmp = prefs->getInt("RStyleVal", findParagraphStyle(Doc, Doc->currentStyle));
	if (tmp < 0 || tmp >= RStyleVal->count())
		RStyleVal->setCurrentItem(0);
	else
		RStyleVal->setCurrentItem(tmp);
	RFontVal->setCurrentText(prefs->get("RFontVal", Doc->currentStyle.charStyle().font()->scName()));
	RSizeVal->setValue(prefs->getDouble("RSizeVal", Doc->currentStyle.charStyle().fontSize() / 10.0));
	RFillVal->setCurrentText(prefs->get("RFillVal", Doc->currentStyle.charStyle().fillColor()));
	RStrokeVal->setCurrentText(prefs->get("RStrokeVal", Doc->currentStyle.charStyle().strokeColor()));
	Word->setChecked(prefs->getBool("Word", false));
	CaseIgnore->setChecked(prefs->getBool("CaseIgnore", false));
	enableTxSearch();
	enableStyleSearch();
	enableFontSearch();
	enableSizeSearch();
	enableEffSearch();
	enableFillSearch();
	enableFillSSearch();
	enableStrokeSearch();
	enableStrokeSSearch();
	enableTxReplace();
	enableStyleReplace();
	enableFontReplace();
	enableSizeReplace();
	enableEffReplace();
	enableFillReplace();
	enableFillSReplace();
	enableStrokeReplace();
	enableStrokeSReplace();
}

void SearchReplace::writePrefs()
{
	prefs->set("SStroke", SStroke->isChecked());
	prefs->set("SFill", SFill->isChecked());
	prefs->set("SStrokeS", SStrokeS->isChecked());
	prefs->set("SFillS", SFillS->isChecked());
	prefs->set("SSize", SSize->isChecked());
	prefs->set("SFont", SFont->isChecked());
	prefs->set("SStyle", SStyle->isChecked());
	prefs->set("SText", SText->isChecked());
	prefs->set("SEffect", SEffect->isChecked());
	prefs->set("REffect", REffect->isChecked());
	prefs->set("STextVal", STextVal->text());
	prefs->set("SStyleVal", SStyleVal->currentItem());
	prefs->set("SFontVal", SFontVal->currentText());
	prefs->set("SSizeVal", SSizeVal->value());
	prefs->set("SFillVal", SFillVal->currentText());
	prefs->set("SStrokeVal", SStrokeVal->currentText());
	prefs->set("RStroke", RStroke->isChecked());
	prefs->set("RStrokeS", RStrokeS->isChecked());
	prefs->set("RFill", RFill->isChecked());
	prefs->set("RFillS", RFillS->isChecked());
	prefs->set("RSize", RSize->isChecked());
	prefs->set("RFont", RFont->isChecked());
	prefs->set("RStyle", RStyle->isChecked());
	prefs->set("RText", RText->isChecked());
	prefs->set("RTextVal", RTextVal->text());
	prefs->set("RStyleVal", RStyleVal->currentText());
	prefs->set("RFontVal", RFontVal->currentText());
	prefs->set("RSizeVal", RSizeVal->value());
	prefs->set("RFillVal", RFillVal->currentText());
	prefs->set("RStrokeVal", RStrokeVal->currentText());
	prefs->set("Word", Word->isChecked());
	prefs->set("CaseIgnore", CaseIgnore->isChecked());
	accept();
}
