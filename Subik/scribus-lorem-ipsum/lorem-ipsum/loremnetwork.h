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

