/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
*   Copyright (C) 2007 by Franz Schmid                                     *
*   franz.schmid@altmuehlnet.de                                            *
*                                                                          *
*   This program is free software; you can redistribute it and/or modify   *
*   it under the terms of the GNU General Public License as published by   *
*   the Free Software Foundation; either version 2 of the License, or      *
*   (at your option) any later version.                                    *
*                                                                          *
*   This program is distributed in the hope that it will be useful,        *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*   GNU General Public License for more details.                           *
*                                                                          *
*   You should have received a copy of the GNU General Public License      *
*   along with this program; if not, write to the                          *
*   Free Software Foundation, Inc.,                                        *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.              *
****************************************************************************/

#ifndef LENSDIALOG_H
#define LENSDIALOG_H

#include <QDialog>
#include <QList>
#include <QPainterPath>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include "ui_lensdialogbase.h"
#include "scribusapi.h"
#include "scribusdoc.h"
#include "scribus.h"
class LensDialog;

class SCRIBUS_API LensItem : public QGraphicsEllipseItem
{
public:
	LensItem(QRectF geom, LensDialog *parent);
	~LensItem() {};
	void setStrength(double s);
	void updateEffect();
	QPainterPath lensDeform(const QPainterPath &source, const QPointF &offset, double m_radius, double s);
	double strength;
protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	LensDialog *dialog;
};

class SCRIBUS_API LensDialog : public QDialog, Ui::LensDialogBase
{
	Q_OBJECT

public:
	LensDialog(QWidget* parent, ScribusDoc *doc);
	~LensDialog() {};
	void lensSelected(LensItem *item);
	void setLensPositionValues(QPointF p);
	QGraphicsScene scene;
	QList<QPainterPath> origPath;
	QList<QGraphicsPathItem*> origPathItem;
	QList<LensItem*> lensList;
	int currentLens;

private slots:
	void doZoomIn();
	void doZoomOut();
	void addLens();
	void removeLens();
	void setNewLensX(double x);
	void setNewLensY(double y);
	void setNewLensRadius(double radius);
	void setNewLensStrength(double s);
};

#endif