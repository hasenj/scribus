/****************************************************************************
** ColorWheel meta object code from reading C++ file 'colorwheelwidget.h'
**
** Created: Tue Mar 22 18:49:16 2005
**      by: The Qt MOC ($Id$)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "colorwheelwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ColorWheel::className() const
{
    return "ColorWheel";
}

QMetaObject *ColorWheel::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ColorWheel( "ColorWheel", &ColorWheel::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ColorWheel::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ColorWheel", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ColorWheel::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ColorWheel", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ColorWheel::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QLabel::staticMetaObject();
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_varptr, "\x0e", QUParameter::In }
    };
    static const QUMethod signal_0 = {"clicked", 2, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "clicked(int,const QPoint&)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"ColorWheel", parentObject,
	0, 0,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ColorWheel.setMetaObject( metaObj );
    return metaObj;
}

void* ColorWheel::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ColorWheel" ) )
	return this;
    return QLabel::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL clicked
void ColorWheel::clicked( int t0, const QPoint& t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_int.set(o+1,t0);
    static_QUType_varptr.set(o+2,&t1);
    activate_signal( clist, o );
}

bool ColorWheel::qt_invoke( int _id, QUObject* _o )
{
    return QLabel::qt_invoke(_id,_o);
}

bool ColorWheel::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: clicked((int)static_QUType_int.get(_o+1),(const QPoint&)*((const QPoint*)static_QUType_ptr.get(_o+2))); break;
    default:
	return QLabel::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool ColorWheel::qt_property( int id, int f, QVariant* v)
{
    return QLabel::qt_property( id, f, v);
}

bool ColorWheel::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
