#include "loremnetwork.h"
#include <qurl.h>
#include <iostream.h>
LoremNetwork::LoremNetwork(QString u)
{
	url = u;
	lorem = "";
	qDebug(errorString());
	cout << this << endl;
	connect(this, SIGNAL(done(bool)), this, SLOT(fetchDone(bool)));
}

LoremNetwork::~LoremNetwork()
{
}

QString LoremNetwork::makeLorem()
{
	QUrl u(url);

	setHost(u.host());
	get("/generator2?" + u.query());

	return lorem;

}


void LoremNetwork::fetchDone(bool error)
{
	if (error)
		lorem = "NETWORK error" + errorString();
	else
		lorem = QString(readAll());
}
