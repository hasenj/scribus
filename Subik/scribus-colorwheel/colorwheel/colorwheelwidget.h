#ifndef COLORWHEELWIDGET_H
#define COLORWHEELWIDGET_H

#include <qlabel.h>
#include <qvaluevector.h>
#include <cmykcolor.h>


class ColorWheel : public QLabel
{
	Q_OBJECT

	public:
		ColorWheel(QWidget * parent, const char * name = 0);
		~ColorWheel();

		enum MethodType {
			Monochromatic,
			Analogous,
			Complementary,
			Split,
			Triadic,
			Tetradic
		};

		uint xsize;
		uint ysize;
		int angle;

		QPoint actualPoint;
		QRgb actualRgb;
		QMap<QString, CMYKColor> colorList;

		void paintWheel(QValueVector<QPoint>);
		QString getTypeDescription(MethodType aType);
		QPixmap sample(QColor);

		void makeMonochromatic();
		void makeAnalogous();
		void makeComplementary();
		void makeSplit();
		void makeTriadic();
		void makeTetradic();

	signals:
		void clicked(int, const QPoint &);

	protected:
		void mouseReleaseEvent(QMouseEvent *);
		QRgb getPointColor(QPoint);
		void sampleByAngle(double, QString);
		double pointAngle(QPoint);
		void baseColor();

};

#endif
