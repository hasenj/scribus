#ifndef _SCRIBUS_LOREMBASE_H_
#define _SCRIBUS_LOREMBASE_H_

#include <qxml.h>
#include <qstringlist.h>
#include <qptrlist.h>
#include "scribus.h"

class LoremInfo: public QObject
{
	//Q_OBJECT
public:
    QString name;
    QString url;
    QString description;

    LoremInfo(QString n, QString u, QString d);
    LoremInfo();
    ~LoremInfo();
};

class LoremData: public QXmlDefaultHandler
{
	//Q_OBJECT
public:
    QStringList *two;
    QStringList *three;
    QStringList *many;

    LoremData(QString fileName);
    ~LoremData();
	bool startElement(const QString&, const QString&, const QString &name, const QXmlAttributes &attrs);
};

class LoremBase: public QXmlDefaultHandler
{
	//Q_OBJECT
public:
    /*! list of the LoremInfo instances */
    QPtrList<LoremInfo> info;

	LoremBase();
	~LoremBase();
	bool startElement(const QString&, const QString&, const QString &name, const QXmlAttributes &attrs);
};

#endif

