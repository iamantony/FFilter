/********************************************************************************
** Form generated from reading UI file 'maskdialog.ui'
**
** Created: Wed 21. Nov 15:24:51 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MASKDIALOG_H
#define UI_MASKDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_MaskDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTableView *tableView;

    void setupUi(QDialog *MaskDialog)
    {
        if (MaskDialog->objectName().isEmpty())
            MaskDialog->setObjectName(QString::fromUtf8("MaskDialog"));
        MaskDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(MaskDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tableView = new QTableView(MaskDialog);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 20, 256, 192));

        retranslateUi(MaskDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), MaskDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MaskDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(MaskDialog);
    } // setupUi

    void retranslateUi(QDialog *MaskDialog)
    {
        MaskDialog->setWindowTitle(QApplication::translate("MaskDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MaskDialog: public Ui_MaskDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASKDIALOG_H
