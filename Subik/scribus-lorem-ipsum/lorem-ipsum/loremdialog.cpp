/****************************************************************************
** Form implementation generated from reading ui file 'loremdialog.ui'
**
** Created: Po lis 15 19:30:50 2004
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "loremdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
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

    layout9 = new QVBoxLayout( 0, 0, 6, "layout9");

    layout7 = new QVBoxLayout( 0, 0, 6, "layout7");

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2");

    textLabel2 = new QLabel( this, "textLabel2" );
    layout2->addWidget( textLabel2 );

    typeBox = new QComboBox( FALSE, this, "typeBox" );
    layout2->addWidget( typeBox );
    layout7->addLayout( layout2 );

    layout1 = new QHBoxLayout( 0, 0, 6, "layout1");

    textLabel1 = new QLabel( this, "textLabel1" );
    layout1->addWidget( textLabel1 );

    paragraphSpinBox = new QSpinBox( this, "paragraphSpinBox" );
    paragraphSpinBox->setMinValue( 1 );
    paragraphSpinBox->setValue( 5 );
    layout1->addWidget( paragraphSpinBox );
    layout7->addLayout( layout1 );

    startWithCheckBox = new QCheckBox( this, "startWithCheckBox" );
    startWithCheckBox->setChecked( TRUE );
    layout7->addWidget( startWithCheckBox );

    descriptionLabel = new QLabel( this, "descriptionLabel" );
    descriptionLabel->setTextFormat( QLabel::RichText );
    layout7->addWidget( descriptionLabel );
    layout9->addLayout( layout7 );

    layout8 = new QHBoxLayout( 0, 0, 6, "layout8");
    spacer2 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout8->addItem( spacer2 );

    okButton = new QPushButton( this, "okButton" );
    layout8->addWidget( okButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    layout8->addWidget( cancelButton );
    layout9->addLayout( layout8 );

    LoremDialogLayout->addLayout( layout9, 0, 0 );
    languageChange();
    resize( QSize(346, 224).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( okButton, SIGNAL( clicked() ), this, SLOT( okButton_clicked() ) );
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( cancelButton_clicked() ) );
    connect( startWithCheckBox, SIGNAL( clicked() ), this, SLOT( startWithCheckBox_clicked() ) );
    connect( typeBox, SIGNAL( textChanged(const QString&) ), this, SLOT( typeBox_textChanged(const QString&) ) );
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
    textLabel2->setText( tr( "Type of the Lorem:" ) );
    textLabel1->setText( tr( "Paragraphs:" ) );
    startWithCheckBox->setText( tr( "&Start with \"Lorem Ipsum\"" ) );
    startWithCheckBox->setAccel( QKeySequence( tr( "Alt+S" ) ) );
    descriptionLabel->setText( tr( "Description" ) );
    okButton->setText( tr( "&OK" ) );
    okButton->setAccel( QKeySequence( tr( "Alt+O" ) ) );
    cancelButton->setText( tr( "&Cancel" ) );
    cancelButton->setAccel( QKeySequence( tr( "Alt+C" ) ) );
}

