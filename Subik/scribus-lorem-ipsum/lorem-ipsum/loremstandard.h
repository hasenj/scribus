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

#ifndef _SCRIBUS_LOREMSTANDARD_H_
#define _SCRIBUS_LOREMSTANDARD_H_

#include <qstringlist.h>

/*! This is wrapper around the LI included in Scribus original
    distribution. Have to say it just takes paragraphs in LI
    file as atoms and combine 'em randomly.
    \author Petr Vanek
 */
class LoremStandard//: public QObject
{
	//Q_OBJECT
public:
    /*! path to the LI file */
	QString url;
    /*! count of the paragraphs to return */
	uint paragraphs;
    /*! List of the paragraphs from LI file */
	QStringList sentences;

    /*! Set the attrs.
        \param u given URL of the LI file
        \param para given count of the paragraphs
     */
	LoremStandard(QString u, uint para);
    /*! Nothing doing desc. */
	~LoremStandard();
    /*! Returns LI created.
        \return LI text
     */
	QString makeLorem();
};


#endif

