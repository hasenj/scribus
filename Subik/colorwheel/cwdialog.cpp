#include "cwdialog.h"

#include <qvariant.h>
#include <qcombobox.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a ColorWheel as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ColorWheelDialog::ColorWheelDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
	: QDialog( parent, name, modal, fl )
{
	if ( !name )
		setName( "ColorWheelDialog" );

	typeCombo = new QComboBox( FALSE, this, "typeCombo" );
	typeCombo->setGeometry( QRect( 400, 30, 106, 25 ) );

	colorList = new QListView( this, "colorList" );
	colorList->addColumn( tr( "Color" ) );
	colorList->addColumn( tr( "Value" ) );
	colorList->setGeometry( QRect( 400, 100, 182, 229 ) );

	colorWheel = new ColorWheel( this, "colorWheel" );
	colorWheel->setGeometry( QRect( 10, 10, 300, 300 ) );
	colorWheel->setFrameShape(QFrame::Box);
	colorWheel->paintWheel(QValueVector<QPoint>());
	languageChange();
	resize( QSize(600, 480).expandedTo(minimumSizeHint()) );
	clearWState( WState_Polished );

	// setup combobox
	typeCombo->insertItem(colorWheel->getTypeDescription(colorWheel->Monochromatic), colorWheel->Monochromatic);
	typeCombo->insertItem(colorWheel->getTypeDescription(colorWheel->Analogous), colorWheel->Analogous);
	typeCombo->insertItem(colorWheel->getTypeDescription(colorWheel->Complementary), colorWheel->Complementary);
	typeCombo->insertItem(colorWheel->getTypeDescription(colorWheel->Split), colorWheel->Split);
	typeCombo->insertItem(colorWheel->getTypeDescription(colorWheel->Triadic), colorWheel->Triadic);
	typeCombo->insertItem(colorWheel->getTypeDescription(colorWheel->Tetradic), colorWheel->Tetradic);

    // signals and slots connections
	connect(typeCombo, SIGNAL(activated(int)), this, SLOT(typeCombo_activated(int)));
	connect(colorWheel, SIGNAL(clicked(int, const QPoint&)), this, SLOT(colorWheel_clicked(int, const QPoint&)));
}

/*
 *  Destroys the object and frees any allocated resources
 */
ColorWheelDialog::~ColorWheelDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ColorWheelDialog::languageChange()
{
	setCaption( tr( "Color Wheel" ) );
	colorList->header()->setLabel( 0, tr( "Color" ) );
	colorList->header()->setLabel( 1, tr( "Value" ) );
}

void ColorWheelDialog::typeCombo_activated(int index)
{
	if (index == colorWheel->Monochromatic)
		colorWheel->makeMonochromatic();
	if (index == colorWheel->Analogous)
		colorWheel->makeAnalogous();
	if (index == colorWheel->Complementary)
		colorWheel->makeComplementary();
	if (index == colorWheel->Split)
		colorWheel->makeSplit();
	if (index == colorWheel->Triadic)
		colorWheel->makeTriadic();
	if (index == colorWheel->Tetradic)
		colorWheel->makeTetradic();
}

void ColorWheelDialog::colorWheel_clicked(int, const QPoint&)
{
	colorList->clear();
	typeCombo_activated(typeCombo->currentItem());
	for (QMap<QString,QPixmap>::iterator it = colorWheel->colorList.begin(); it != colorWheel->colorList.end(); ++it )
	{
		QListViewItem *item = new QListViewItem(colorList);
		item->setText(1, it.key().latin1());
		item->setPixmap(0, it.data());
	}
}
