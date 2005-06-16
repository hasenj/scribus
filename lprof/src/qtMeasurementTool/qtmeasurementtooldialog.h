//
//  Little cms - profiler construction set
//  Copyright (C) 1998-2001 Marti Maria
//
// THIS SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
// EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
// WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
//
// IN NO EVENT SHALL MARTI MARIA BE LIABLE FOR ANY SPECIAL, INCIDENTAL,
// INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
// OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
// WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
// LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
// OF THIS SOFTWARE.
//
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

// Version 1.08b

#ifndef _H_qtmeasurement_tool
#define _H_qtmeasurement_tool

#include "qtmeasurementtooldialogbase.h"

#include <qfiledialog.h>
#include <qcombobox.h>
#include <qtabwidget.h>
#include <qcanvas.h>
#include <qimage.h>
#include <qpainter.h>
#include <qmultilineedit.h>
#include <qtextstream.h>
#include <qapplication.h>
#include <qspinbox.h>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qradiobutton.h>

#include "lcmsprf.h"

class QVBoxLayout;

// RTTI numbers 

#define imageRTTI 0xF0538
#define gridRTTI  0xF0539


// The back image

class ImageItem: public QCanvasRectangle {
	

public:

    ImageItem(QString ImageFile, 
			  const QString MonitorProfile, 
			  const QString ScannerProfile, 
			  QCanvas *canvas );

    int rtti () const { return imageRTTI; }
 
	void Reload(QString ImageFile, 
			  const QString MonitorProfile, 
			  const QString ScannerProfile, 
			  QCanvas *canvas );

    QImage image;
    QPixmap pixmap, proof;
	double sx, sy;
	BOOL lProof;

protected:



    void drawShape( QPainter & );	
	void TransformImage(const QString OutputProfile, 
							   const QString InputProfile, 
							   QImage& p);

	
};


// Picker layout. Coords are in 0...0xffff units

#define LAYOUT_MAX	(65535.)

class GridLayout {

public:

	void ScaleTo(int w, int h, QRect& Scaled);
	int  Scale(int n, int max);
 
	PATCH   p;
	QRect   rect;	

};




class GridItem: public QCanvasRectangle {
	

public:

    GridItem( QCanvas *canvas, QString TemplateFile, int SafeFrame );
    int rtti () const { return gridRTTI; }


	void Pick(QString InputProfile, QImage& Image, double sx, double sy);
	
	QList<GridLayout> Layout;

	double  UnShearFactor;
	double  SafeFrameFactor;


protected:

	int  ScaleX(int n) { return (int) ((double) (n * width())  / LAYOUT_MAX); }
	int  ScaleY(int n) { return (int) ((double) (n * height()) / LAYOUT_MAX); } 

	void ComputePatchRects(QRect& OurViewport, GridLayout* Patch, 
								 QRect& Frame, QRect& HotZone);

	void ComputeViewport(QRect& OurViewport, double sx, double sy);


    void drawShape(QPainter & );	
	
};


class qtMeasurementToolDialog;

// This class implements a visual dragger for pick templates

class FigureEditor : public QCanvasView {

    Q_OBJECT

public:

	 FigureEditor(qtMeasurementToolDialog &measurement_dialog, QCanvas& c, QWidget* parent=0, const char* name=0, WFlags f=0) : QCanvasView(&c,parent,name,f), MeasurementDialog(measurement_dialog) {}
    void clear();
    void resizeEvent( QResizeEvent* e );
protected:
    void contentsMousePressEvent(QMouseEvent*);
    void contentsMouseMoveEvent(QMouseEvent*);

signals:
    void status(const QString&);

protected:

	
    GridItem* moving;
	GridItem* sizing;
	GridItem* unshearing;
    QPoint moving_start;
    qtMeasurementToolDialog &MeasurementDialog;	
};


// The dialog

class qtMeasurementToolDialog : public qtMeasurementToolDialogBase
{
	Q_OBJECT

public:

	qtMeasurementToolDialog( QWidget* parent = 0, 
							 const char* name = 0, 
							 bool modal = FALSE, 
							 WFlags f = 0 );

	virtual ~qtMeasurementToolDialog();

	void LoadImage();
	void AddTemplate();

	const char* ConfigFile;
	const char* WorkTempFileName;

	BOOL LoadConfig();
	void SaveConfig();
	void Reload();

public slots:

    void slotPick();
	void slotLoad();	
	void slotSave();	
	void slotProof();	
	void slotSelSheet();
	void slotTabChanged();
	
protected:

	
	void SaveIT8(const char *fileName);
	void LoadIT8(const char *fileName);
	void DumpResultsToIT8(QList<GridLayout>& Layout);

	
	QCanvas*	     Canvas;
	QVBoxLayout* CanvasFrameLayout;
	GridItem*		 TheGrid;
	ImageItem*       TheImage; 
	FigureEditor*    FigEditor;	

	QString			 CurrentTemplate;
	double           CurrentSafeFrame;

	QString fn;			
};

// Statistics

class Statistic {

public:
		
	Statistic() { clear(); }
 

	void clear(void) { n = x = x2 = 0; }


	void	Add(double v) { x += v; x2 += (v * v); n  += 1.0;} 
		
	double	Std(void)	  { return sqrt((n * x2 - x * x) / (n*(n-1))); }
	double  Mean(void)	  { return x/n; }

	
protected:

	double n, x, x2;    
    
};

#endif

