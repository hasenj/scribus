#include "loremturkey.h"
#include "scribus.h"
#include <qfile.h>
#include <qdir.h>
#include <qdatetime.h>
#include <qtextcodec.h>


LoremTurkey::LoremTurkey(QString file, uint par, uint sent, bool s)
{
    paragraphs = par;
    sentences = sent;
	startWithLorem = s;

    // read data
	QFile f(PREL + QDir::convertSeparators("/share/scribus/lorem-ipsum/") + file);
    if (f.open(IO_ReadOnly))
    {
        QTextStream stream(&f);
		stream.setEncoding( QTextStream::UnicodeUTF8);
		stream.setCodec(QTextCodec::codecForName("utf8"));
        while (!stream.atEnd())
			words.append(stream.readLine().lower());
        f.close();
    }
    else
    {
        qDebug("FATAL ERROR reading turkey config!");
		return;
    }

    // init random
	QTime time = QTime::currentTime();
	srand(time.msec());
}

LoremTurkey::~LoremTurkey()
{
}

QString LoremTurkey::makeLorem()
{
	QString lorem = "";
	if (startWithLorem)
		lorem = "Lorem Ipsum. ";
    for (uint i = 0; i < paragraphs; ++i)
        lorem += makeParagraph();
	return lorem.stripWhiteSpace();
}

QString LoremTurkey::makeParagraph()
{
    QString lorem = "";
    for (uint i = 0; i < sentences; ++i)
        lorem += makeSentence();
    return lorem + '\n';
}

QString LoremTurkey::makeSentence()
{
	// TODO: implement turkey algorithm
    QString lorem = makeWord();
    // capitalize 1st char in the sentence
	lorem = lorem.left(1).upper() + lorem.right(lorem.length() - 1);

	for (uint i = 0; i < (4 + rand()%9); ++i)
        lorem += " " + makeWord();
    //return lorem + ". ";
	if (rand()%1 == 1)
		return lorem + ". ";
	return lorem + ", ";
}

QString LoremTurkey::makeWord()
{
	// TODO: implement turkey algorithm
	return words[rand()%words.count() + 1];
}

