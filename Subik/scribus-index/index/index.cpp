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

#include "index.h"
#include "indexdialog.h"

extern ScribusApp *ScApp;


QString Name()
{
	return QObject::tr("&Index and toc...");
}

int Type()
{
	return 1;
}

int ID()
{
	return 667;
}

void Run(QWidget *d, ScribusApp *plug)
{
	// create basic toc styles (if it doesn't exists)
	for (uint i = 1; i < 8; ++i)
	{
		bool styleExists = FALSE;
		QString name("Index %1");
		name = name.arg(i);
		// just non-existing
		for (uint j = 5; j < ScApp->doc->Vorlagen.count(); ++j)
			if (ScApp->doc->Vorlagen[j].Vname == name)
				styleExists = TRUE;

		if (!styleExists)
		{
			struct StVorL sty;
			sty.Vname = name;
			sty.LineSpa = ((ScApp->doc->Dsize / 10.0)
					* static_cast<double>(ScApp->doc->AutoLine) / 100)
					+ (ScApp->doc->Dsize / 10.0);
			sty.Ausri = 0;
			sty.Indent = 0;
			sty.First = 0;
			sty.Avor = 0;
			sty.Anach = 0;
			sty.Font = ScApp->doc->Dfont;
			sty.FontSize = ScApp->doc->Dsize;
			sty.TabValues.clear();
			sty.Drop = false;
			sty.DropLin = 2;
			sty.FontEffect = 0;
			sty.FColor = ScApp->doc->Dbrush;
			sty.FShade = ScApp->doc->Dshade;
			sty.SColor = ScApp->doc->Dpen;
			sty.SShade = ScApp->doc->Dshade2;
			sty.BaseAdj = false;
			ScApp->doc->Vorlagen.append(sty);
		} // if
	} // for
	// dialog
	IndexDialog *dia = new IndexDialog(0, 0, TRUE, 0);
	dia->exec();
	delete dia;
}

