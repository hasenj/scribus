#include "loremstandard.h"
#include "scribus.h"
#include <qfile.h>
#include <qdir.h>
#include <qtextstream.h>


LoremStandard::LoremStandard(QString u, uint para)
{
	paragraphs = para;
	url = u;
}

LoremStandard::~LoremStandard()
{
}

QString LoremStandard::makeLorem()
{
	QFile f(PREL + QDir::convertSeparators(url));
	if (f.open(IO_ReadOnly))
	{
		QTextStream stream(&f);
		while (!stream.atEnd())
			sentences.append(stream.readLine());
		f.close();
	}
	else
		return("Lorem Ipsum FATAL ERROR reading standard config!");

	QString lorem = sentences[0];
	uint turn = 1;
	for (uint i = 1; i < paragraphs; ++i)
	{
		if (turn >= sentences.count() - 1)
			turn = 0;
		else
			++turn;
		lorem += sentences[turn] + "\n";
	}// for
	return lorem.stripWhiteSpace();
}
