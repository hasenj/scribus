/*! This is the Scribus Short Words various constants and preprocessor
definitions. There should be all SPACEs defined (unbreak, em, en etc.)

This code is based on the Scribus-Vlna plug in rewritten for
international use.

2004 Petr Vanek <petr@yarpen.cz>

This program is free software - see LICENSE file in the distribution
or documentation
*/

#ifndef _SCRIBUS_SHORTVER_H_
#define _SCRIBUS_SHORTVER_H_

#define VLNA_VERSION "1.2.1cvs"

#define RC_PATH QDir::convertSeparators(QString(PLUGINDIR) + "/scribus-short-words.rc")
#define RC_PATH_USR QDir::homeDirPath() + QDir::convertSeparators("/.scribus/scribus-short-words.rc")

//#define UNBREAKABLE_SPACE QString(QChar(0x83))+QString(QChar(0x20))
//#define UNBREAKABLE_SPACE QString(QChar(0xA0))
#define UNBREAKABLE_SPACE QString(QChar(29))
#define SPACE QChar(' ')

#endif
