/****************************************************************************
** Form interface generated from reading ui file 'indexdialog.ui'
**
** Created: Po pro 6 20:41:09 2004
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
class QLabel;
class QComboBox;
class QPushButton;

class IndexDialog : public QDialog
{
    Q_OBJECT

public:
    IndexDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~IndexDialog();

    QLabel* textLabel1;
    QComboBox* heading1;
    QLabel* textLabel2;
    QComboBox* heading2;
    QLabel* textLabel3;
    QComboBox* heading3;
    QLabel* textLabel4;
    QComboBox* heading4;
    QLabel* textLabel5;
    QComboBox* heading5;
    QLabel* textLabel6;
    QComboBox* heading6;
    QLabel* textLabel7;
    QComboBox* heading7;
    QPushButton* okButton;
    QPushButton* cancelButton;

public slots:
    virtual void cancelButton_pressed();
    virtual void okButton_pressed();
    virtual void heading1_textChanged( const QString & );
    virtual void heading2_textChanged( const QString & );
    virtual void heading3_textChanged( const QString & );
    virtual void heading4_textChanged( const QString & );
    virtual void heading5_textChanged( const QString & );
    virtual void heading6_textChanged( const QString & );
    virtual void heading7_textChanged( const QString & );
    virtual void init();

protected:
    QGridLayout* IndexDialogLayout;
    QVBoxLayout* layout10;
    QVBoxLayout* layout9;
    QHBoxLayout* layout1;
    QHBoxLayout* layout2;
    QHBoxLayout* layout3;
    QHBoxLayout* layout4;
    QHBoxLayout* layout5;
    QHBoxLayout* layout6;
    QHBoxLayout* layout7;
    QHBoxLayout* layout8;
    QSpacerItem* spacer1;

protected slots:
    virtual void languageChange();

};

#endif // INDEXDIALOG_H
