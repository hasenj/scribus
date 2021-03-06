/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#include "pageselector.h"

#include <QEvent>
#include <QLineEdit>
#if OPTION_USE_QTOOLBUTTON
    #include <QToolButton>
#else
    #include <QPushButton>
#endif
#include <QLabel>
#include <QToolTip>
#include <QRegExp>
#include <QPixmap>
#include <QHBoxLayout>
#include <QValidator>
#include "sccombobox.h"
#include "util_icon.h"
#include "util.h"

// QIntValidator does it better for us... PV
// class PageValidator : public QValidator
// {
// public:
// 	PageValidator(int min, int max, QObject * parent);
// 	void fixup(QString & input) const;
// 	State validate(QString & input, int & pos) const;
// private:
// 	QRegExp rx;
// 	QRegExp rx2;
// 	PageSelector * pageSelector;
// };
// 
// PageValidator::PageValidator(int /* min */, int /* max */, QObject * parent) : QValidator
// (parent), rx("^([0-9]+).*"), rx2("^[0-9]+$") 
// {
// 	pageSelector = static_cast<PageSelector*>(parent);
// }
// 
// QValidator::State PageValidator::validate(QString & input, int & /* pos */) const
// {
// 	if (rx2.indexIn(input) == 0 && pageSelector->PageCombo->itemText(input.toInt()-1) == input)
// 		return Acceptable;
// 	else
// 		return Intermediate;
// }
// 
// void PageValidator::fixup(QString & input) const
// {
// 	if (rx.indexIn(input) == 0)
// 		input = const_cast<QRegExp &>(rx).cap(1);
// }
// 	

PageSelector::PageSelector( QWidget* parent, int maxPg ) : QWidget( parent, 0 )
{
	PageCountString = "%1" ;
	LastPG = maxPg;
	APage = 1;
	PageSelectorLayout = new QHBoxLayout( this );
	PageSelectorLayout->setMargin(0);
	PageSelectorLayout->setSpacing(1);

#if OPTION_USE_QTOOLBUTTON
	Start = new QToolButton( this );
	Start->setAutoRaise(OPTION_FLAT_BUTTON);
	Back = new QToolButton( this );
	Back->setAutoRaise(OPTION_FLAT_BUTTON);
	Forward = new QToolButton( this );
	Forward->setAutoRaise(OPTION_FLAT_BUTTON);
	Last = new QToolButton( this );
	Last->setAutoRaise(OPTION_FLAT_BUTTON);
#else
	Start = new QPushButton( this );
	Start->setDefault( false );
	Start->setAutoDefault( false );
	Start->setFlat(OPTION_FLAT_BUTTON);
	Back = new QPushButton( this );
	Back->setDefault( false );
	Back->setAutoDefault( false );
	Back->setFlat(OPTION_FLAT_BUTTON);
	Forward = new QPushButton( this );
	Forward->setDefault( false );
	Forward->setAutoDefault( false );
	Forward->setFlat(OPTION_FLAT_BUTTON);
	Last = new QPushButton( this );
	Last->setDefault( false );
	Last->setAutoDefault( false );
	Last->setFlat(OPTION_FLAT_BUTTON);
#endif
	Start->setIcon(QIcon(loadIcon("16/go-first.png")));
	Start->setFocusPolicy(Qt::NoFocus);
	PageSelectorLayout->addWidget( Start );

	Back->setIcon(QIcon(loadIcon("16/go-previous.png")));
	Back->setFocusPolicy(Qt::NoFocus);
	Back->setAutoRepeat(true);
	PageSelectorLayout->addWidget( Back );

// 	v = new PageValidator(1, LastPG, this);
	m_validator = new QIntValidator(1, LastPG, this);
	PageCombo = new ScComboBox( this );
	PageCombo->setEditable(true);
	PageCombo->setDuplicatesEnabled( false );
	PageCombo->lineEdit()->setAlignment(Qt::AlignHCenter);
	for (int a = 0; a < LastPG; ++a)
	{
		PageCombo->addItem(QString::number(a+1));
	}
	PageCombo->setValidator(m_validator);
	PageCombo->setMinimumSize(fontMetrics().width( "999" )+20, 20);
	PageCombo->setFocusPolicy(Qt::ClickFocus);
	PageSelectorLayout->addWidget( PageCombo );
	
	PageCount = new QLabel(PageCountString.arg(LastPG), this);
	PageSelectorLayout->addWidget(PageCount);
			
	Forward->setIcon(QIcon(loadIcon("16/go-next.png")));
	Forward->setFocusPolicy(Qt::NoFocus);
	Forward->setAutoRepeat(true);
	PageSelectorLayout->addWidget( Forward );

	Last->setIcon(QIcon(loadIcon("16/go-last.png")));
	Last->setFocusPolicy(Qt::NoFocus);
	PageSelectorLayout->addWidget( Last );
	Forward->setEnabled(true);
	Last->setEnabled(true);
	Back->setEnabled(false);
	Start->setEnabled(false);
	if (APage == LastPG)
	{
		Forward->setEnabled(false);
		Last->setEnabled(false);
	}

	languageChange();
	// signals and slots connections
	connect( PageCombo, SIGNAL( activated(int) ), this, SLOT( GotoPgE(int) ) );
	connect( Back, SIGNAL( clicked() ), this, SLOT( goBk() ) );
	connect( Start, SIGNAL( clicked() ), this, SLOT( ToStart() ) );
	connect( Forward, SIGNAL( clicked() ), this, SLOT( goFw() ) );
	connect( Last, SIGNAL( clicked() ), this, SLOT( ToEnd() ) );
}

