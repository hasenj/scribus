#ifndef _SCRIBUS_LOREMIPSUM_H_
#define _SCRIBUS_LOREMIPSUM_H_

#include "scribus.h"

/*! Calls the Plugin with the main Application window as parent
	and the main Application Class as parameter */
extern "C" void Run(QWidget *d, ScribusApp *plug);


/*! Returns the Name of the Plugin.
	This name appears in the relevant Menue-Entrys */
extern "C" QString Name();


/*! Returns the Type of the Plugin.
  \retval 1 = the Plugin is a normal Plugin, which appears in the Extras Menue
  \retval 2 = the Plugin is a Import Plugin, which appears in the Import Menue
  \retval 3 = the Plugin is a Export Plugin, which appears in the Export Menue
  \retval 4 = the Plugin is a resident Plugin	*/
extern "C" int Type();

/*! ID number of the plug. */
extern "C" int ID();

#endif

