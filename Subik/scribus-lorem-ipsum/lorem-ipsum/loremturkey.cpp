/*
 * Copyright (c) Petr Vanek <petr@yarpen.cz>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

/* $Id$ */

#include "loremturkey.h"
#include "scribus.h"
#include <qfile.h>
#include <qdir.h>
#include <qdatetime.h>
#include <qtextcodec.h>

// TODO: config! throw() a exceptions
#define PREFIX_LENGTH 3

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
			analyzeString(stream.readLine().lower());
			//words.append(stream.readLine().lower());
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
	//return words[rand()%words.count() + 1];
	QValueList<QChar> startChars(table[" "]);
	QChar next(startChars.at(rand()%startChars.size()));
	QString prefix(" " + next);
	QString word(next);

	while (TRUE)
	{
		for (uint i = prefix.length(); i > 0; --i)
		{
			try {
				next = getNext(prefix.mid(0, i));
			} catch {
				continue;
			}
			break;
		} // for

		if (next.isWhite())
			return word;

		word += next;
		prefix += next;

		if (prefix.length() > PREFIX_LENGTH)
			prefix = prefix.mid(0, prefix.length() - PREFIX_LENGTH);
	} // while
}

void LoremTurkey::analyzeString(QString aString)
{
	if (aString.isEmpty())
		return;

	for (uint i = 0; i <= PREFIX_LENGTH; ++i)
	{
		for (uint j = i; j < aString.length(); ++j)
		{
			QString prefix = aString.mid(j-i, j);
			QChar next = aString.at(j);
			if (!table.contains(prefix))
				table.insert(prefix, QStringList());
			table[prefix].append(next);
		} //for j
	} //for i
}

QChar LoremTurkey::getNext(QString prefix)
{
	if (!table.contains(prefix))
		throw(1);
	QValueList<QChar> nextChars(table[prefix]);
	return nextChars.at(rand()%nextChars.size());
}
