#include <scribus.h>
#include <qobject.h>
#include "vlnapage.h"
#include "frame.h"

VlnaPage::VlnaPage(ScribusApp *plug)
{
    this->plug = plug;
}

VlnaPage::~VlnaPage()
{
}

uint VlnaPage::parse(Page *page)
{
    Frame *item = new Frame();

    uint cnt = page->Items.count();
    uint modify = 0;

    plug->FProg->setTotalSteps(cnt);
    plug->view->GotoPage(page->PageNr);

    for (uint i=0; i<cnt; i++) {
        plug->FProg->setProgress(i);
        plug->FMess->setText(page->PageNam);
        modify += item->parse(page->Items.at(i));
    } // for items

    delete item;
    plug->FProg->setProgress(cnt);
    return modify;
}

uint VlnaPage::parseAll()
{
    uint modify = 0;

    for (uint i=0; i<plug->view->Pages.count(); i++) {
        plug->FMess->setText(QObject::tr("Page: ")
                + i
                + plug->view->Pages.at(i)->PageNam);
        modify += parse(plug->view->Pages.at(i));
    }
    return modify;
}
