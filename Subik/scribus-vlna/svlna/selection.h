#ifndef _VLNA_SELECTION_H_
#define _VLNA_SELECTION_H_

#include <scribus.h>

/**
 This class handles processing when user select 'selected items'
 option
 */
class Selection : public QObject
{
    Q_OBJECT
public:
    /** constructor
    \param plug reference to the Scribus API
    */
    Selection(ScribusApp *plug);
    /** nothing doing destructor */
    ~Selection();
    /** process selection.
    \retval uint count of the changes
    */
    uint parse();
protected:
    /** reference to the S. API. */
    ScribusApp *plug;
};

#endif
