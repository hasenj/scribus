#ifndef _VLNA_PAGE_H_
#define _VLNA_PAGE_H_

#include <scribus.h>

/** Handles page related options from GUI dialog. */
class VlnaPage : public QObject
{
    Q_OBJECT
public:
    /** constructor with S. API reference. */
    VlnaPage(ScribusApp *plug);
    /** nothing doing destructor. */
    ~VlnaPage();
    /** make one page
    \param page - now \a page is processed
    */
    uint parse(Page *page);
    /** process all pages in document */
    uint parseAll();
private:
    /** Scribus api reference object */
    ScribusApp *plug;
};

#endif
