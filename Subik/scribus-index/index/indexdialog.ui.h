/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

/* $Id$ */

#include "scribus.h"

extern ScribusApp *ScApp;


void IndexDialog::init()
{
	heading1->insertItem("None");
	for (uint i = 5; i < ScApp->doc->Vorlagen.count(); ++i)
		if (ScApp->doc->Vorlagen[i].Vname.left(6) != "Index ")
			heading1->insertItem(ScApp->doc->Vorlagen[i].Vname);
}

void IndexDialog::cancelButton_pressed()
{
	reject();
}


void IndexDialog::okButton_pressed()
{
	QString toc("");
	accept();
}


void IndexDialog::heading1_textChanged( const QString & )
{

}


void IndexDialog::heading2_textChanged( const QString & )
{

}


void IndexDialog::heading3_textChanged( const QString & )
{

}


void IndexDialog::heading4_textChanged( const QString & )
{

}


void IndexDialog::heading5_textChanged( const QString & )
{

}


void IndexDialog::heading6_textChanged( const QString & )
{

}


void IndexDialog::heading7_textChanged( const QString & )
{

}
