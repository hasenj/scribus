/****************************************************************************
** Form interface generated from reading ui file 'indexdialog.ui'
**
** Created: Čt pro 9 18:28:21 2004
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef INDEXDIALOG_H
#define INDEXDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QListBox;
class QListBoxItem;
class QPushButton;

class IndexDialog : public QDialog
{
    Q_OBJECT

public:
    IndexDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~IndexDialog();

    QListBox* stylesBox;
    QPushButton* appendButton;
    QPushButton* removeButton;
    QListBox* tocStylesBox;
    QPushButton* okButton;
    QPushButton* cancelButton;

public slots:
    virtual void init();
    virtual void cancelButton_pressed();
    virtual void okButton_pressed();
    virtual void appendButton_pressed();
    virtual void removeButton_pressed();
    virtual void stylesBox_selected( const QString & );

protected:
    QGridLayout* IndexDialogLayout;
    QVBoxLayout* layout13;
    QHBoxLayout* layout12;
    QVBoxLayout* layout11;
    QSpacerItem* spacer3;
    QSpacerItem* spacer2;
    QHBoxLayout* layout8;
    QSpacerItem* spacer1;

protected slots:
    virtual void languageChange();

};

#endif // INDEXDIALOG_H
