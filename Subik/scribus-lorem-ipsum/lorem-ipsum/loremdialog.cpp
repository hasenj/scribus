/****************************************************************************
** Form implementation generated from reading ui file 'loremdialog.ui'
**
** Created: Út lis 23 19:05:01 2004
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "loremdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
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

    layout24 = new QVBoxLayout( 0, 0, 6, "layout24"); 

    textLabel8 = new QLabel( this, "textLabel8" );
    layout24->addWidget( textLabel8 );

    dictionaryView = new QListView( this, "dictionaryView" );
    dictionaryView->addColumn( tr( "Name" ) );
    dictionaryView->addColumn( tr( "Type" ) );
    dictionaryView->addColumn( tr( "Description" ) );
    dictionaryView->addColumn( tr( "Url" ) );
    layout24->addWidget( dictionaryView );

    layout7 = new QHBoxLayout( 0, 0, 6, "layout7"); 

    textLabel5 = new QLabel( this, "textLabel5" );
    layout7->addWidget( textLabel5 );

    turkeyParagraphs = new QSpinBox( this, "turkeyParagraphs" );
    turkeyParagraphs->setMinValue( 1 );
    turkeyParagraphs->setValue( 4 );
    layout7->addWidget( turkeyParagraphs );
    layout24->addLayout( layout7 );

    layout8 = new QHBoxLayout( 0, 0, 6, "layout8"); 

    textLabel6 = new QLabel( this, "textLabel6" );
    layout8->addWidget( textLabel6 );

    avgSentences = new QSpinBox( this, "avgSentences" );
    avgSentences->setMinValue( 1 );
    avgSentences->setValue( 5 );
    layout8->addWidget( avgSentences );
    layout24->addLayout( layout8 );

    shouldStartLorem = new QCheckBox( this, "shouldStartLorem" );
    shouldStartLorem->setChecked( TRUE );
    layout24->addWidget( shouldStartLorem );

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout3->addItem( spacer1 );

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 

    okButton = new QPushButton( this, "okButton" );
    layout2->addWidget( okButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    layout2->addWidget( cancelButton );
    layout3->addLayout( layout2 );
    layout24->addLayout( layout3 );

    LoremDialogLayout->addLayout( layout24, 0, 0 );
    languageChange();
    resize( QSize(647, 527).expandedTo(minimumSizeHint()) );
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
    textLabel8->setText( tr( "<p>Select dictionary:</p>" ) );
    dictionaryView->header()->setLabel( 0, tr( "Name" ) );
    dictionaryView->header()->setLabel( 1, tr( "Type" ) );
    dictionaryView->header()->setLabel( 2, tr( "Description" ) );
    dictionaryView->header()->setLabel( 3, tr( "Url" ) );
    textLabel5->setText( tr( "Paragraphs:" ) );
    textLabel6->setText( tr( "AVG. Sentences:" ) );
    shouldStartLorem->setText( tr( "Should Start with Lorem Ipsum" ) );
    okButton->setText( tr( "&OK" ) );
    okButton->setAccel( QKeySequence( tr( "Alt+O" ) ) );
    cancelButton->setText( tr( "&Cancel" ) );
    cancelButton->setAccel( QKeySequence( tr( "Alt+C" ) ) );
}

