/*
 * Copyright (c) Petr Vanek <petr@yarpen.cz>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

/* $Id$ */

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
