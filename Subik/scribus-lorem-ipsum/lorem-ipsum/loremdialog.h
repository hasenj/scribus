/****************************************************************************
** Form interface generated from reading ui file 'loremdialog.ui'
**
** Created: So lis 20 19:34:29 2004
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
class QTabWidget;
class QWidget;
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

    QTabWidget* tabWidget;
    QWidget* turkeyTab;
    QLabel* textLabel8;
    QLabel* textLabel4;
    QListView* dictionaryView;
    QLabel* textLabel5;
    QSpinBox* turkeyParagraphs;
    QLabel* textLabel6;
    QSpinBox* avgSentences;
    QCheckBox* turkeyStartLorem;
    QWidget* networkTab;
    QLabel* textLabel7;
    QLabel* textLabel4_2;
    QListView* networkView;
    QWidget* standardTab;
    QLabel* textLabel3;
    QLabel* textLabel1;
    QSpinBox* standardParaBox;
    QPushButton* okButton;
    QPushButton* cancelButton;

public slots:
    virtual void okButton_pressed();
    virtual void cancelButton_pressed();

protected:
    QGridLayout* LoremDialogLayout;
    QVBoxLayout* layout14;
    QGridLayout* turkeyTabLayout;
    QVBoxLayout* layout22;
    QHBoxLayout* layout21;
    QVBoxLayout* layout20;
    QSpacerItem* spacer2;
    QHBoxLayout* layout7;
    QHBoxLayout* layout8;
    QGridLayout* networkTabLayout;
    QVBoxLayout* layout19;
    QHBoxLayout* layout18;
    QVBoxLayout* layout16;
    QSpacerItem* spacer3;
    QVBoxLayout* layout5;
    QHBoxLayout* layout1;
    QHBoxLayout* layout3;
    QSpacerItem* spacer1;
    QHBoxLayout* layout2;

protected slots:
    virtual void languageChange();

};

#endif // LOREMDIALOG_H
