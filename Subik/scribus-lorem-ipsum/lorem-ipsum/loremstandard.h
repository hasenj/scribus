#ifndef _SCRIBUS_LOREMSTANDARD_H_
#define _SCRIBUS_LOREMSTANDARD_H_

#include <qstringlist.h>

class LoremStandard//: public QObject
{
	//Q_OBJECT
public:
	QString url;
	uint paragraphs;
	QStringList sentences;

	LoremStandard(QString u, uint para);
	~LoremStandard();
	QString makeLorem();
};


#endif

