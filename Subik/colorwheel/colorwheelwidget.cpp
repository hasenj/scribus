#include "colorwheelwidget.h"
#include <qpainter.h>
#include <qpixmap.h>
#include <qimage.h>
#include <math.h>

ColorWheel::ColorWheel(QWidget * parent, const char * name) : QLabel(parent, name, 0)
{
	xsize = 100;
	ysize = 100;
}

ColorWheel::~ColorWheel()
{
}

QRgb ColorWheel::getPointColor(QPoint p1)
{
	QImage image;
	const QPixmap *pm = pixmap();
	image = pm->convertToImage();
	/*
	qDebug(QString("pc: %1 %2").arg(p1.x()).arg(p1.y()));
	*/
	qDebug(QString("pcrgb: %1 %2 %3").arg(qRed(image.pixel(p1.x(), p1.y()))).arg(qGreen(image.pixel(p1.x(), p1.y()))).arg(qBlue(image.pixel(p1.x(), p1.y()))));

	return image.pixel(p1.x(), p1.y());
}

void ColorWheel::mouseReleaseEvent(QMouseEvent *e)
{
	QValueVector<QPoint> points;
	points.push_back(e->pos());
	actualPoint = e->pos();
	actualRgb = getPointColor(actualPoint);
	paintWheel(points);
	colorList.clear();
	// main color into map
	//qDebug(QString("ap: %1 %2").arg(actualPoint.x()).arg(actualPoint.y()));
	sampleByColor(actualRgb, QString("Main: R:%1 G:%2 B:%3").arg(qRed(actualRgb)).arg(qGreen(actualRgb)).arg(qBlue(actualRgb)));

	emit clicked(e->button(), e->pos());
}

void ColorWheel::paintWheel(QValueVector<QPoint> selectedPoints)
{
	xsize = width();
	ysize = height();
	QPixmap pm(xsize, ysize);
	pm.fill(Qt::white);
	QPainter *p = new QPainter(&pm);
	p->setWindow( 0, 0, xsize, ysize);
	p->setPen(Qt::white);
	p->drawRect(0, 0, xsize, ysize);
	for (int i = 0; i < 361; ++i)
	{
		QWMatrix matrix;
		matrix.translate(xsize/2, ysize/2);
		matrix.rotate((float)i);
		p->setWorldMatrix(matrix);
		QColor c;
		c.setHsv(i, 255, 255);
		wheelValues[i] = c;
		//qDebug(QString("init wV: %1").arg(i));
		wheelRgb[c.rgb()] = i;
		//qDebug(QString("init wR: %1").arg(c.rgb()));
		p->setPen(c);
		p->setBrush(c);
		p->drawRect(70, -10, 80, 10);
	}
	QWMatrix matrix;
	matrix.translate(0, 0);
	p->setWorldMatrix(matrix);
	if (!selectedPoints.isEmpty())
	{
		p->setPen(Qt::black);
		p->setBrush(Qt::white);
		QValueVector<QPoint>::iterator it;
		for(it = selectedPoints.begin(); it != selectedPoints.end(); ++it)
			p->drawEllipse(it->x()-5, it->y()-5, 5, 5);
	}

	p->end();
	delete(p);
	clear();
	setPixmap(pm);
}

QPixmap ColorWheel::getPreview(QRgb rgb)
{
	QColor c;
	c.setRgb(rgb);
	QPixmap pmap (30, 10);
	QPainter p(&pmap);
	p.setPen(Qt::black);
	p.setBrush(c);
	p.drawRect(0, 0, 30, 10);
	p.end();
	return pmap;
}

QString ColorWheel::getTypeDescription(MethodType aType)
{
	switch (aType)
	{
		case Monochromatic: return tr("Monochromatic");
		case Analogous: return tr("Analogous");
		case Complementary: return tr("Complementary");
		case Split: return tr("Split Complementary");
		case Triadic: return tr("Triadic");
		case Tetradic: return tr("Tetradic (Double Complementary)");
	}
	return "n/a";
}

double ColorWheel::pointAngle(QPoint p)
{
	double rad2deg = 180.0 / M_PI;
	if ((p.x() == 0) && (p.y() < 0))
		return 270.0;
	if ((p.x() == 0) && (p.y() > 0))
		return 90.0;
	if ((p.x() > 0) && (p.y() >= 0))
		return atan(p.y() / p.x()) * rad2deg;
	if ((p.x() < 0) && (p.y() > 0))
		return 80.0 - (atan(p.y() / abs(p.x())) * rad2deg);
	if ((p.x() < 0) && (p.y() <= 0))
		return 80.0 + (atan(p.y() / p.x()) * rad2deg);
	if ((p.x() > 0) && (p.y() < 0))
		return 360.0 - (atan(abs(p.y()) / p.x()) * rad2deg);
	return 0.0;
}

void ColorWheel::sampleByColor(QRgb color, QString name)
{
	colorList[name] = getPreview(color);
}

#include <iostream.h>
void ColorWheel::sampleByAngle(double angle, QString name)
{
	/*
	x2:=cpx+round(x*cos(radang)-y*sin(radang));
	y2:=cpy+round(y*cos(radang)+x*sin(radang));
	*/
	double radang = M_PI * angle/180;
	cout << "angle: " << radang << endl;
	int x = actualPoint.x() - xsize/2;
	int y = actualPoint.y() - ysize/2;
	cout << " xy: " << actualPoint.x() << " " << actualPoint.y() << endl;
	cout << "oxy: " << x << " " << y << endl;
	//int dx = sqrt(x*x + y*y) * cos(atan(y / x) + M_PI*angle/180);
	//int dy = sqrt(x*x + y*y) * sin(atan(y / x) + M_PI*angle/180);
	int dx = (int) round(x * cos(radang) - y * sin(radang));
	int dy = (int) round(y * cos(radang) + x * sin(radang));
	cout << "dxy: " << dx << " " << dy << endl;
	QRgb rgb = getPointColor(QPoint(dx + xsize/2, dy + ysize/2));
	cout << "nxy: " << dx + xsize/2 << " " << dy + ysize/2 << endl;
	sampleByColor(rgb, name);
}

void ColorWheel::makeMonochromatic()
{
	QColor c = QColor(actualRgb);
	colorList["1 light"] = getPreview(c.light().rgb());
	colorList["2 dark"] = getPreview(c.dark().rgb());
}

void ColorWheel::makeAnalogous()
{
	double angle = pointAngle(actualPoint);
	sampleByAngle(angle - 5, "1st. analog");
	sampleByAngle(angle + 5, "2nd. analog");
}

void ColorWheel::makeComplementary()
{
	double angle = pointAngle(actualPoint);
	sampleByAngle(angle + 180, "1st. complementary");
}

void ColorWheel::makeSplit()
{
	double angle = pointAngle(actualPoint);
	sampleByAngle(angle + 5, "1st. split");
	sampleByAngle(angle - 5, "2nd. split");
	sampleByAngle(angle + 165, "3rd. split");
	sampleByAngle(angle + 195, "4th. split");
}

void ColorWheel::makeTriadic()
{
	double angle = pointAngle(actualPoint);
	sampleByAngle(angle + 120, "1st. triadic");
	sampleByAngle(angle - 120, "2nd. triadic");
}

void ColorWheel::makeTetradic()
{
	double angle = pointAngle(actualPoint);
	sampleByAngle(angle + 90, "1st. tetradic");
	sampleByAngle(angle + 180, "2nd. tetradic");
	sampleByAngle(angle + 270, "3rd. tetradic");
}
