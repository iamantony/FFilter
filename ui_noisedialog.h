/********************************************************************************
** Form generated from reading UI file 'noisedialog.ui'
**
** Created: Fri 23. Nov 11:49:48 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOISEDIALOG_H
#define UI_NOISEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_NoiseDialog
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NoiseDialog)
    {
        if (NoiseDialog->objectName().isEmpty())
            NoiseDialog->setObjectName(QString::fromUtf8("NoiseDialog"));
        NoiseDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(NoiseDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(NoiseDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NoiseDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NoiseDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NoiseDialog);
    } // setupUi

    void retranslateUi(QDialog *NoiseDialog)
    {
        NoiseDialog->setWindowTitle(QApplication::translate("NoiseDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NoiseDialog: public Ui_NoiseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOISEDIALOG_H
