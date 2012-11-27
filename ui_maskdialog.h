/********************************************************************************
** Form generated from reading UI file 'maskdialog.ui'
**
** Created: Tue 27. Nov 09:58:29 2012
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
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_MaskDialog
{
public:
    QTableWidget *maskTable;
    QPushButton *cancelBtn;
    QPushButton *okBtn;

    void setupUi(QDialog *MaskDialog)
    {
        if (MaskDialog->objectName().isEmpty())
            MaskDialog->setObjectName(QString::fromUtf8("MaskDialog"));
        MaskDialog->resize(403, 268);
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
        cancelBtn = new QPushButton(MaskDialog);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(320, 230, 75, 23));
        okBtn = new QPushButton(MaskDialog);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setGeometry(QRect(240, 230, 75, 23));

        retranslateUi(MaskDialog);

        QMetaObject::connectSlotsByName(MaskDialog);
    } // setupUi

    void retranslateUi(QDialog *MaskDialog)
    {
        MaskDialog->setWindowTitle(QApplication::translate("MaskDialog", "Mask settings", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("MaskDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("MaskDialog", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MaskDialog: public Ui_MaskDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASKDIALOG_H
