#include "loremnetwork.h"
#include <qurl.h>


#include <iostream.h>

LoremNetwork::LoremNetwork(QString u)
{
	url = u;
	lorem = "";
	http = new QHttp;
	connect(http, SIGNAL(done(bool)), this, SLOT(fetchDone(bool)));
}

LoremNetwork::~LoremNetwork()
{
}

QString LoremNetwork::makeLorem()
{
	QUrl u(url);
	http->setHost(u.host());
	http->get("/generator2?" + u.query());
	qDebug(http->errorString());
	return lorem;
}


void LoremNetwork::fetchDone(bool error)
{
	qDebug(http->errorString());
	if (error)
		lorem = "NETWORK error" + errorString();
	else
		lorem = QString(readAll());
}
