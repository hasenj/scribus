#ifndef _SCRIBUS_LOREMSTANDARD_H_
#define _SCRIBUS_LOREMSTANDARD_H_

#include <qstringlist.h>

class LoremStandard
{
	public:
		uint paragraphs;
		QStringList sentences;

		LoremStandard(uint para);
		~LoremStandard();
		QString makeLorem();
};


#endif

