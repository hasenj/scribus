#include "lorembase.h"
#include "lorembase.moc"

#define LOREM_CFG "/home/subzero/devel/Subik/scribus-lorem-ipsum/lorem-ipsum/config/lorem_ipsum.xml"
#define CFG "/home/subzero/devel/Subik/scribus-lorem-ipsum/lorem-ipsum/config/"

LoremInfo::LoremInfo(QString n, QString u, QString d)
{
    name = n;
	url = u;
    description = d;
}

LoremInfo::LoremInfo()
{
    name = "";
	url = "";
    description = "";
}

LoremInfo::~LoremInfo()
{
}

LoremData::LoremData(QString fileName)
{
    QStringList *two = new QStringList();
    QStringList *three = new QStringList();
    QStringList *many = new QStringList();
    // parse the fileName
	QXmlSimpleReader reader;
	QFile *f = new QFile(fileName);
    QXmlInputSource* source = new QXmlInputSource(f);
	reader.parse(source);
	delete f;
	delete source;
}

LoremData::~LoremData()
{
    delete two;
    delete three;
    delete many;
}

bool LoremData::startElement(const QString&, const QString&, const QString &name, const QXmlAttributes &attrs)
{
    if (attrs.localName(0) != "item")
        return false;
    if (name == "two")
        two->append(attrs.value(0));
    if (name == "three")
        three->append(attrs.value(0));
    if (name == "many")
        many->append(attrs.value(0));
    return true;
}

LoremBase::LoremBase()
{
	// parse the main config
	QXmlSimpleReader reader;
	reader.setContentHandler(this);
	QFile *f = new QFile(LOREM_CFG);
	QXmlInputSource* source = new QXmlInputSource(f);
	reader.parse(source);
	delete f;
	delete source;
}

LoremBase::~LoremBase()
{
}

bool LoremBase::startElement(const QString&, const QString&, const QString &name, const QXmlAttributes &attrs)
{
    if (name == "file")
    {
        LoremInfo *newLorem = new LoremInfo();
        for (uint i = 0; i < attrs.count(); ++i)
        {
            if (attrs.localName(i) == "name")
                newLorem->name += attrs.value(i);
            if (attrs.localName(i) == "url")
                newLorem->url += attrs.value(i);
			if (attrs.localName(i) == "description")
                newLorem->description += attrs.value(i);
        }
		QFile f(CFG + newLorem->url);
		if (f.exists())
			info.append(newLorem);
		else
		{
			qDebug("nonex");
			qDebug(newLorem->url);
			qDebug("\n\n");
		}
        delete newLorem;
    }
    return true;
}


