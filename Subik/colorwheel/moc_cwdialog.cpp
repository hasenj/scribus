/****************************************************************************
** ColorWheelDialog meta object code from reading C++ file 'cwdialog.h'
**
** Created: Mon Mar 21 21:08:36 2005
**      by: The Qt MOC ($Id$)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "cwdialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ColorWheelDialog::className() const
{
    return "ColorWheelDialog";
}

QMetaObject *ColorWheelDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ColorWheelDialog( "ColorWheelDialog", &ColorWheelDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ColorWheelDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ColorWheelDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ColorWheelDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ColorWheelDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ColorWheelDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"typeCombo_activated", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_varptr, "\x0e", QUParameter::In }
    };
    static const QUMethod slot_1 = {"colorWheel_clicked", 2, param_slot_1 };
    static const QUMethod slot_2 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "typeCombo_activated(int)", &slot_0, QMetaData::Public },
	{ "colorWheel_clicked(int,const QPoint&)", &slot_1, QMetaData::Public },
	{ "languageChange()", &slot_2, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"ColorWheelDialog", parentObject,
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ColorWheelDialog.setMetaObject( metaObj );
    return metaObj;
}

void* ColorWheelDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ColorWheelDialog" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool ColorWheelDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: typeCombo_activated((int)static_QUType_int.get(_o+1)); break;
    case 1: colorWheel_clicked((int)static_QUType_int.get(_o+1),(const QPoint&)*((const QPoint*)static_QUType_ptr.get(_o+2))); break;
    case 2: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ColorWheelDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool ColorWheelDialog::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool ColorWheelDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
