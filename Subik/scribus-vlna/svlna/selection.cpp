#include <scribus.h>
#include "frame.h"
#include "selection.h"

Selection::Selection(ScribusApp *plug)
{
    this->plug = plug;
}

uint Selection::parse()
{
    Frame *item = new Frame();
    uint cnt = plug->doc->ActPage->SelItem.count();
    uint modify = 0;

    plug->FProg->setTotalSteps(cnt);

    for (uint i=0; i<cnt; i++) {
        plug->FProg->setProgress(i);
        modify += item->parse(plug->doc->ActPage->SelItem.at(i));
        //plug->FMess->setText(QObject::tr("Changes: ") +
        //    modify);
    } // for items

    plug->FProg->setProgress(cnt);

    return modify;
}

Selection::~Selection()
{
}
