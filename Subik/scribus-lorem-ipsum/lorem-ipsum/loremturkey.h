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

#ifndef _SCRIBUS_TURKEY_H_
#define _SCRIBUS_TURKEY_H_

#include <qstring.h>
#include <qstringlist.h>
#include <qmap.h>

/*! This is based on the Tomas Znamenacek's Turkey.sf.net dummy text
    generator.
    \author Petr Vanek
 */
class LoremTurkey
{
public:
    /*! Count of the paragraphs */
    uint paragraphs;
    /*! Count of the sentences per paragraphs. It's randomized a little bit. */
    uint sentences;
    /*! Flag to hold info that final LI should start with obligatory
        phrase "Lorem Ipsum" */
	bool startWithLorem;
    /*! List of the strings readed from given dictionary. */
    QStringList words;

	QMap<QString, QValueList<QChar> > table;

    /*! Reads base config for turkey based LI.
        \param file filename of the dictioanry
        \param par count of the paragraphs
        \param sent count of the sentences
        \param s should start with LI flag
     */
    LoremTurkey(QString file, uint par, uint sent, bool s);
    /*! Nothing doing desc. */
    ~LoremTurkey();
    /*! Returns LI created.
        \return LI text
     */
    QString makeLorem();

private:
    /* Create on paragraph */
    QString makeParagraph();
    /* Create one sentence */
    QString makeSentence();
    /* Create one word */
    QString makeWord();
	void analyzeString(QString aString);
	QChar getNext(QString prefix);
};

#endif

