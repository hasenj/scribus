#ifndef _SCRIBUS_LOREMCONFIG_H_
#define _SCRIBUS_LOREMCONFIG_H_

#include <qxml.h>
#include <qstringlist.h>
#include <qptrlist.h>
#include "scribus.h"

class LoremInfo//: public QObject
{
	//Q_OBJECT
public:
    QString name;
    QString url;
    QString description;
    QString type;

	LoremInfo(QString n, QString u, QString d, QString t);
    LoremInfo();
    ~LoremInfo();
};

class LoremConfig: public QXmlDefaultHandler
{
	//Q_OBJECT
public:
    /*! list of the LoremInfo instances */
    QPtrList<LoremInfo> info;
	QString errMsg;

	LoremConfig();
	~LoremConfig();
	bool startElement(const QString&, const QString&, const QString &name, const QXmlAttributes &attrs);
};

#endif

