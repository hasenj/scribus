/****************************************************************************
** Form interface generated from reading ui file 'loremdialog.ui'
**
** Created: Po lis 15 19:30:36 2004
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
class QComboBox;
class QSpinBox;
class QCheckBox;
class QPushButton;

class LoremDialog : public QDialog
{
    Q_OBJECT

public:
    LoremDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~LoremDialog();

    QLabel* textLabel2;
    QComboBox* typeBox;
    QLabel* textLabel1;
    QSpinBox* paragraphSpinBox;
    QCheckBox* startWithCheckBox;
    QLabel* descriptionLabel;
    QPushButton* okButton;
    QPushButton* cancelButton;

public slots:
    virtual void okButton_clicked();
    virtual void cancelButton_clicked();
    virtual void startWithCheckBox_clicked();
    virtual void typeBox_textChanged( const QString & );

protected:
    QGridLayout* LoremDialogLayout;
    QVBoxLayout* layout9;
    QVBoxLayout* layout7;
    QHBoxLayout* layout2;
    QHBoxLayout* layout1;
    QHBoxLayout* layout8;
    QSpacerItem* spacer2;

protected slots:
    virtual void languageChange();

};

#endif // LOREMDIALOG_H
