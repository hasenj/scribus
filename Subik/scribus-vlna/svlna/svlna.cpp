#include "svlna.h"
#include "vlnadialog.h"
#include "selection.h"
#include "vlnapage.h"

#include <qmessagebox.h>
#include <qtextcodec.h>
#include <qcursor.h>
#include <qprogressdialog.h>
#include <qfile.h>
#include <qdir.h>

QString Name()
{
    return QObject::tr("TeX Vlna...");
}


int Type()
{
    return 1;
}


void Run(QWidget *d, ScribusApp *plug)
{
    // PREL defined in .pro file
    QString pPath = PREL;
    pPath += "/lib/scribus/plugins/";

    QTranslator *trans = new QTranslator(0);
    //trans->load("libscribus-vlna."+QTextCodec::locale()+".qm", pPath);
    trans->load(
        QString("libscribus-vlna.")
        + QString(QTextCodec::locale()).left(2)
        +QString(".qm"),
        pPath
        );
    qApp->installTranslator(trans);

    Vlna *vlna = new Vlna(d, plug);

    delete vlna;
    delete trans;
}

/*
 * base class
 */
Vlna::Vlna(QWidget *parent, ScribusApp *p)
{
    Selection *sel = new Selection(p);
    VlnaPage *pg = new VlnaPage(p);
    int action;
    uint modify = 0;
    // mark where return
    uint actPage;
    plug = p;

    //fConfig.setName("/home/subzero/.scribus/scribus-vlna.rc");
    action = readConfig();
    actPage = plug->doc->ActPage->PageNr;
    // GUI dialog
    VlnaDialog *dlg = new VlnaDialog(parent, "dlg", TRUE, 0);
    dlg->selectAction(action);
    if (dlg->exec()==QDialog::Accepted) {
        action = dlg->actionSelected;
    } else {
        action = -1;
    }
    delete dlg;
    // perform action
    if (action!=-1) {
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        plug->FMess->setText(QObject::tr("Vlna processing. Wait please..."));
        switch (action) {
            case 0:
                modify = sel->parse();
                break;
            case 1:
                modify = pg->parse(plug->doc->ActPage);
                break;
            case 2:
                modify = pg->parseAll();
                break;
        } // switch
        // enable "Save" icon
        if (modify>0) {
            //plug->doc->setModified();
            plug->slotDocCh(true);
            //plug->DatSav->setEnabled(true);
        } // if
        // redraw document
        plug->view->DrawNew();
        QApplication::restoreOverrideCursor();
        plug->FMess->setText(QObject::tr("Vlna processing. Done."));
        plug->FProg->reset();
        // write config
        writeConfig(action);
        // set page where user calls vlna
        plug->view->GotoPage(actPage);
    } // action
    delete sel;
    delete pg;
} // constructor


int Vlna::readConfig()
{
    // configuration form RC file
    QString actCfg;
    QFile fConfig;

    fConfig.setName(QDir::homeDirPath() + "/.scribus/scribus-vlna.rc");
    if (fConfig.exists()) {
        fConfig.open(IO_ReadOnly);
        // errors handled in vlnadialog
        fConfig.readLine(actCfg, 8);
        fConfig.close();
        return actCfg.toInt();
    } else {
        return 0;
    }// if rc file exists
}


void Vlna::writeConfig(int aAction)
{
    QFile fConfig;
    QString actCfg;

    fConfig.setName(QDir::homeDirPath() + "/.scribus/scribus-vlna.rc");
    fConfig.open(IO_WriteOnly);
    actCfg.setNum(aAction);
    fConfig.writeBlock(actCfg, actCfg.length());
    fConfig.close();
}


void Vlna::errMessage(QString aMessage)
{
    QMessageBox::information( plug,
        QObject::tr("Vlna"),
        aMessage
        );
}


Vlna::~Vlna()
{
}
