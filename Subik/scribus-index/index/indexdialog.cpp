/****************************************************************************
** Form implementation generated from reading ui file 'indexdialog.ui'
**
** Created: Po pro 6 20:41:15 2004
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "indexdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "indexdialog.ui.h"

/*
 *  Constructs a IndexDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
IndexDialog::IndexDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "IndexDialog" );
    IndexDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "IndexDialogLayout"); 

    layout10 = new QVBoxLayout( 0, 0, 6, "layout10"); 

    layout9 = new QVBoxLayout( 0, 0, 6, "layout9"); 

    layout1 = new QHBoxLayout( 0, 0, 6, "layout1"); 

    textLabel1 = new QLabel( this, "textLabel1" );
    layout1->addWidget( textLabel1 );

    heading1 = new QComboBox( FALSE, this, "heading1" );
    layout1->addWidget( heading1 );
    layout9->addLayout( layout1 );

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 

    textLabel2 = new QLabel( this, "textLabel2" );
    layout2->addWidget( textLabel2 );

    heading2 = new QComboBox( FALSE, this, "heading2" );
    heading2->setEnabled( FALSE );
    layout2->addWidget( heading2 );
    layout9->addLayout( layout2 );

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 

    textLabel3 = new QLabel( this, "textLabel3" );
    layout3->addWidget( textLabel3 );

    heading3 = new QComboBox( FALSE, this, "heading3" );
    heading3->setEnabled( FALSE );
    layout3->addWidget( heading3 );
    layout9->addLayout( layout3 );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    textLabel4 = new QLabel( this, "textLabel4" );
    layout4->addWidget( textLabel4 );

    heading4 = new QComboBox( FALSE, this, "heading4" );
    heading4->setEnabled( FALSE );
    layout4->addWidget( heading4 );
    layout9->addLayout( layout4 );

    layout5 = new QHBoxLayout( 0, 0, 6, "layout5"); 

    textLabel5 = new QLabel( this, "textLabel5" );
    layout5->addWidget( textLabel5 );

    heading5 = new QComboBox( FALSE, this, "heading5" );
    heading5->setEnabled( FALSE );
    layout5->addWidget( heading5 );
    layout9->addLayout( layout5 );

    layout6 = new QHBoxLayout( 0, 0, 6, "layout6"); 

    textLabel6 = new QLabel( this, "textLabel6" );
    layout6->addWidget( textLabel6 );

    heading6 = new QComboBox( FALSE, this, "heading6" );
    heading6->setEnabled( FALSE );
    layout6->addWidget( heading6 );
    layout9->addLayout( layout6 );

    layout7 = new QHBoxLayout( 0, 0, 6, "layout7"); 

    textLabel7 = new QLabel( this, "textLabel7" );
    layout7->addWidget( textLabel7 );

    heading7 = new QComboBox( FALSE, this, "heading7" );
    heading7->setEnabled( FALSE );
    layout7->addWidget( heading7 );
    layout9->addLayout( layout7 );
    layout10->addLayout( layout9 );

    layout8 = new QHBoxLayout( 0, 0, 6, "layout8"); 
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout8->addItem( spacer1 );

    okButton = new QPushButton( this, "okButton" );
    layout8->addWidget( okButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    layout8->addWidget( cancelButton );
    layout10->addLayout( layout8 );

    IndexDialogLayout->addLayout( layout10, 0, 0 );
    languageChange();
    resize( QSize(321, 286).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( cancelButton, SIGNAL( pressed() ), this, SLOT( cancelButton_pressed() ) );
    connect( okButton, SIGNAL( pressed() ), this, SLOT( okButton_pressed() ) );
    connect( heading1, SIGNAL( textChanged(const QString&) ), this, SLOT( heading1_textChanged(const QString&) ) );
    connect( heading2, SIGNAL( textChanged(const QString&) ), this, SLOT( heading2_textChanged(const QString&) ) );
    connect( heading3, SIGNAL( textChanged(const QString&) ), this, SLOT( heading3_textChanged(const QString&) ) );
    connect( heading4, SIGNAL( textChanged(const QString&) ), this, SLOT( heading4_textChanged(const QString&) ) );
    connect( heading5, SIGNAL( textChanged(const QString&) ), this, SLOT( heading5_textChanged(const QString&) ) );
    connect( heading6, SIGNAL( textChanged(const QString&) ), this, SLOT( heading6_textChanged(const QString&) ) );
    connect( heading7, SIGNAL( textChanged(const QString&) ), this, SLOT( heading7_textChanged(const QString&) ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
IndexDialog::~IndexDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void IndexDialog::languageChange()
{
    setCaption( tr( "Index" ) );
    textLabel1->setText( tr( "Heading 1:" ) );
    textLabel2->setText( tr( "Heading 2:" ) );
    textLabel3->setText( tr( "Heading 3:" ) );
    textLabel4->setText( tr( "Heading 4:" ) );
    textLabel5->setText( tr( "Heading 5:" ) );
    textLabel6->setText( tr( "Heading 6:" ) );
    textLabel7->setText( tr( "Heading 7:" ) );
    okButton->setText( tr( "&OK" ) );
    okButton->setAccel( QKeySequence( tr( "Alt+O" ) ) );
    cancelButton->setText( tr( "&Cancel" ) );
    cancelButton->setAccel( QKeySequence( tr( "Alt+C" ) ) );
}

