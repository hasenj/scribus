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

#ifndef _SCRIBUS_LOREMCONFIG_H_
#define _SCRIBUS_LOREMCONFIG_H_

#include <qxml.h>
#include <qstringlist.h>
#include <qptrlist.h>
#include "scribus.h"
#include "prefscontext.h"

/*! This class holds basic info of each LI dictionary.
 \author Petr Vanek
 */
class LoremInfo//: public QObject
{
	//Q_OBJECT
public:
    /*! Name of the dictionary - it is shown in GUI */
    QString name;
    /*! URL to the dictionary - filesystem, network... */
    QString url;
    /*! Description of the dict. Shown in GUI */
    QString description;
    /*! Type of the dict. This is a flag to decide "what to do" */
    QString type;

    /*! Constructor with info filled.
        \param n given name
        \param u given URL
        \param d given description
        \param t given type
     */
	LoremInfo(QString n, QString u, QString d, QString t);
    /*! Basic constructor */
    LoremInfo();
    /*! Nothing doing desc. */
    ~LoremInfo();
};

/*! Everything important for user is stored in this class.
    All LI dictionaries, parameters for generator and GUI.
    \author Petr Vanek
 */
class LoremConfig: public QXmlDefaultHandler
{
	//Q_OBJECT
public:
    /*! list of the LoremInfo instances */
    QPtrList<LoremInfo> info;
    /*! Obsolete? Error message */
	QString errMsg;
    /*! Preferences handler */
    PrefsContext *prefs;
    /*! Number of the returning paragraphs */
    uint paragraphs;
    /*! Average count of the sentences in the paragraph - it's used only
        sometimes */
    uint avgSentences;
    /*! Should the LI start with obligatory "Lorem Ipsum"? */
    bool shouldStartWith;

    /*! Reads configuration of this plugin */
	LoremConfig();
    /*! Saves the config */
	~LoremConfig();
    /*! This is the XML reader method because this class is inherited from
        QXmlDefaultHandler - here I specify what to do with XML elements.
        See QXmlDefaultHandler for more info.
        \param 1 unused
        \param 2 unused
        \param name name of the XML element
        \param attrs list of the element attributes
     */
	bool startElement(const QString&, const QString&, const QString &name, const QXmlAttributes &attrs);
};

#endif

