#include "loremconfig.h"

#define CFG "/home/subzero/devel/Subik/scribus-lorem-ipsum/lorem-ipsum/config/"

LoremInfo::LoremInfo(QString n, QString u, QString d, QString t)
{
    name = n;
	url = u;
    description = d;
    type = t;
}

LoremInfo::LoremInfo()
{
    name = "";
	url = "";
    description = "";
	type = "unknown";
}

LoremInfo::~LoremInfo()
{
}

LoremConfig::LoremConfig()
{
	errMsg = "OK";
	// parse the main config
	QXmlSimpleReader reader;
	reader.setContentHandler(this);
	QFile *f = new QFile(QString(CFG) + QString("/lorem-ipsum.xml"));
	if (!f->exists())
		errMsg = "Config file doesn't exists";
	QXmlInputSource* source = new QXmlInputSource(f);
	reader.parse(source);
	delete f;
	delete source;
}

LoremConfig::~LoremConfig()
{
}

bool LoremConfig::startElement(const QString&, const QString&, const QString &name, const QXmlAttributes &attrs)
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
            if (attrs.localName(i) == "type")
				newLorem->type = attrs.value(i);
        }
		/*qDebug("cfg: " + newLorem->name);
		qDebug("cfg: " + newLorem->url);
		qDebug("cfg: " + newLorem->description);
		qDebug("cfg: " + newLorem->type);*/
		info.append(newLorem);
        //delete newLorem;
    }
    return true;
}

