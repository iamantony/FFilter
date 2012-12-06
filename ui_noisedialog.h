/********************************************************************************
** Form generated from reading UI file 'noisedialog.ui'
**
** Created: Thu 6. Dec 10:15:27 2012
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
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NoiseDialog
{
public:
    QLabel *noiseTypeLabel;
    QComboBox *noiseTypeCB;
    QLabel *ampLabel;
    QLineEdit *ampLE;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *NoiseDialog)
    {
        if (NoiseDialog->objectName().isEmpty())
            NoiseDialog->setObjectName(QString::fromUtf8("NoiseDialog"));
        NoiseDialog->resize(269, 112);
        noiseTypeLabel = new QLabel(NoiseDialog);
        noiseTypeLabel->setObjectName(QString::fromUtf8("noiseTypeLabel"));
        noiseTypeLabel->setGeometry(QRect(10, 15, 101, 16));
        noiseTypeCB = new QComboBox(NoiseDialog);
        noiseTypeCB->setObjectName(QString::fromUtf8("noiseTypeCB"));
        noiseTypeCB->setGeometry(QRect(150, 10, 111, 22));
        ampLabel = new QLabel(NoiseDialog);
        ampLabel->setObjectName(QString::fromUtf8("ampLabel"));
        ampLabel->setGeometry(QRect(10, 45, 81, 16));
        ampLE = new QLineEdit(NoiseDialog);
        ampLE->setObjectName(QString::fromUtf8("ampLE"));
        ampLE->setGeometry(QRect(150, 40, 111, 22));
        okBtn = new QPushButton(NoiseDialog);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setGeometry(QRect(100, 80, 75, 23));
        cancelBtn = new QPushButton(NoiseDialog);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(180, 80, 75, 23));

        retranslateUi(NoiseDialog);

        QMetaObject::connectSlotsByName(NoiseDialog);
    } // setupUi

    void retranslateUi(QDialog *NoiseDialog)
    {
        NoiseDialog->setWindowTitle(QApplication::translate("NoiseDialog", "Noise Settings", 0, QApplication::UnicodeUTF8));
        noiseTypeLabel->setText(QApplication::translate("NoiseDialog", "Noise type:", 0, QApplication::UnicodeUTF8));
        ampLabel->setText(QApplication::translate("NoiseDialog", "Amplitude:", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("NoiseDialog", "OK", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("NoiseDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NoiseDialog: public Ui_NoiseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOISEDIALOG_H
