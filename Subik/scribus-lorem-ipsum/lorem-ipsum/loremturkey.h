#ifndef _SCRIBUS_TURKEY_H_
#define _SCRIBUS_TURKEY_H_

#include <qstring.h>
#include <qstringlist.h>

class LoremTurkey
{
public:
    uint paragraphs;
    uint sentences;
	bool startWithLorem;

    QStringList words;

    LoremTurkey(QString file, uint par, uint sent, bool s);
    ~LoremTurkey();
    QString makeLorem();

private:
    QString makeParagraph();
    QString makeSentence();
    QString makeWord();
};

#endif

