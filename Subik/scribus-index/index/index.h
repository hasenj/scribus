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

#ifndef _SCRIBUS_INDEX_H_
#define _SCRIBUS_INDEX_H_

#include "scribus.h"

/*! Calls the Plugin with the main Application window as parent
	and the main Application Class as parameter.
    \param d Parent QWidget
    \param plug reference to the main Scribus app.
 */
extern "C" void Run(QWidget *d, ScribusApp *plug);


/*! Returns the Name of the Plugin.
	This name appears in the relevant Menue-Entrys */
extern "C" QString Name();


/*! Returns the Type of the Plugin.
  \retval 1 = the Plugin is a normal Plugin, which appears in the Extras Menue
  \retval 2 = the Plugin is a Import Plugin, which appears in the Import Menue
  \retval 3 = the Plugin is a Export Plugin, which appears in the Export Menue
  \retval 4 = the Plugin is a resident Plugin	*/
extern "C" int Type();

/*! ID number of the plug. */
extern "C" int ID();

#endif