bool PageSelector::hasFocus()
{
	return PageCombo->hasFocus();
}


void PageSelector::focusPolicy(Qt::FocusPolicy policy)
{
	PageCombo->setFocusPolicy(policy);
}

void PageSelector::setFont ( const QFont &fo )
{
	PageCount->setFont(fo);
	QWidget::setFont(fo);
}

void PageSelector::GotoPgE(int a)
{
	clearFocus();
	GotoPg(a);
	emit GotoPage(a+1);
}


void PageSelector::GotoPage()
{
	static QRegExp rx("^([0-9])+.*");
	int p = rx.cap(1).toInt();
	if (p < 1)
		p=1;
	if (p > LastPG)
		p = LastPG;
	GotoPg(p-1);
	emit GotoPage(p);
}


void PageSelector::GotoPg(int a)
{
	disconnect( PageCombo, SIGNAL( activated(int) ), this, SLOT( GotoPgE(int) ) );
	PageCombo->setCurrentIndex(a);
	setCurrentComboItem(PageCombo, QString::number(a+1));
	APage = a+1;
	Back->setEnabled(true);
	Start->setEnabled(true);
	Forward->setEnabled(true);
	Last->setEnabled(true);
	if (a == 0)
	{
		Back->setEnabled(false);
		Start->setEnabled(false);
	}
	if (a == LastPG-1)
	{
		Forward->setEnabled(false);
		Last->setEnabled(false);
	}
	connect( PageCombo, SIGNAL( activated(int) ), this, SLOT( GotoPgE(int) ) );
}

void PageSelector::setMaximum(int a)
{
	disconnect( PageCombo, SIGNAL( activated(int) ), this, SLOT( GotoPgE(int) ) );
	PageCombo->clear();
	LastPG = a;
//	v->setTop(LastPG);
	m_validator->setRange(1, LastPG);
	for (int b = 0; b < LastPG; ++b)
	{
		PageCombo->addItem(QString::number(b+1));
	}
	setCurrentComboItem(PageCombo, QString::number(APage));
	PageCount->setText(PageCountString.arg(LastPG));
	connect( PageCombo, SIGNAL( activated(int) ), this, SLOT( GotoPgE(int) ) );
}

void PageSelector::ToStart()
{
	if (APage == 1)
		return;
	GotoPgE(0);
}

void PageSelector::ToEnd()
{
	if (APage == LastPG)
		return;
	GotoPgE(LastPG-1);
}

void PageSelector::goBk()
{
	APage--;
	if (APage < 1)
		APage = 1;
	GotoPgE(APage-1);
}

void PageSelector::goFw()
{
	APage++;
	if (APage > LastPG)
		APage = LastPG;
	GotoPgE(APage-1);
}

void PageSelector::changeEvent(QEvent *e)
{
	if (e->type() == QEvent::LanguageChange)
		languageChange();
	else
		QWidget::changeEvent(e);
}

void PageSelector::languageChange()
{
	Start->setToolTip( tr("Go to the first page") );
	Back->setToolTip( tr("Go to the previous page") );
	Forward->setToolTip( tr("Go to the next page") );
	Last->setToolTip( tr("Go to the last page") );
	PageCombo->setToolTip( tr("Select the current page") );
	PageCountString =  tr(" of %1", "number of pages in document");
	PageCount->setText(PageCountString.arg(LastPG));
	disconnect( PageCombo, SIGNAL( activated(int) ), this, SLOT( GotoPgE(int) ) );
	setCurrentComboItem(PageCombo, QString::number(APage));
	connect( PageCombo, SIGNAL( activated(int) ), this, SLOT( GotoPgE(int) ) );
}

void PageSelector::clearFocus()
{
	PageCombo->clearFocus();	
}
