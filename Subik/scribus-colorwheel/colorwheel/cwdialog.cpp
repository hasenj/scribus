#include "cwdialog.h"

#include <qvariant.h>
#include <qcombobox.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qpushbutton.h>
#include <qspinbox.h>

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

	formLayout = new QGridLayout( this, 1, 1, 11, 6, "formLayout");
	mainLayout = new QHBoxLayout( 0, 0, 6, "mainLayout");
	wheelLayout = new QVBoxLayout( 0, 0, 6, "wheelLayout");

	colorWheel = new ColorWheel( this, "colorWheel" );
	colorWheel->setFrameShape(QFrame::Box);
	colorWheel->setMinimumSize(QSize(300, 300));
	colorWheel->setMaximumSize(QSize(300, 300));
	wheelLayout->addWidget(colorWheel);
	colorWheel->paintWheel(QValueVector<QPoint>());

	angleLabel = new QLabel(this, "angleLabel");

	angleLayout = new QHBoxLayout( 0, 0, 6, "angleLayout");
	angleLayout->addWidget(angleLabel);

	angleSpin = new QSpinBox(this, "angleSpin");
	angleSpin->setValue(15);
	angleSpin->setMinValue(0);
	angleSpin->setMaxValue(365);
	angleLayout->addWidget(angleSpin);
	wheelLayout->addLayout(angleLayout);

	brightnessLabel = new QLabel(this, "brightnessLabel");

	brightnessLayout = new QHBoxLayout( 0, 0, 6, "brightnessLayout");
	brightnessLayout->addWidget(brightnessLabel);

	brightnessSpin = new QSpinBox(this, "brightnessSpin");
	brightnessSpin->setMinValue(0);
	brightnessSpin->setMaxValue(255);
	brightnessSpin->setValue(255);
	brightnessLayout->addWidget(brightnessSpin);
	wheelLayout->addLayout(brightnessLayout);

	spacer1 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
	wheelLayout->addItem(spacer1);
	mainLayout->addLayout(wheelLayout);

	listLayout = new QVBoxLayout( 0, 0, 6, "listLayout");

	typeLabel = new QLabel(this, "typeLabel");
	listLayout->addWidget(typeLabel);
	typeCombo = new QComboBox( FALSE, this, "typeCombo" );
	listLayout->addWidget(typeCombo);

	colorList = new QListView( this, "colorList" );
	listLayout->addWidget(colorList);

	buttonLayout = new QHBoxLayout( 0, 0, 6, "buttonLayout");
	addButton = new QPushButton(this, "addButton");
	buttonLayout->addWidget(addButton);
	cancelButton = new QPushButton(this, "cancelButton");
	buttonLayout->addWidget(cancelButton);

	listLayout->addLayout(buttonLayout);
	mainLayout->addLayout(listLayout);
	formLayout->addLayout(mainLayout, 0, 0);

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
	typeCombo_activated(typeCombo->currentItem());

    // signals and slots connections
	connect(typeCombo, SIGNAL(activated(int)), this, SLOT(typeCombo_activated(int)));
	connect(colorWheel, SIGNAL(clicked(int, const QPoint&)), this, SLOT(colorWheel_clicked(int, const QPoint&)));
	colorWheel_clicked(0, QPoint(0, 0));
	connect(angleSpin, SIGNAL(valueChanged(int)), this, SLOT(angleSpin_valueChanged(int)));
	connect(brightnessSpin, SIGNAL(valueChanged(int)), this, SLOT(brightnessSpin_valueChanged(int)));
	connect(addButton, SIGNAL(clicked()), this, SLOT(addButton_clicked()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButton_clicked()));
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
	setCaption(tr("Color Wheel"));
	colorList->addColumn(tr("Color"));
	colorList->addColumn(tr("Value"));
	colorList->addColumn(tr("Name"));
	typeLabel->setText(tr("Select Method:"));
	angleLabel->setText(tr("Angle (0 - 365 degrees):"));
	brightnessLabel->setText(tr("Brightness (0 - 255):"));
	addButton->setText(tr("&Add Colors"));
	cancelButton->setText(tr("&Cancel"));

}

void ColorWheelDialog::fillColorList()
{
	colorList->clear();
	for (QMap<QString,CMYKColor>::iterator it = colorWheel->colorList.begin(); it != colorWheel->colorList.end(); ++it )
	{
		QListViewItem *item = new QListViewItem(colorList);
		item->setPixmap(0, colorWheel->sample(it.data().getShadeColorProof(brightnessSpin->value())));
		item->setText(1, it.data().name());
		item->setText(2, it.key());
	}
}

void ColorWheelDialog::typeCombo_activated(int index)
{
	colorList->clear();
	if (index == colorWheel->Monochromatic)
	{
		angleSpin->setEnabled(false);
		colorWheel->makeMonochromatic();
	}
	if (index == colorWheel->Analogous)
	{
		angleSpin->setEnabled(true);
		colorWheel->makeAnalogous();
	}
	if (index == colorWheel->Complementary)
	{
		angleSpin->setEnabled(false);
		colorWheel->makeComplementary();
	}
	if (index == colorWheel->Split)
	{
		angleSpin->setEnabled(true);
		colorWheel->makeSplit();
	}
	if (index == colorWheel->Triadic)
	{
		angleSpin->setEnabled(false); //TODO
		colorWheel->makeTriadic();
	}
	if (index == colorWheel->Tetradic)
	{
		angleSpin->setEnabled(false); //TODO
		colorWheel->makeTetradic();
	}
	fillColorList();
}

void ColorWheelDialog::colorWheel_clicked(int, const QPoint&)
{
	typeCombo_activated(typeCombo->currentItem());
	//fillColorList();
}

void ColorWheelDialog::angleSpin_valueChanged(int value)
{
	colorWheel->angle = value;
	typeCombo_activated(typeCombo->currentItem());
}

void ColorWheelDialog::brightnessSpin_valueChanged(int value)
{
	for (QMap<QString,CMYKColor>::iterator it = colorWheel->colorList.begin(); it != colorWheel->colorList.end(); ++it )
	{
		CMYKColor c = CMYKColor();
		c.fromQColor(it.data().getShadeColorProof(value));
		it.data() = c;
	}
	fillColorList();

}

void ColorWheelDialog::addButton_clicked()
{
	qDebug("TODO: implement ColorWheel::addButton_clicked");
	accept();
}


void ColorWheelDialog::cancelButton_clicked()
{
	qDebug("TODO: implement ColorWheel::cancelButton_clicked");
	reject();
}
