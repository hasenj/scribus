/****************************************************************************
** Form implementation generated from reading ui file 'vlnadialog.ui'
**
** Created: Út pro 2 21:08:58 2003
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "vlnadialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "vlnadialog.ui.h"

/* 
 *  Constructs a VlnaDialog as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
VlnaDialog::VlnaDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "VlnaDialog" );
    VlnaDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "VlnaDialogLayout"); 

    layout4 = new QVBoxLayout( 0, 0, 6, "layout4"); 

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 

    buttonGroup = new QButtonGroup( this, "buttonGroup" );
    buttonGroup->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)3, 0, 0, buttonGroup->sizePolicy().hasHeightForWidth() ) );

    frameRadio = new QRadioButton( buttonGroup, "frameRadio" );
    frameRadio->setGeometry( QRect( 20, 30, 160, 22 ) );

    pageRadio = new QRadioButton( buttonGroup, "pageRadio" );
    pageRadio->setGeometry( QRect( 20, 60, 110, 22 ) );

    allRadio = new QRadioButton( buttonGroup, "allRadio" );
    allRadio->setGeometry( QRect( 20, 90, 110, 22 ) );
    layout3->addWidget( buttonGroup );

    layout2 = new QVBoxLayout( 0, 0, 6, "layout2"); 
    QSpacerItem* spacer = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout2->addItem( spacer );

    layout1 = new QVBoxLayout( 0, 0, 6, "layout1"); 

    okButton = new QPushButton( this, "okButton" );
    okButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, okButton->sizePolicy().hasHeightForWidth() ) );
    layout1->addWidget( okButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    cancelButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, cancelButton->sizePolicy().hasHeightForWidth() ) );
    layout1->addWidget( cancelButton );
    layout2->addLayout( layout1 );
    layout3->addLayout( layout2 );
    layout4->addLayout( layout3 );

    statusLabel = new QLabel( this, "statusLabel" );
    layout4->addWidget( statusLabel );

    VlnaDialogLayout->addLayout( layout4, 0, 0 );
    languageChange();
    resize( QSize(306, 193).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( okButton, SIGNAL( pressed() ), this, SLOT( okButton_pressed() ) );
    connect( frameRadio, SIGNAL( pressed() ), this, SLOT( frameRadio_pressed() ) );
    connect( pageRadio, SIGNAL( pressed() ), this, SLOT( pageRadio_pressed() ) );
    connect( allRadio, SIGNAL( pressed() ), this, SLOT( allRadio_pressed() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
VlnaDialog::~VlnaDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void VlnaDialog::languageChange()
{
    setCaption( tr( "Vlna" ) );
    buttonGroup->setTitle( tr( "Select action" ) );
    frameRadio->setText( tr( "&Seleceted frames" ) );
    pageRadio->setText( tr( "Active &page" ) );
    pageRadio->setAccel( QKeySequence( tr( "Alt+P" ) ) );
    allRadio->setText( tr( "&All items" ) );
    okButton->setText( tr( "&OK" ) );
    cancelButton->setText( tr( "&Cancel" ) );
    statusLabel->setText( tr( "Select action..." ) );
}

