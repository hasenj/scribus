#ifndef _VLNA_FRAME_H_
#define _VLNA_FRAME_H_

#include <scribus.h>

/**
 * This class applies VLNA on single specified page item - frame.
 */
class Frame : public QObject
{
    Q_OBJECT
public:
    /**
    \brief nothing doing constructor.

    I planned to write some 'funny' outputs here but decided not to do
    it that way... */
    Frame();
    /**
    \brief nothing doing destructor.

    without funny stuff too */
    ~Frame();
    /**
    \brief method to parse specified item.
    \param aFrame pointer to page object
    \retval uint count of the changes done
    */
    uint parse(PageItem *aFrame);
protected:
    /**
    \brief check if \a s string contains one of the affected preps.
    \param s qstring given from text frame
    \retval boolean
    */
    bool inPrepositions(QString &s);
};

#endif
