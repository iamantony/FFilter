/********************************************************************************
** Form generated from reading UI file 'maskdialog.ui'
**
** Created: Mon 26. Nov 10:34:20 2012
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
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_MaskDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTableWidget *maskTable;

    void setupUi(QDialog *MaskDialog)
    {
        if (MaskDialog->objectName().isEmpty())
            MaskDialog->setObjectName(QString::fromUtf8("MaskDialog"));
        MaskDialog->resize(403, 268);
        buttonBox = new QDialogButtonBox(MaskDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(50, 230, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        maskTable = new QTableWidget(MaskDialog);
        maskTable->setObjectName(QString::fromUtf8("maskTable"));
        maskTable->setGeometry(QRect(10, 10, 381, 211));
        maskTable->setProperty("showDropIndicator", QVariant(false));
        maskTable->setDragDropOverwriteMode(false);
        maskTable->setSelectionMode(QAbstractItemView::SingleSelection);
        maskTable->setCornerButtonEnabled(false);
        maskTable->setRowCount(0);
        maskTable->setColumnCount(0);
        maskTable->horizontalHeader()->setDefaultSectionSize(50);
        maskTable->horizontalHeader()->setMinimumSectionSize(30);
        maskTable->verticalHeader()->setDefaultSectionSize(25);
        maskTable->verticalHeader()->setMinimumSectionSize(15);

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
