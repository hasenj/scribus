#ifndef _SCRIBUS_VLNA_H_
#define _SCRIBUS_VLNA_H_

#include <scribus.h>

/** Calls the Plugin with the main Application window as parent
  * and the main Application Class as parameter */
extern "C" void Run(QWidget *d, ScribusApp *plug);


/** Returns the Name of the Plugin.
  * This name appears in the relevant Menue-Entrys */
extern "C" QString Name();


/** Returns the Type of the Plugin.

  \retval 1 = the Plugin is a normal Plugin, which appears in the Extras Menue
  \retval 2 = the Plugin is a Import Plugin, which appears in the Import Menue
  \retval 3 = the Plugin is a Export Plugin, which appears in the Export Menue
  \retval 4 = the Plugin is a resident Plugin   */
extern "C" int Type();


/** Base class of this plugin */
class Vlna : public QObject
{
    Q_OBJECT
public:
    /** scribus object */
    ScribusApp *plug;
    /** actualy processed item */
    PageItem *item;
    /** S. text structure */
    struct Pti *hl;

    /** initialize parameters from Scribus app and start the plug. */
    Vlna(QWidget *parent, ScribusApp *plug);
    /** nothing doing */
    ~Vlna();
private:
    /** debug/error dialog */
    void errMessage(QString aMessage);
    /** reads configuration from RC file */
    int readConfig();
    /** writes last used options into RC */
    void writeConfig(int aAction);
};

#endif
