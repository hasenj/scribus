#include "loremipsum.h"
#include "loremipsum.moc"

extern ScribusApp *ScApp;


QString Name()
{
	return QObject::tr("&Lorem Ipsum...");
}

int Type()
{
	return 1;
}

int ID()
{
	return 666;
}

void Run(QWidget *d, ScribusApp *plug)
{
	// only one selection check
	if (ScApp->doc->ActPage->SelItem.count() != 1)
	{
		ScApp->FMess->setText("Select only one frame");
		return;
	}
	PageItem *item = ScApp->doc->ActPage->Items.at(ScApp->doc->ActPage->SelItem.at(0)->ItemNr);
	if (item->Ptext.count() != 0)
	{
		ScApp->FMess->setText("Cannot replace text in the frame");
		return;
	}
	LoremIpsum *li = new LoremIpsum();
	ScApp->FMess->setText(li->makeText());
	delete li;
}


LoremIpsum::LoremIpsum()
{
	// init fro rand()
	QTime time = QTime::currentTime();
	srand(time.msec());
	// attributes
	paragraphs = 5;
	startWithLorem = true;
	item = ScApp->doc->ActPage->Items.at(ScApp->doc->ActPage->SelItem.at(0)->ItemNr);
}

LoremIpsum::~LoremIpsum()
{
	item = NULL;
}

QString LoremIpsum::makeText()
{
	QString loremText;

	startWithLorem ? loremText = "Lorem ipsum dolor sit amet. " : loremText = "";

	for (uint i = 0; i <= paragraphs; ++i)
		loremText += makeParagraph();

	// fill text into frame
	item->Ptext.clear();
	for (uint i = 0; i < loremText.length(); ++i)
	{
		struct Pti *hg = new Pti;
		hg->ch = loremText.at(i);
		if (hg->ch == QChar(10))
			hg->ch = QChar(13);
		hg->cfont = item->IFont;
		hg->csize = item->ISize;
		hg->ccolor = item->TxtFill;
		hg->cshade = item->ShTxtFill;
		hg->cstroke = item->TxtStroke;
		hg->cshade2 = item->ShTxtStroke;
		hg->cscale = item->TxtScale;
		hg->cextra = 0;
		hg->cselect = false;
		hg->cstyle = 0;
		hg->cab = ScApp->doc->CurrentABStil;
		hg->xp = 0;
		hg->yp = 0;
		hg->PRot = 0;
		hg->PtransX = 0;
		hg->PtransY = 0;
		item->Ptext.append(hg);
	} // for
	// funny feedback
	return resultComment();
}

QString LoremIpsum::makeParagraph()
{
	QString loremText = "";
	for (uint i = 0; i < (rand()%7+1); ++i) // rand 4, 7
		loremText += makeSentence();
	return loremText + '\n';
}

QString LoremIpsum::makeSentence()
{
	QString loremText = "";
	for (uint i = 0; i < (rand()%4+1); ++i) // rand 3, 4
		loremText += makeClause() + '.';
	return loremText;
}

#declare CNT_CFG_LOREMS 3
QString LoremIpsum::makeClause()
{
	QString loremText = "";

	/* pseudocode
	for (uint i = 0; i < (rand()%4+1); ++i)
	{
		uint wordType= rand()%CNT_CFG_LOREMS+1;
		loremText += chosenLorem[wordType].at(rand()%chosenLorem[wordType].length()+1);
	}
	*/
	return loremText;
}

QString LoremIpsum::resultComment()
{
	/* TODO: phrases
	"Remarkably well done!","Beautiful execution, what a fabulous $lang1!!",
	  "Extremely well done!","Very well done!","Magnificently well done!",
	  "Superb performance, exquisite $lang1 delivered!",
	  "No doubt, the mother of all $lang1\s! Perfect.","Brilliant execution, this is a beauty!",
	  "Extraordinary performance!","This $lang1 is perfect!","Congratulate yourself ...the mother of 'em $lang1\s!",
	  "Fella, you now how to press a button, respect!","Best $lang1 ever generated, governor!",
	  "Awesome result, give yourself a hand!","Have a cigar - this $lang1 is sweet!"
	*/
	return QString("Remarkably well done!");
}

