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

#include "loremconfig.h"
#include "prefsfile.h"

#include <qdir.h>

extern PrefsFile *prefsFile;


LoremInfo::LoremInfo(QString n, QString u, QString d, QString t)
{
    name = n;
	url = u;
    description = d;
    type = t;
}

LoremInfo::LoremInfo()
{
    name = "";
	url = "";
    description = "";
	type = "unknown";
}

LoremInfo::~LoremInfo()
{
}
#include <iostream.h>
LoremConfig::LoremConfig()
{
	// cfg
	prefs = prefsFile->getPluginContext("lorem-ipsum");
	paragraphs = prefs->getUInt("paragraphs", 4);
	avgSentences = prefs->getUInt("avgSentences", 4);
	shouldStartWith = prefs->getBool("shouldStartWith", TRUE);
	errMsg = "OK";
	// parse the main config
	QXmlSimpleReader reader;
	reader.setContentHandler(this);
	QFile *f = new QFile(PREL + QDir::convertSeparators("/share/scribus/lorem-ipsum/lorem-ipsum.xml"));
	if (!f->exists())
		errMsg = "Config file doesn't exists";
	QXmlInputSource* source = new QXmlInputSource(f);
	reader.parse(source);
	delete f;
	delete source;
}

LoremConfig::~LoremConfig()
{
	prefs->set("paragraphs", paragraphs);
	prefs->set("avgSentences", avgSentences);
	prefs->set("shouldStartWith", shouldStartWith);
}

bool LoremConfig::startElement(const QString&, const QString&, const QString &name, const QXmlAttributes &attrs)
{
    if (name == "file")
    {
		LoremInfo *newLorem = new LoremInfo();
        for (uint i = 0; i < attrs.count(); ++i)
        {
            if (attrs.localName(i) == "name")
                newLorem->name += attrs.value(i);
            if (attrs.localName(i) == "url")
				newLorem->url += attrs.value(i);
			if (attrs.localName(i) == "description")
				newLorem->description += attrs.value(i);
            if (attrs.localName(i) == "type")
				newLorem->type = attrs.value(i);
        }
		/*qDebug("cfg: " + newLorem->name);
		qDebug("cfg: " + newLorem->url);
		qDebug("cfg: " + newLorem->description);
		qDebug("cfg: " + newLorem->type);*/
		info.append(newLorem);
        //delete newLorem;
    }
    return true;
}

