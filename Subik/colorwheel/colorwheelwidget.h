#ifndef COLORWHEELWIDGET_H
#define COLORWHEELWIDGET_H

#include <qlabel.h>
#include <qvaluevector.h>


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
		QPoint actualPoint;
		QRgb actualRgb;
		QMap<QString,QPixmap> colorList;
		QMap<int,QColor> wheelValues;
		QMap<QRgb, int> wheelRgb;

		void paintWheel(QValueVector<QPoint>);
		QString getTypeDescription(MethodType aType);

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
		QPixmap getPreview(QRgb);
		void sampleByColor(QRgb, QString);
		void sampleByAngle(double, QString);
		double pointAngle(QPoint);

};

#endif
