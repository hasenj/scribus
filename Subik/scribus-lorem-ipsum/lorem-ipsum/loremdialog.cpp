/****************************************************************************
** Form implementation generated from reading ui file 'loremdialog.ui'
**
** Created: So lis 20 19:34:41 2004
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "loremdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qheader.h>
#include <qlistview.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "loremdialog.ui.h"

/*
 *  Constructs a LoremDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
LoremDialog::LoremDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "LoremDialog" );
    LoremDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "LoremDialogLayout"); 

    layout14 = new QVBoxLayout( 0, 0, 6, "layout14"); 

    tabWidget = new QTabWidget( this, "tabWidget" );

    turkeyTab = new QWidget( tabWidget, "turkeyTab" );
    turkeyTabLayout = new QGridLayout( turkeyTab, 1, 1, 11, 6, "turkeyTabLayout"); 

    layout22 = new QVBoxLayout( 0, 0, 6, "layout22"); 

    textLabel8 = new QLabel( turkeyTab, "textLabel8" );
    layout22->addWidget( textLabel8 );

    layout21 = new QHBoxLayout( 0, 0, 6, "layout21"); 

    layout20 = new QVBoxLayout( 0, 0, 6, "layout20"); 

    textLabel4 = new QLabel( turkeyTab, "textLabel4" );
    layout20->addWidget( textLabel4 );
    spacer2 = new QSpacerItem( 20, 180, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout20->addItem( spacer2 );
    layout21->addLayout( layout20 );

    dictionaryView = new QListView( turkeyTab, "dictionaryView" );
    dictionaryView->addColumn( tr( "Name" ) );
    dictionaryView->addColumn( tr( "Description" ) );
    dictionaryView->addColumn( tr( "Url" ) );
    layout21->addWidget( dictionaryView );
    layout22->addLayout( layout21 );

    layout7 = new QHBoxLayout( 0, 0, 6, "layout7"); 

    textLabel5 = new QLabel( turkeyTab, "textLabel5" );
    layout7->addWidget( textLabel5 );

    turkeyParagraphs = new QSpinBox( turkeyTab, "turkeyParagraphs" );
    turkeyParagraphs->setMinValue( 1 );
    turkeyParagraphs->setValue( 4 );
    layout7->addWidget( turkeyParagraphs );
    layout22->addLayout( layout7 );

    layout8 = new QHBoxLayout( 0, 0, 6, "layout8"); 

    textLabel6 = new QLabel( turkeyTab, "textLabel6" );
    layout8->addWidget( textLabel6 );

    avgSentences = new QSpinBox( turkeyTab, "avgSentences" );
    avgSentences->setMinValue( 1 );
    avgSentences->setValue( 5 );
    layout8->addWidget( avgSentences );
    layout22->addLayout( layout8 );

    turkeyStartLorem = new QCheckBox( turkeyTab, "turkeyStartLorem" );
    turkeyStartLorem->setChecked( TRUE );
    layout22->addWidget( turkeyStartLorem );

    turkeyTabLayout->addLayout( layout22, 0, 0 );
    tabWidget->insertTab( turkeyTab, QString("") );

    networkTab = new QWidget( tabWidget, "networkTab" );
    networkTabLayout = new QGridLayout( networkTab, 1, 1, 11, 6, "networkTabLayout"); 

    layout19 = new QVBoxLayout( 0, 0, 6, "layout19"); 

    textLabel7 = new QLabel( networkTab, "textLabel7" );
    layout19->addWidget( textLabel7 );

    layout18 = new QHBoxLayout( 0, 0, 6, "layout18"); 

    layout16 = new QVBoxLayout( 0, 0, 6, "layout16"); 

    textLabel4_2 = new QLabel( networkTab, "textLabel4_2" );
    layout16->addWidget( textLabel4_2 );
    spacer3 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout16->addItem( spacer3 );
    layout18->addLayout( layout16 );

    networkView = new QListView( networkTab, "networkView" );
    networkView->addColumn( tr( "Name" ) );
    networkView->addColumn( tr( "Description" ) );
    networkView->addColumn( tr( "Url" ) );
    layout18->addWidget( networkView );
    layout19->addLayout( layout18 );

    networkTabLayout->addLayout( layout19, 0, 0 );
    tabWidget->insertTab( networkTab, QString("") );

    standardTab = new QWidget( tabWidget, "standardTab" );

    QWidget* privateLayoutWidget = new QWidget( standardTab, "layout5" );
    privateLayoutWidget->setGeometry( QRect( 10, 10, 250, 114 ) );
    layout5 = new QVBoxLayout( privateLayoutWidget, 11, 6, "layout5"); 

    textLabel3 = new QLabel( privateLayoutWidget, "textLabel3" );
    layout5->addWidget( textLabel3 );

    layout1 = new QHBoxLayout( 0, 0, 6, "layout1"); 

    textLabel1 = new QLabel( privateLayoutWidget, "textLabel1" );
    layout1->addWidget( textLabel1 );

    standardParaBox = new QSpinBox( privateLayoutWidget, "standardParaBox" );
    standardParaBox->setMinValue( 1 );
    standardParaBox->setValue( 4 );
    layout1->addWidget( standardParaBox );
    layout5->addLayout( layout1 );
    tabWidget->insertTab( standardTab, QString("") );
    layout14->addWidget( tabWidget );

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout3->addItem( spacer1 );

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 

    okButton = new QPushButton( this, "okButton" );
    layout2->addWidget( okButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    layout2->addWidget( cancelButton );
    layout3->addLayout( layout2 );
    layout14->addLayout( layout3 );

    LoremDialogLayout->addLayout( layout14, 0, 0 );
    languageChange();
    resize( QSize(689, 557).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( okButton, SIGNAL( pressed() ), this, SLOT( okButton_pressed() ) );
    connect( cancelButton, SIGNAL( pressed() ), this, SLOT( cancelButton_pressed() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
LoremDialog::~LoremDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void LoremDialog::languageChange()
{
    setCaption( tr( "Lorem Ipsum" ) );
    textLabel8->setText( tr( "<p>This is based on the Turkey (turkey.sf.net) dummy text generator, which means it generates dummy texts.</p>" ) );
    textLabel4->setText( tr( "Dictionary:" ) );
    dictionaryView->header()->setLabel( 0, tr( "Name" ) );
    dictionaryView->header()->setLabel( 1, tr( "Description" ) );
    dictionaryView->header()->setLabel( 2, tr( "Url" ) );
    textLabel5->setText( tr( "Paragraphs:" ) );
    textLabel6->setText( tr( "AVG. Sentences:" ) );
    turkeyStartLorem->setText( tr( "Should Start with Lorem Ipsum" ) );
    tabWidget->changeTab( turkeyTab, tr( "Turkey" ) );
    textLabel7->setText( tr( "<p><b>This feature requires network connection!</b> Here you can access large Lorem Ipsum library at lorem-ipsum.info</p>" ) );
    textLabel4_2->setText( tr( "Dictionary:" ) );
    networkView->header()->setLabel( 0, tr( "Name" ) );
    networkView->header()->setLabel( 1, tr( "Description" ) );
    networkView->header()->setLabel( 2, tr( "Url" ) );
    tabWidget->changeTab( networkTab, tr( "lorem-ipsum.info" ) );
    textLabel3->setText( tr( "<p>This is wrapper around classical piece of the Lorem Ipsum distributed with Scribus</p>" ) );
    textLabel1->setText( tr( "Paragraphs:" ) );
    tabWidget->changeTab( standardTab, tr( "Standard" ) );
    okButton->setText( tr( "&OK" ) );
    okButton->setAccel( QKeySequence( tr( "Alt+O" ) ) );
    cancelButton->setText( tr( "&Cancel" ) );
    cancelButton->setAccel( QKeySequence( tr( "Alt+C" ) ) );
}

