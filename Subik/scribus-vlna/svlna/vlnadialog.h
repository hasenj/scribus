/****************************************************************************
** Form interface generated from reading ui file 'vlnadialog.ui'
**
** Created: Út pro 2 21:08:35 2003
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef VLNADIALOG_H
#define VLNADIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QButtonGroup;
class QRadioButton;
class QPushButton;
class QLabel;

/** GUI dialog for user to make decision.
 \detail generated from Qt designer UI file. see source code from ./ui
    directory in distro package.*/
class VlnaDialog : public QDialog
{
    Q_OBJECT

public:
    VlnaDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~VlnaDialog();

    QButtonGroup* buttonGroup;
    QRadioButton* frameRadio;
    QRadioButton* pageRadio;
    QRadioButton* allRadio;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QLabel* statusLabel;

    int actionSelected;

    /**
     Readed from config file
     */
    void selectAction(int aAction);

public slots:
    virtual void okButton_pressed();
    virtual void cancelButton_pressed();
    virtual void frameRadio_pressed();
    virtual void pageRadio_pressed();
    virtual void allRadio_pressed();

protected:
    QGridLayout* VlnaDialogLayout;
    QVBoxLayout* layout4;
    QHBoxLayout* layout3;
    QVBoxLayout* layout2;
    QVBoxLayout* layout1;

protected slots:
    virtual void languageChange();

};

#endif // VLNADIALOG_H
