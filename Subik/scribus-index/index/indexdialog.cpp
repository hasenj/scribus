/****************************************************************************
** Form implementation generated from reading ui file 'indexdialog.ui'
**
** Created: Čt pro 9 18:28:41 2004
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "indexdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlistbox.h>
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

    layout13 = new QVBoxLayout( 0, 0, 6, "layout13"); 

    layout12 = new QHBoxLayout( 0, 0, 6, "layout12"); 

    stylesBox = new QListBox( this, "stylesBox" );
    layout12->addWidget( stylesBox );

    layout11 = new QVBoxLayout( 0, 0, 6, "layout11"); 
    spacer3 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout11->addItem( spacer3 );

    appendButton = new QPushButton( this, "appendButton" );
    layout11->addWidget( appendButton );

    removeButton = new QPushButton( this, "removeButton" );
    layout11->addWidget( removeButton );
    spacer2 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout11->addItem( spacer2 );
    layout12->addLayout( layout11 );

    tocStylesBox = new QListBox( this, "tocStylesBox" );
    layout12->addWidget( tocStylesBox );
    layout13->addLayout( layout12 );

    layout8 = new QHBoxLayout( 0, 0, 6, "layout8"); 
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout8->addItem( spacer1 );

    okButton = new QPushButton( this, "okButton" );
    layout8->addWidget( okButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    layout8->addWidget( cancelButton );
    layout13->addLayout( layout8 );

    IndexDialogLayout->addLayout( layout13, 0, 0 );
    languageChange();
    resize( QSize(321, 286).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( cancelButton, SIGNAL( pressed() ), this, SLOT( cancelButton_pressed() ) );
    connect( okButton, SIGNAL( pressed() ), this, SLOT( okButton_pressed() ) );
    connect( appendButton, SIGNAL( pressed() ), this, SLOT( appendButton_pressed() ) );
    connect( removeButton, SIGNAL( pressed() ), this, SLOT( removeButton_pressed() ) );
    connect( stylesBox, SIGNAL( selected(const QString&) ), this, SLOT( stylesBox_selected(const QString&) ) );
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
    appendButton->setText( tr( ">" ) );
    removeButton->setText( tr( "<" ) );
    okButton->setText( tr( "&OK" ) );
    okButton->setAccel( QKeySequence( tr( "Alt+O" ) ) );
    cancelButton->setText( tr( "&Cancel" ) );
    cancelButton->setAccel( QKeySequence( tr( "Alt+C" ) ) );
}

