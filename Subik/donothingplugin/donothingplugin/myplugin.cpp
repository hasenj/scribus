#include "myplugin.h"
#include <qstring.h>

QString Name()
{
    return "Do Nothing Plugin";
}


int Type()
{
    return 1;
}


void Run(QWidget *d, ScribusApp *plug)
{
}

