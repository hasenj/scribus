#include "loremstandard.h"
#include <qfile.h>
#include <qtextstream.h>

LoremStandard::LoremStandard(uint para)
{
	paragraphs = para;
}

LoremStandard::~LoremStandard()
{
}

QString LoremStandard::makeLorem()
{
	QFile f("/home/subzero/devel/SCRIBUS/share/scribus/samples/LoremIpsum.txt");
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
