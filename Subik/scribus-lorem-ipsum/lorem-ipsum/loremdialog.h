/****************************************************************************
** Form interface generated from reading ui file 'loremdialog.ui'
**
** Created: Út lis 23 19:04:41 2004
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef LOREMDIALOG_H
#define LOREMDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QListView;
class QListViewItem;
class QSpinBox;
class QCheckBox;
class QPushButton;

class LoremDialog : public QDialog
{
    Q_OBJECT

public:
    LoremDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~LoremDialog();

    QLabel* textLabel8;
    QListView* dictionaryView;
    QLabel* textLabel5;
    QSpinBox* turkeyParagraphs;
    QLabel* textLabel6;
    QSpinBox* avgSentences;
    QCheckBox* shouldStartLorem;
    QPushButton* okButton;
    QPushButton* cancelButton;

public slots:
    virtual void okButton_pressed();
    virtual void cancelButton_pressed();

protected:
    QGridLayout* LoremDialogLayout;
    QVBoxLayout* layout24;
    QHBoxLayout* layout7;
    QHBoxLayout* layout8;
    QHBoxLayout* layout3;
    QSpacerItem* spacer1;
    QHBoxLayout* layout2;

protected slots:
    virtual void languageChange();

};

#endif // LOREMDIALOG_H
