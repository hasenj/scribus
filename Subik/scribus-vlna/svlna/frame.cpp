#include "frame.h"
#include <scribus.h>
#include <qstring.h>

#define UNBREAKABLE_SPACE 0xA0

Frame::Frame()
{
}

uint Frame::parse(PageItem *aFrame)
{
    // string history
    QString prev(" ");
    QString prev2(" ");
    // text structure
    struct Pti *hl;
    // cnt of changes
    uint changes = 0;

    // just textframes processed
    if (aFrame->PType==4) {
        for (uint i=0; i<aFrame->MaxChars; i++) {
            hl = aFrame->Ptext.at(i);
            //change?
            if ((hl->ch==" ") & (inPrepositions(prev)) & (prev2==" ")) {
                hl->ch = QChar(UNBREAKABLE_SPACE);
                changes++;
            } // if
            // move history
            prev2 = prev;
            prev = hl->ch;
        } //for maxchars
    } // if ptype 4

    return changes;
}

bool Frame::inPrepositions(QString &s)
{
    QString preps("KkSsVvZzOoUuIiA");
    if (preps.contains(s, TRUE)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

Frame::~Frame()
{
}
