#ifndef _SCRIBUS_LOREMNETWORK_
#define _SCRIBUS_LOREMNETWORK_

#include <qstring.h>
#include <qhttp.h>
#include <qdialog.h>


class LoremNetwork: public QHttp
{
	// Can't find Plug-in/undefined reference with Q_OBJECT
	Q_OBJECT
public:
    QString url;
	QString lorem;
	QHttp *http;

    LoremNetwork(QString u);
    ~LoremNetwork();
    QString makeLorem();

public slots:
	void fetchDone(bool);
};

#endif

